#include "SrodMuxer.h"
#include "SrodError.pb.h"
#include "SrodPipeVideoDefine.pb.h"
extern "C" {
#include "libavutil/opt.h"
#include "libavutil/imgutils.h"
#include "libavutil/error.h"
#include "libavutil/hwcontext.h"
#include "libavutil/mem.h"
}

#define Srod_Wait(msec) std::this_thread::sleep_for(std::chrono::milliseconds(msec))

SrodMuxer::SrodMuxer(void)
    : m_status(Srod::PipeVideo::RECORD_IDLE)
    , m_szRecordFile("")
    , m_cbFunc(nullptr)
    , m_dwUser(0)
    , m_nFrameRate(25)
    , m_encodingType(ENCODING_H264)
    , m_codec(nullptr)
    , m_codecCtx(nullptr)
    , m_formatCtx(nullptr)
{
}

SrodMuxer::~SrodMuxer(void)
{
}

int SrodMuxer::startRecord(const char* p_file, lpRecordStatusCallback p_cbFunc, void* p_dwUser)
{
    if (Srod::PipeVideo::RECORD_IDLE != m_status)
        return Srod::Error::SROD_ERR_IN_USE;

    if (nullptr == p_file)
        return Srod::Error::SROD_ERR_INVALID_PARAM;

    m_szRecordFile = p_file;
    m_cbFunc = p_cbFunc;
    m_dwUser = p_dwUser;
    m_bFrameInit = false;

    m_thread = std::make_shared<std::thread>(std::bind(&SrodMuxer::run, this));
    m_thread->detach();
    m_status = Srod::PipeVideo::RECORD_ING;
    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodMuxer::pauseRecord(bool p_pause)
{
    if (Srod::PipeVideo::RECORD_ING != m_status && Srod::PipeVideo::RECORD_PAUSE != m_status)
        return Srod::Error::SROD_ERR_NOT_OPENED;

    if (p_pause)
        m_status = Srod::PipeVideo::RECORD_PAUSE;
    else
        m_status = Srod::PipeVideo::RECORD_ING;
    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodMuxer::stopRecord(int p_forceStop)
{
    if (Srod::PipeVideo::RECORD_STOP == m_status || Srod::PipeVideo::RECORD_IDLE == m_status)
        return Srod::Error::SROD_ERR_SUCCESS;

    m_status = Srod::PipeVideo::RECORD_STOP;
    if (p_forceStop)
        m_memQueue.clear();
    return Srod::Error::SROD_ERR_SUCCESS;
}

void SrodMuxer::writeFrame(AVFrame* frameYUV)
{
    if (Srod::PipeVideo::RECORD_ING != m_status)
        return;

    if (!m_bFrameInit)
    {
        memcpy(&m_frameYUV, frameYUV, sizeof(AVFrame));
        m_bFrameInit = true;
        m_nFrameIndex = 0;
    }

    if (nullptr == m_memPool)
    {
        m_memPool = std::make_shared<SrodMemPool>();
        m_memPool->init(frameYUV->width * frameYUV->height * 1.5, 10, false);
    }

    Mem_Ptr mem = m_memPool->get();
    if (nullptr == mem)
    {
        if (m_cbFunc)
            m_cbFunc(Srod::PipeVideo::RECORD_ING, Srod::Error::SROD_ERR_RECORD_DROP, 0, m_dwUser);
        return;
    }

    int YLen = frameYUV->width * frameYUV->height;
    int ULen = frameYUV->width * frameYUV->height / 4;
    int VLen = frameYUV->width * frameYUV->height / 4;

    char* buff = mem.get();
    memcpy(buff, frameYUV->data[0], YLen);
    memcpy(buff + YLen, frameYUV->data[1], VLen);
    memcpy(buff + YLen + ULen, frameYUV->data[2], ULen);

    m_memQueue.put(mem);
}

void SrodMuxer::run()
{
    m_bInitFlag = false;
    while (true)
    {
        if (!m_bInitFlag)
        {
            if (!m_bFrameInit)
            {
                Srod_Wait(25);
                continue;
            }

            init();
            m_bInitFlag = true;
        }

        Mem_Ptr mem = m_memQueue.get();
        if (nullptr == mem)
        {
            if (Srod::PipeVideo::RECORD_STOP == m_status)
                break;

            int msec = 100;
            if (Srod::PipeVideo::RECORD_ING == m_status)
                msec = 10;
            Srod_Wait(msec);
            continue;
        }

        writeMp4(mem.get());
    }

    //muxend()
    closeMp4();
    m_status = Srod::PipeVideo::RECORD_IDLE;
    if (m_cbFunc)
        m_cbFunc(Srod::PipeVideo::RECORD_IDLE, Srod::Error::SROD_ERR_SUCCESS, (m_nFrameIndex - 1) * 1000 / m_nFrameRate, m_dwUser);
}

int SrodMuxer::init(/*AVFrame* frameYUV, const char* file, *//*int framerate, int codectype*/)
{
    if (NULL != m_codecCtx)
        return Srod::Error::SROD_ERR_SUCCESS;
    AVDictionary* param = 0;

    //     ReadEncodecConfig();
    //     m_nCurrFramerate = framerate;
    //     CheckConfig();

    //av_register_all();
    //av_log_set_level(AV_LOG_DEBUG);
    //av_log_set_flags(AV_LOG_SKIP_REPEATED);
    //av_log_set_callback(libffmpeg_log_callback);

    if (ENCODING_H265 == m_encodingType)
        m_codec = avcodec_find_encoder(AV_CODEC_ID_H265);
    else
        m_codec = avcodec_find_encoder(AV_CODEC_ID_H264);

    if (NULL == m_codec)
    {
        //LogFileDebug("record.log", "find AV_CODEC_ID_H264 fail! \n");
        return Srod::Error::SROD_ERR_NOT_READY;
    }

    //分配AVCodecContex实例
    m_codecCtx = avcodec_alloc_context3(m_codec);
    if (NULL == m_codecCtx)
    {
        //LogFileDebug("record.log", "avcodec_alloc_context3  ERROR\n");
        return Srod::Error::SROD_ERR_NOT_READY;
    }

    //设置编×××的参数
    m_codecCtx->width = m_frameYUV.width;//帧高
    m_codecCtx->height = m_frameYUV.height;
    m_codecCtx->bit_rate = m_frameYUV.sample_rate;//比特率
    AVRational r = { 1, m_nFrameRate };//设置帧率
    m_codecCtx->time_base = r;
    m_codecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    m_codecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

    m_codecCtx->gop_size = m_nFrameRate;//m_nGopSize;
    m_codecCtx->max_b_frames = 0;
    if (ENCODING_H265 == m_encodingType)
    {
        av_dict_set(&param, "preset", "veryfast", 0);
        av_dict_set(&param, "tune", "zero-latency", 0);
    }
    else
    {
        //m_codecCtx->qmin = m_nQmin;
        //m_codecCtx->qmax = m_nQmax;
        //preset: ultrafast, superfast, veryfast, faster, fast,
        //medium, slow, slower, veryslow, placebo
        const char* pszPreset = "veryfast";
        av_opt_set(m_codecCtx->priv_data, "preset", pszPreset, 0);
    }

    if (avcodec_open2(m_codecCtx, m_codec, NULL) < 0)
    {
        //LogFileDebug("record.log", "avcodec_open2 ERR\n");
        av_free(m_codecCtx);
        return Srod::Error::SROD_ERR_NOT_READY;
    }

    //memcpy(&m_avFrame, frameYUV, sizeof(AVFrame));
    //m_frameYUV = &m_avFrame;

    int nRet = openMp4();
    if (Srod::Error::SROD_ERR_SUCCESS != nRet)
    {
        avcodec_close(m_codecCtx);
        av_free(m_codecCtx);
        return nRet;
    }

    //LogFileDebug("record.log", "YuvH264Muxing[%p] Start\n", this);
    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodMuxer::openMp4()
{
    if (m_formatCtx)
        return 0;

    const char* out_file = m_szRecordFile.c_str();
    int nRet = avformat_alloc_output_context2(&m_formatCtx, NULL, NULL, out_file);
    if (0 > nRet)
    {
        //char errbuf[1024] = { 0 };
        //int nLen = av_strerror(nRet, errbuf, 1024);
        //LogFileDebug("record.log", errbuf);
        return -1;
    }
    nRet = avio_open(&m_formatCtx->pb, out_file, AVIO_FLAG_READ_WRITE);
    if (0 > nRet)
    {
        //char errbuf[1024] = { 0 };
        //int nLen = av_strerror(nRet, errbuf, 1024);
        //LogFileDebug("record.log", errbuf);

        avformat_free_context(m_formatCtx);
        return -1;
    }

    // 构建一个新stream
    AVStream* pAVStream = avformat_new_stream(m_formatCtx, 0);
    if (pAVStream == NULL)
    {
        //char errbuf[1024] = { 0 };
        //int nLen = av_strerror(nRet, errbuf, 1024);
        //LogFileDebug("record.log", errbuf);

        avio_close(m_formatCtx->pb);
        avformat_free_context(m_formatCtx);
        return -1;
    }

    avcodec_parameters_from_context(m_formatCtx->streams[0]->codecpar, m_codecCtx);
    av_dump_format(m_formatCtx, 0, out_file, 1);
    nRet = avformat_write_header(m_formatCtx, NULL);
    if (nRet < 0)
    {
        //char errbuf[1024] = { 0 };
        //int nLen = av_strerror(nRet, errbuf, 1024);
        //LogFileDebug("record.log", errbuf);

        avio_close(m_formatCtx->pb);
        avformat_free_context(m_formatCtx);
        return -1;
    }
    av_init_packet(&m_pkt);
    return Srod::Error::SROD_ERR_SUCCESS;
}
int SrodMuxer::writeMp4(const char* p_yuvBuff)
{
    if (NULL == m_codecCtx)
        return Srod::Error::SROD_ERR_THREAD_STOP;

    do
    {
        int YLen = m_frameYUV.width * m_frameYUV.height;
        int ULen = YLen / 4;
        int VLen = ULen;

        uint8_t* yuvBuff = (uint8_t*)p_yuvBuff;
        m_frameYUV.data[0] = yuvBuff;
        m_frameYUV.data[1] = yuvBuff + YLen;
        m_frameYUV.data[2] = yuvBuff + YLen + ULen;

        m_pkt.data = NULL;
        m_pkt.size = 0;

        //int got_picture = 0;
        //Encode 编码
        //m_nTestYuvBegin = TcUnsTime::GetMilliseconds();
        int nRet = avcodec_send_frame(m_codecCtx, &m_frameYUV);
        if (Srod::Error::SROD_ERR_SUCCESS != nRet)
            break;

        nRet = avcodec_receive_packet(m_codecCtx, &m_pkt);
        if (Srod::Error::SROD_ERR_SUCCESS != nRet)
            break;
        //m_nTestYuvEnd = TcUnsTime::GetMilliseconds();

        //LogFileDebug("recordEncode.log", "Encode one frame success, cost: %d\n", m_nTestYuvEnd - m_nTestYuvBegin);
        m_pkt.pts = av_rescale_q((m_nFrameIndex++), m_codecCtx->time_base, m_formatCtx->streams[0]->time_base);
        m_pkt.dts = m_pkt.pts;
        //m_nCurrPTS = m_pkt.pts;
        m_pkt.duration = av_rescale_q(m_pkt.duration, m_codecCtx->time_base, m_formatCtx->streams[0]->time_base);
        av_interleaved_write_frame(m_formatCtx, &m_pkt);

        av_packet_unref(&m_pkt);

        if (m_cbFunc && 0 == ((m_nFrameIndex - 1) % m_nFrameRate))
            m_cbFunc(Srod::PipeVideo::RECORD_ING, Srod::Error::SROD_ERR_SUCCESS, (m_nFrameIndex - 1) * 1000 / m_nFrameRate, m_dwUser);
    }
    while (0);
    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodMuxer::closeMp4()
{
    if (NULL == m_codecCtx)
        return Srod::Error::SROD_ERR_THREAD_STOP;
    //m_nCurrFramerate = -1;
    //m_nCurrPTS = 0;
    //m_nPTSBase = 0;
    int nRet = 0;
    bool bFirst = true;
    while (true)
    {
        //经测试最后再插入一个空帧
        if (bFirst)
        {
            nRet = avcodec_send_frame(m_codecCtx, NULL);
            if (Srod::Error::SROD_ERR_SUCCESS != nRet)
                break;
            bFirst = false;
        }

        nRet = avcodec_receive_packet(m_codecCtx, &m_pkt);
        if (Srod::Error::SROD_ERR_SUCCESS != nRet)
            break;

        m_pkt.pts = av_rescale_q((m_nFrameIndex++), m_codecCtx->time_base, m_formatCtx->streams[0]->time_base);
        m_pkt.dts = m_pkt.pts;
        m_pkt.duration = av_rescale_q(m_pkt.duration, m_codecCtx->time_base, m_formatCtx->streams[0]->time_base);
        av_interleaved_write_frame(m_formatCtx, &m_pkt);

        av_packet_unref(&m_pkt);

        if (m_cbFunc && 0 == ((m_nFrameIndex - 1) % m_nFrameRate))
            m_cbFunc(Srod::PipeVideo::RECORD_ING, Srod::Error::SROD_ERR_SUCCESS, (m_nFrameIndex - 1) * 1000 / m_nFrameRate, m_dwUser);
    }

    av_write_trailer(m_formatCtx);
    if (m_formatCtx)
    {
        if (m_formatCtx->pb)
            avio_close(m_formatCtx->pb);
        avformat_free_context(m_formatCtx);
    }

    avcodec_close(m_codecCtx);
    av_free(m_codecCtx);

    m_formatCtx = NULL;
    m_codecCtx = NULL;
    m_codec = NULL;
    //m_ptsInc = 0;
    //m_nRecordFlag = 0;
    return Srod::Error::SROD_ERR_THREAD_STOP;
}
