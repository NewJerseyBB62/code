#include "SrodPlayer.h"
#include "SrodDecoder.h"
#include "SrodRender.h"
#include "SrodMuxer.h"
#include "SrodOverlay.h"
#include "SrodCapturer.h"
#include "mediacommon.h"
#include "SrodError.pb.h"
#include "SrodPipeVideoDefine.pb.h"
#include "MediaFactory.h"

bool IMediaPlayer::m_enableHardwareAcceleration = false;
IMediaPlayer* MediaFactory::createPlayer()
{
    return new SrodPlayer();
}

SrodPlayer::SrodPlayer()
    : m_cbStatus(nullptr)
    , m_dwUser(0)
    , m_decoder(nullptr)
    , m_render(nullptr)
    , m_muxer(nullptr)
    , m_capturer(nullptr)
    , m_overlay(nullptr)
    , m_ThreadStop(false)
    , m_TimeStamp(0)
    , m_LastTimeStamp(0)
    , m_OsdSrcWidth(960)
    , m_OsdSrcHeight(540)
    , m_Close(true)
    , m_NoDataCnt(0)
{
    ThreadStart();
}

SrodPlayer::~SrodPlayer(void)
{
    ThreadStop();
}

void SrodPlayer::setPlayWnd(long long p_playWnd)
{
    if (0 == p_playWnd)
        return;
    g_enableHardwareAcceleration = IMediaPlayer::m_enableHardwareAcceleration;
    m_render = std::make_shared<SrodRender>((void*)p_playWnd);
}

void SrodPlayer::setCBPlayStatus(lpMediaStatusCallback p_cbStatus, void* p_dwUser)
{
    m_cbStatus = p_cbStatus;
    m_dwUser = p_dwUser;
}

void SrodPlayer::setStretch(bool p_bStretch)
{
    if (nullptr == m_render)
        return;
    m_render->setStretch(p_bStretch);
}

void SrodPlayer::resizeWindow(int p_width, int p_height)
{
    if (nullptr == m_render)
        return;
    m_render->resizeWindow(p_width, p_height);
}

int SrodPlayer::audioOn()
{
    return 0;
}

int SrodPlayer::audioOff()
{
    return 0;
}

int SrodPlayer::setOSD(void* p_videoOSD, int p_len)
{
    if (nullptr == m_overlay)
    {
        m_overlay = std::make_shared<SrodOverlay>();
        m_overlay->setWindow(m_OsdSrcWidth, m_OsdSrcHeight);
    }

    return m_overlay->setOSD(p_videoOSD, p_len);
}

int SrodPlayer::modifyOSD(int p_osdType, const char* p_osdName, const char* p_newText)
{
    if (nullptr == m_overlay)
        return Srod::Error::SROD_ERR_NOT_READY;
    return m_overlay->modifyOSD(p_osdType, p_osdName, p_newText);
}

int SrodPlayer::disableOSD(int p_osdType, int p_disable)
{
    if (nullptr == m_overlay)
        return Srod::Error::SROD_ERR_NOT_READY;
    return m_overlay->disableOSD(p_osdType, p_disable);
}

int SrodPlayer::startRecord(const char* p_file, lpRecordStatusCallback p_cbFunc, void* p_dwUser)
{
    if (nullptr == m_muxer)
        m_muxer = std::make_shared<SrodMuxer>();

    if (m_overlay)
    {
        if (m_overlay->isRecording())
            return Srod::Error::SROD_ERR_IN_USE;
        m_overlay->activateOSD(Srod::PipeVideo::VIDEO_OSD_TYPE_TITLES, true);
    }

    int nRet = m_muxer->startRecord(p_file, p_cbFunc, p_dwUser);
    if (Srod::Error::SROD_ERR_SUCCESS != nRet)
    {
        m_overlay->activateOSD(Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO, true);
        return nRet;
    }

    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodPlayer::pauseRecord(int p_pause)
{
    //录制片头片尾过程中不能暂停
    if (m_overlay)
    {
        switch (m_overlay->getOSDType())
        {
        case Srod::PipeVideo::VIDEO_OSD_TYPE_TITLES:
        case Srod::PipeVideo::VIDEO_OSD_TYPE_TRAILER:
            return Srod::Error::SROD_ERR_FAILED;
        }
    }
    if (m_muxer)
        return m_muxer->pauseRecord(p_pause);

    return Srod::Error::SROD_ERR_THREAD_STOP;
}

int SrodPlayer::stopRecord(bool p_forceStop)
{
    if (m_overlay)
    {
        if (p_forceStop)
            m_overlay->activateOSD(Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO, false);
        else
            m_overlay->activateOSD(Srod::PipeVideo::VIDEO_OSD_TYPE_TRAILER, true);
    }
    else
    {
        if (m_muxer)
            return m_muxer->stopRecord(p_forceStop);
    }

    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodPlayer::snapshot(const char* p_file)
{
    if (nullptr == m_capturer)
        m_capturer = std::make_shared<SrodCapturer>();

    return m_capturer->snapshot(p_file);
}

int SrodPlayer::setWindow(int p_width, int p_height)
{
    m_OsdSrcWidth = p_width;
    m_OsdSrcHeight = p_height;
    return Srod::Error::SROD_ERR_SUCCESS;
}

void SrodPlayer::close()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    if (m_overlay != nullptr)
        m_overlay = nullptr;
    if (m_capturer != nullptr)
        m_capturer = nullptr;
    if (m_muxer != nullptr)
        m_muxer = nullptr;
    if (m_render != nullptr)
    {
        m_render->close();
        m_render = nullptr;
    }
    if (m_decoder != nullptr)
    {
        m_decoder->uninitFfmpeg();
        m_decoder = nullptr;
    }
}

void SrodPlayer::ThreadStart()
{
    m_Thread = new std::thread(&SrodPlayer::ThreadFunc, this);
    m_ThreadStop = false;
    m_Thread->detach();
}

void SrodPlayer::ThreadStop()
{
    if (m_Thread == nullptr)
        return;
    m_ThreadStop = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    delete m_Thread;
    m_Thread = nullptr;
}

void SrodPlayer::consumeFrame(void* p_srodFrame)
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    SrodFrame* srodFrame = (SrodFrame*)p_srodFrame;
    if (STREAM_AUDIO == srodFrame->_head._streamType)
        return;

    if (nullptr == m_decoder)
        m_decoder = std::make_shared<SrodDecoder>();
    int nRet = m_decoder->decode(p_srodFrame);
    if (Srod::Error::SROD_ERR_SUCCESS != nRet)
        return;
    m_TimeStamp = srodFrame->_head._timestamp;
    AVFrame* avFrame = m_decoder->getYUV();
    avFrame->pkt_dts = srodFrame->_head._timestamp;

    AVFrame* dstFrame = avFrame;
    if (m_overlay)
    {
        m_overlay->recount(srodFrame->_head._frameRate);
        m_overlay->overlay(avFrame, nullptr, &dstFrame);
        if (m_muxer && !m_overlay->isRecording())
            m_muxer->stopRecord(false);
    }
    if (m_render)
        m_render->play(dstFrame->data, dstFrame->linesize, srodFrame->_head._imageWidth, srodFrame->_head._imageHeight);

    if (m_capturer)
        m_capturer->writeFrame(dstFrame);

    if (m_muxer)
        m_muxer->writeFrame(dstFrame);
}

void SrodPlayer::ThreadFunc()
{
    while (!m_ThreadStop)
    {
        if (m_TimeStamp == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }
        if (m_TimeStamp != m_LastTimeStamp)
        {
            m_LastTimeStamp = m_TimeStamp;
            m_NoDataCnt = 0;
        }
        else
        {
            if (++m_NoDataCnt >= 7)
            {
                if (m_cbStatus != nullptr)
                    m_cbStatus((long long)this, -1, m_dwUser);
                m_NoDataCnt = 0;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return;
}

