#include "SrodDecoder.h"
extern "C" {
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
#include "libavutil/imgutils.h"
#include "libavutil/error.h"
#include "libavutil/hwcontext.h"
}
#include "SrodError.pb.h"

SrodDecoder::SrodDecoder(void)
    : m_encodingType(ENCODING_UNKNOWN)
    , m_codec(nullptr)
    , m_codecCtx(nullptr)
    , m_frameYUV(nullptr)
{
}

SrodDecoder::~SrodDecoder(void)
{
    uninitFfmpeg();
}

int SrodDecoder::decode(const void* p_srodFrame)
{
    SrodFrame* srodFrame = (SrodFrame*)p_srodFrame;
    if (m_encodingType != srodFrame->_head._encodingType)
    {
        uninitFfmpeg();

        int nRet = initFfmpeg(static_cast<EncodingType>(srodFrame->_head._encodingType));
        if (Srod::Error::SROD_ERR_SUCCESS != nRet)
            return nRet;

        m_encodingType = (EncodingType)srodFrame->_head._encodingType;
    }

    if (ENCODING_H265 == srodFrame->_head._encodingType || ENCODING_H264 == srodFrame->_head._encodingType)
    {
        unsigned char* pData = (unsigned char*)srodFrame->_frame;
        int nDataLen = srodFrame->_head._frameLen;
        int nRet = ffmpegDecode(pData, nDataLen);
        if (Srod::Error::SROD_ERR_SUCCESS != nRet)
        {
            uninitFfmpeg();
            return nRet;
        }
    }
    else if (ENCODING_YV12 == srodFrame->_head._encodingType)
    {
        av_image_fill_arrays(m_frameYUV->data, m_frameYUV->linesize, (const uint8_t*)srodFrame->_frame, AV_PIX_FMT_YUV420P, srodFrame->_head._imageWidth, srodFrame->_head._imageHeight, 1);

        //交换UV数据,YV12转YUV420
        uint8_t* yuvBuff = m_frameYUV->data[1];
        m_frameYUV->data[1] = m_frameYUV->data[2];
        m_frameYUV->data[2] = yuvBuff;
        m_frameYUV->width = srodFrame->_head._imageWidth;
        m_frameYUV->height = srodFrame->_head._imageHeight;
        m_frameYUV->format = AV_PIX_FMT_YUV420P;
    }

    return Srod::Error::SROD_ERR_SUCCESS;
}

AVFrame* SrodDecoder::getYUV()
{
    return m_frameYUV;
}

int SrodDecoder::initFfmpeg(EncodingType p_encodingType)
{
    //av_register_all();
    if (ENCODING_H265 == p_encodingType || ENCODING_H264 == p_encodingType)
    {
        AVCodecID codecID = ENCODING_H265 == p_encodingType ? AV_CODEC_ID_HEVC : AV_CODEC_ID_H264;

        //     av_log_set_level(AV_LOG_DEBUG);
        //     av_log_set_flags(AV_LOG_SKIP_REPEATED);
        //     av_log_set_callback(libffmpeg_log_callback);

        //avcodec_register_all();
        // AV_CODEC_ID H264是AV_CODEC_ID_H264, H265是AV_CODEC_ID_HEVC, 具体看ffmpeg源码中的宏定义
        m_codec = avcodec_find_decoder(codecID);
        m_codecCtx = avcodec_alloc_context3(m_codec);

        //     m_hwDeviceType = av_hwdevice_find_type_by_name("dxva2");
        //     m_hwPixFmt = find_fmt_by_hw_type(m_hwDeviceType);
        //     if (AV_PIX_FMT_NONE != m_hwPixFmt)
        //     {
        //         av_opt_set_int(m_codecCtx, "refcounted_frames", 1, 0);
        //         if (InitHwDecoder(m_codecCtx) < 0)
        //         {
        //             return -1;
        //         }
        //     }

        int avcodecopenRes = avcodec_open2(m_codecCtx, m_codec, 0);
        if (avcodecopenRes < 0)
        {
            if (m_codecCtx)
            {
                av_free(m_codecCtx);
                m_codecCtx = NULL;
                return -1;
            }
        }
    }
    m_frameYUV = av_frame_alloc();
    if (!m_frameYUV)
    {
        if (m_codecCtx)
        {
            avcodec_close(m_codecCtx);
            av_free(m_codecCtx);
            m_codecCtx = NULL;
        }
        return -1;
    }

    return Srod::Error::SROD_ERR_SUCCESS;
}
//释放解码器
void SrodDecoder::uninitFfmpeg()
{
    if (m_codec && m_codecCtx)
    {
        m_codec->close(m_codecCtx);
        m_codec = NULL;
    }
    if (m_codecCtx)
    {
        avcodec_close(m_codecCtx);
        av_free(m_codecCtx);
    }
    if (m_frameYUV)
        av_free(m_frameYUV);

    m_frameYUV = nullptr;
    m_codec = nullptr;
    m_codecCtx = nullptr;
    m_encodingType = ENCODING_UNKNOWN;
}

int SrodDecoder::ffmpegDecode(unsigned char* avpkt_data, int avpkt_size)
{
    AVPacket avpkt;
    memset(&avpkt, 0, sizeof(AVPacket));
    avpkt.data = avpkt_data;
    avpkt.size = avpkt_size;
    int nRet = avcodec_send_packet(m_codecCtx, &avpkt);
    if (nRet != 0)
    {
        char szErr[AV_ERROR_MAX_STRING_SIZE] = { 0 };
        av_make_error_string(szErr, AV_ERROR_MAX_STRING_SIZE, nRet);
        return nRet;
    }

    nRet = avcodec_receive_frame(m_codecCtx, m_frameYUV);
    if (nRet != 0)
    {
        char szErr[AV_ERROR_MAX_STRING_SIZE] = { 0 };
        av_make_error_string(szErr, AV_ERROR_MAX_STRING_SIZE, nRet);
        return nRet;
    }

    return Srod::Error::SROD_ERR_SUCCESS;
}
