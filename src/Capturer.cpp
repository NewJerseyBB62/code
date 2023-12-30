#include "SrodCapturer.h"
extern "C" {
#include "libavutil/opt.h"
#include "libavutil/imgutils.h"
#include "libavutil/error.h"
#include "libavutil/hwcontext.h"
#include "libavutil/mem.h"
}
#include <thread>
#include "SrodError.pb.h"

#define Srod_Wait(msec) std::this_thread::sleep_for(std::chrono::milliseconds(msec))

SrodCapturer::SrodCapturer(void)
    : m_status(SNAPSHOT_IDLE)
    , m_frameBuff(nullptr)
    , m_buffSize(0)
{
}

SrodCapturer::~SrodCapturer(void)
{
}

int SrodCapturer::snapshot(const char* p_file)
{
    if (SNAPSHOT_IDLE != m_status)
        return Srod::Error::SROD_ERR_IN_USE;

    m_status = SNAPSHOT_START;
    int timeout = 1500;
    do
    {
        Srod_Wait(100);
        if (SNAPSHOT_READY == m_status)
            break;

        timeout -= 100;
    }
    while (timeout > 0);

    if (SNAPSHOT_READY != m_status)
        return Srod::Error::SROD_ERR_TIMEOUT;

    saveFile(p_file);
    m_status = SNAPSHOT_IDLE;
    return Srod::Error::SROD_ERR_SUCCESS;
}

void SrodCapturer::writeFrame(AVFrame* frameYUV)
{
    if (SNAPSHOT_START != m_status)
        return;

    memcpy(&m_frameYUV, frameYUV, sizeof(AVFrame));
    if (nullptr == m_frameBuff)
    {
        //frameYUV->format
        m_buffSize = frameYUV->width * frameYUV->height * 1.5;
        m_frameBuff = new char[m_buffSize];
    }

    int YLen = frameYUV->width * frameYUV->height;
    int ULen = frameYUV->width * frameYUV->height / 4;
    int VLen = frameYUV->width * frameYUV->height / 4;

    memcpy(m_frameBuff, frameYUV->data[0], YLen);
    memcpy(m_frameBuff + YLen, frameYUV->data[1], VLen);
    memcpy(m_frameBuff + YLen + ULen, frameYUV->data[2], ULen);
    m_frameYUV.data[0] = (uint8_t*)m_frameBuff;
    m_frameYUV.data[1] = (uint8_t*)(m_frameBuff + YLen);
    m_frameYUV.data[2] = (uint8_t*)(m_frameBuff + YLen + ULen);

    m_status = SNAPSHOT_READY;
}

int SrodCapturer::saveFile(const char* p_file)
{
    //av_register_all();
    AVPacket pkt;
    av_init_packet(&pkt);
    bool bNewPkt = false;
    AVCodecContext* pCodecCtx = nullptr;
    AVFormatContext* pFormatCtx = nullptr;
    int nRet = Srod::Error::SROD_ERR_SUCCESS;
    std::string strOperation;
    do
    {
        // 分配AVFormatContext对象
        pFormatCtx = avformat_alloc_context();

        // 设置输出文件格式
        pFormatCtx->oformat = av_guess_format("mjpeg", NULL, NULL);
        // 创建并初始化一个和该url相关的AVIOContext
        nRet = avio_open(&pFormatCtx->pb, p_file, AVIO_FLAG_READ_WRITE);
        if (0 > nRet)
        {
            char errbuf[1024] = { 0 };
            int nLen = av_strerror(nRet, errbuf, 1024);
            strOperation = "avio_open";
            nRet = Srod::Error::SROD_ERR_NOT_OPENED;
            break;
        }

        nRet = Srod::Error::SROD_ERR_NOT_READY;

        // 构建一个新stream
        AVStream* pAVStream = avformat_new_stream(pFormatCtx, 0);
        if (pAVStream == NULL)
        {
            strOperation = "avformat_new_stream";
            break;
        }

        av_dump_format(pFormatCtx, 0, p_file, 1);

        // 查找解码器
        AVCodec* pCodec = avcodec_find_encoder(pFormatCtx->oformat->video_codec);
        if (!pCodec)
        {
            strOperation = "avcodec_find_encoder codec:";
            //            strOperation.append(std::to_string(pFormatCtx->oformat->video_codec));
            break;
        }

        // 设置pCodecCtx的解码器为pCodec
        pCodecCtx = avcodec_alloc_context3(pCodec);
        pCodecCtx->codec_id = pFormatCtx->oformat->video_codec;
        pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
        pCodecCtx->pix_fmt = AV_PIX_FMT_YUVJ420P;
        pCodecCtx->width = m_frameYUV.width;
        pCodecCtx->height = m_frameYUV.height;
        pCodecCtx->time_base.num = 1;
        pCodecCtx->time_base.den = 25;
        pCodecCtx->qcompress = 1.0; //默认质量0.5，这里改成成1.0，按最好质量保存
        nRet = avcodec_open2(pCodecCtx, pCodec, NULL);
        if (0 != nRet)
        {
            strOperation = "avcodec_open2";
            break;
        }
        avcodec_parameters_from_context(pFormatCtx->streams[0]->codecpar, pCodecCtx);
        //Write Header
        avformat_write_header(pFormatCtx, NULL);

        int y_size = pCodecCtx->width * pCodecCtx->height;

        //Encode
        // 给AVPacket分配足够大的空间
        //nRet = av_new_packet(&pkt, y_size * 3);
        //if (0 != nRet)
        //{
        //    strOperation = "av_new_packet";
        //    break;
        //}
        //bNewPkt = true;
        nRet = avcodec_send_frame(pCodecCtx, &m_frameYUV);
        if (0 != nRet)
        {
            strOperation = "avcodec_send_frame";
            break;
        }

        nRet = avcodec_receive_packet(pCodecCtx, &pkt);
        if (0 != nRet)
        {
            strOperation = "avcodec_receive_packet";
            break;
        }

        nRet = av_write_frame(pFormatCtx, &pkt);
        if (0 != nRet)
        {
            strOperation = "av_write_frame";
            break;
        }

        //Write Trailer
        nRet = av_write_trailer(pFormatCtx);
        if (0 != nRet)
        {
            strOperation = "av_write_trailer";
            break;
        }
    }
    while (0);

    //if (bNewPkt)
    av_packet_unref(&pkt);

    if (pCodecCtx)
    {
        avcodec_close(pCodecCtx);
        avcodec_free_context(&pCodecCtx);
    }
    if (pFormatCtx)
    {
        if (pFormatCtx->pb)
            avio_close(pFormatCtx->pb);

        avformat_free_context(pFormatCtx);
    }
    if (0 != nRet)
        return Srod::Error::SROD_ERR_HANDLE_FAILED;
    return Srod::Error::SROD_ERR_SUCCESS;
}
