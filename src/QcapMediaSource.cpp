#include "QcapMediaSource.h"
#include <string.h>
#include "SrodError.pb.h"
#include "MediaFactory.h"
#include "logger.h"

int IMediaSource::m_sensitivitySec = 10;
int IMediaSource::m_timeoutSec = 5;
bool IMediaSource::m_autoReconnect = true;
int IMediaSource::m_intervalSec = 5;
IMediaSource* MediaFactory::createSource()
{
    return new QcapMediaSource();
}

QcapMediaSource::QcapMediaSource(void)
{
	m_cbFrame = nullptr;
	m_dwUser = nullptr;
}

QcapMediaSource::~QcapMediaSource(void)
{
	QCAP_DESTROY(m_videoDevice);
	m_videoDevice = nullptr;
}

int QcapMediaSource::init(const char* p_url, const char* p_user, const char* p_pwd, int p_streamID)
{
    CoInitialize(nullptr);
    char dvsName[32] = "MZ0380 PCI";
    int nRet = QCAP_CREATE(dvsName, 0, 0, &m_videoDevice, FALSE, FALSE);
    if (QCAP_RS_SUCCESSFUL != nRet)
    {
        log("media.log", "%s %d open:%s ret:%d\n", __FILE__, __LINE__, "QCAP_CREATE", nRet);
        return Srod::Error::SROD_ERR_NOT_READY;
    }
    memset(&m_frame, 0, sizeof(SrodFrame));
    //m_frame._head._dvsID[8];      //设备ID
    m_frame._head._channelID = 1;     //视频通道号
    m_frame._head._streamID = 0;      //流编号
    m_frame._head._streamType = STREAM_VIDEO;    //流类型，TeStreamType
    m_frame._head._encodingType = ENCODING_YV12;  //编码格式,TeEncoderType
    m_frame._head._sequenceId = 0;    //数据帧序号
    m_frame._head._frameType = FRAME_I;     //数据帧类型,TeFrameType
    m_frame._head._frameRate = 25;     //帧率
    m_frame._head._imageWidth = 1920;    //视频宽度
    m_frame._head._imageHeight = 1080;   //视频高度
    //m_frame._head._timestamp;     //数据采集时间戳，单位为毫秒
    //m_frame._head._frameLen;      //数据有效长度

    nRet = QCAP_SET_VIDEO_DEFAULT_OUTPUT_FORMAT(m_videoDevice, QCAP_COLORSPACE_TYPE_YV12/*QCAP_COLORSPACE_TYEP_I420*/, 1920, 1080, false, 25);
    if (QCAP_RS_SUCCESSFUL != nRet)
    {
        log("media.log", "%s %d open:%s ret:%d\n", __FILE__, __LINE__, "QCAP_SET_VIDEO_DEFAULT_OUTPUT_FORMAT", nRet);
        return Srod::Error::SROD_ERR_NOT_READY;
    }
    nRet = QCAP_REGISTER_VIDEO_PREVIEW_CALLBACK(m_videoDevice, &QcapMediaSource::callbackVideoPreview, this);
    if (QCAP_RS_SUCCESSFUL != nRet)
    {
        log("media.log", "%s %d open:%s ret:%d\n", __FILE__, __LINE__, "QCAP_REGISTER_VIDEO_PREVIEW_CALLBACK", nRet);
        return Srod::Error::SROD_ERR_NOT_READY;
    }

    log("media.log", "%s %d open:%s Success\n", __FILE__, __LINE__, "init");
    return Srod::Error::SROD_ERR_SUCCESS;
}

void QcapMediaSource::uninit()
{
    QCAP_DESTROY(m_videoDevice);
    CoUninitialize();
}

int QcapMediaSource::openStream(CallbackFrame p_cbFrame, void* p_dwUser)
{
    m_cbFrame = p_cbFrame;
    m_dwUser = p_dwUser;
#if W_QCAP
    m_pf = fopen("test.yuv", "wb");
    m_nCnt = 10;
#endif
#if R_QCAP
    m_pf = nullptr;
    m_bRun = true;
    m_thread = std::make_shared<std::thread>(std::bind(&QcapMediaSource::run, this));
#endif
    int nRet = QCAP_RUN(m_videoDevice);
    if (QCAP_RS_SUCCESSFUL != nRet)
    {
        return Srod::Error::SROD_ERR_NOT_READY;
    }
    //log("media.log", "%s %d oper:%s Success\n", __FILE__, __LINE__, "QCAP_RUN");
    return Srod::Error::SROD_ERR_SUCCESS;
}

int QcapMediaSource::closeStream(void* p_playHandle)
{
#if R_QCAP
    m_bRun = false;
#endif
    QCAP_STOP(m_videoDevice);
#if W_QCAP
    fclose(m_pf);
#endif
    return Srod::Error::SROD_ERR_SUCCESS;
}

QRETURN QCAP_EXPORT QcapMediaSource::callbackVideoPreview(PVOID pDevice /*IN*/, double dSampleTime /*IN*/, BYTE* pFrameBuffer /*IN*/, ULONG nFrameBufferLen /*IN*/, PVOID pUserData /*IN*/)
{
    if (nullptr == pUserData)
        return QCAP_RT_OK;
    QcapMediaSource* obj = (QcapMediaSource*)pUserData;
    obj->callbackVideoPreview(pDevice, dSampleTime, pFrameBuffer, nFrameBufferLen);
    return QCAP_RT_OK;
}

void QcapMediaSource::callbackVideoPreview(PVOID pDevice, double dSampleTime, BYTE* pFrameBuffer, ULONG nFrameBufferLen)
{
    if (0 >= nFrameBufferLen || m_cbFrame == nullptr)
        return;
    m_frame._frame = (char*)pFrameBuffer;
    m_frame._head._timestamp = round(dSampleTime * 1000);     //数据采集时间戳，单位为毫秒
    m_frame._head._frameLen = nFrameBufferLen;

#if W_QCAP
    if (m_nCnt <= 0)
    {
        if (m_pf)
        {
            log("media.log", "%s %d oper:%s end\n", __FILE__, __LINE__, "callbackVideoPreview");
            fclose(m_pf);
            m_pf = nullptr;
        }
        return;
    }

    m_nCnt--;
    log("media.log", "%s %d oper:%s time:%f => %u len:%u frameLen:%u\n", __FILE__, __LINE__, "callbackVideoPreview", dSampleTime, m_frame._head._timestamp, nFrameBufferLen, m_frame._head._frameLen);
    fwrite(&m_frame._head, 1, sizeof(m_frame._head), m_pf);
    fwrite(pFrameBuffer, 1, nFrameBufferLen, m_pf);
#endif
    if (m_cbFrame)
        m_cbFrame(&m_frame, m_dwUser);
}

#if R_QCAP
void QcapMediaSource::run()
{
    m_pf = nullptr;
    char* buff = nullptr;
    int buffSize = 0;
    while (m_bRun)
    {
        if (nullptr == m_pf)
        {
            m_pf = fopen("test.yuv", "rb");
            if (nullptr == m_pf)
                break;
        }

        int nLen = fread(&m_frame._head, 1, sizeof(m_frame._head), m_pf);
        if (nLen <= 0)
            break;
        if (0 >= m_frame._head._frameLen)
            continue;

        if (buffSize < m_frame._head._frameLen)
        {
            if (buffSize > 0)
                delete[] buff;
            buff = new char[m_frame._head._frameLen];
            buffSize = m_frame._head._frameLen;
        }
        fread(buff, 1, m_frame._head._frameLen, m_pf);
        m_frame._frame = buff;
        if (m_cbFrame)
            m_cbFrame(&m_frame, m_dwUser);
    }
    if (nullptr != m_pf)
        fclose(m_pf);
}

#endif
