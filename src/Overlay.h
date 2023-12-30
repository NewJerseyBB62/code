#ifndef _SRODOVERLAY_H_
#define _SRODOVERLAY_H_

extern "C" {
#include "libavcodec/avcodec.h"
}
#include <memory>
#include <map>
#include "OverlayFilter.h"
#include <mutex>

class OverlayFilter;
using OverlayFilter_Ptr = std::shared_ptr<OverlayFilter>;
using OverlayFilterMap = std::map<int, OverlayFilter_Ptr>;

class SrodOverlay
{
public:
    SrodOverlay(void);
    virtual ~SrodOverlay(void);

    int setOSD(void* p_videoOSD, int p_len);
    int modifyOSD(int p_osdType, const char* p_osdName, const char* p_newText);
    int disableOSD(int p_osdType, int p_disable);

    bool activateOSD(int p_osdType, bool p_bRecording);
    int getOSDType();
    bool isRecording();

    void recount(int p_frameRate);
    void overlay(AVFrame* p_srcFrame, unsigned char* p_dstBuff, AVFrame** p_dstFrame);
    void setWindow(int p_width, int p_height);
private:
    SrodOverlay(const SrodOverlay& ) = delete;
    SrodOverlay& operator=(const SrodOverlay& ) = delete;

    OverlayFilterMap        m_overlayMap;
    OverlayFilter_Ptr       m_workingFilter;
    bool                    m_bRecording;
    int                     m_nFrameRate;
    int                     m_nOsdWidth;
    int                     m_nOsdHeight;
    VideoOsd_Ptr m_osd;
	std::mutex				m_Mutex;
};

#endif //_SRODOVERLAY_H_