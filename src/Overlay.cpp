#include "SrodOverlay.h"
#include "SrodError.pb.h"
#include "SrodPipeVideoDefine.pb.h"


SrodOverlay::SrodOverlay(void)
    : m_workingFilter(nullptr)
    , m_bRecording(false)
    , m_nFrameRate(0)
    , m_osd(nullptr)
{
}

SrodOverlay::~SrodOverlay(void)
{
	std::lock_guard<std::mutex> lk(m_Mutex);
	m_overlayMap.clear();
}

int SrodOverlay::setOSD(void* p_videoOSD, int p_len)
{
	std::lock_guard<std::mutex> lk(m_Mutex);
    m_osd = std::make_shared<Srod::PipeVideo::VideoOSD>();
    if (!m_osd->ParseFromArray(p_videoOSD, p_len))
        return Srod::Error::SROD_ERR_INVALID_PARAM;
    if (m_overlayMap.size() > 0)
    {
        m_workingFilter = nullptr;
        m_overlayMap.clear();
    }
    for (int t = Srod::PipeVideo::VIDEO_OSD_TYPE_TITLES; t <= Srod::PipeVideo::VIDEO_OSD_TYPE_TRAILER; ++t)
    {
        OverlayFilter_Ptr ptr = std::make_shared<OverlayFilter>(m_osd);
        ptr->setOsdType((Srod::PipeVideo::VIDEO_OSD_TYPE)t);
        ptr->setWindow(m_nOsdWidth, m_nOsdHeight);
        m_overlayMap.emplace(std::make_pair(t, ptr));
        if (nullptr == m_workingFilter && Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO == t)
            m_workingFilter = ptr;
        ptr = nullptr;
    }
    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodOverlay::modifyOSD(int p_osdType, const char* p_osdName, const char* p_newText)
{
    /*auto iter = m_overlayMap.find(p_osdType);
    if (m_overlayMap.end() == iter)
        return Srod::Error::SROD_ERR_NOT_FOUND;
    iter->second->modifyOSD(p_osdName, p_newText);*/
    for (auto iter = m_overlayMap.begin(); iter != m_overlayMap.end(); ++iter)
        iter->second->modifyOSD(p_osdName, p_newText);
    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodOverlay::disableOSD(int p_osdType, int p_disable)
{
    auto iter = m_overlayMap.find(p_osdType);
    if (m_overlayMap.end() == iter)
        return Srod::Error::SROD_ERR_NOT_FOUND;
    iter->second->disable(p_disable);
    return Srod::Error::SROD_ERR_SUCCESS;
}

bool SrodOverlay::activateOSD(int p_osdType, bool p_bRecording)
{
    auto iter = m_overlayMap.find(p_osdType);
    if (m_overlayMap.end() == iter)
        return false;
    iter->second->recount(m_nFrameRate);

    m_workingFilter = iter->second;
    m_bRecording = p_bRecording;
    return true;
}

int SrodOverlay::getOSDType()
{
    if (nullptr == m_workingFilter)
        return Srod::PipeVideo::VIDEO_OSD_TYPE_UNKNOWN;
    return m_workingFilter->getOsdType();
}

bool SrodOverlay::isRecording()
{
    return m_bRecording;
}

void SrodOverlay::recount(int p_frameRate)
{
    if (m_nFrameRate == p_frameRate)
        return;
    m_nFrameRate = p_frameRate;

    if (m_workingFilter)
        m_workingFilter->recount(m_nFrameRate);
}

void SrodOverlay::overlay(AVFrame* p_srcFrame, unsigned char* p_dstBuff, AVFrame** p_dstFrame)
{
	std::lock_guard<std::mutex> lk(m_Mutex);
    if (nullptr == m_workingFilter)
    {
        *p_dstFrame = p_srcFrame;
        return;
    }

    m_workingFilter->overlay(p_srcFrame, p_dstBuff, p_dstFrame);

    if (m_workingFilter->checkOverlayCnt())
        return;

    if (Srod::PipeVideo::VIDEO_OSD_TYPE_TITLES == m_workingFilter->getOsdType())
        activateOSD(Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO, true);
    else if (Srod::PipeVideo::VIDEO_OSD_TYPE_TRAILER == m_workingFilter->getOsdType())
        activateOSD(Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO, false);
}

void SrodOverlay::setWindow(int p_width, int p_height)
{
    m_nOsdWidth = p_width;
    m_nOsdHeight = p_height;
}

