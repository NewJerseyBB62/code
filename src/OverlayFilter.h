#ifndef _OVERLAYFILTER_H_
#define _OVERLAYFILTER_H_
extern "C" {
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"
}
#include <memory>
#include <string>
#include <map>

namespace Srod
{
    namespace PipeVideo
    {
        class VideoOSD;
        enum VIDEO_OSD_TYPE;
    }
}
using VideoOsd_Ptr = std::shared_ptr<Srod::PipeVideo::VideoOSD>;
using OsdIndexMap = std::map<std::string, int>;

class OverlayFilter
{
public:
    OverlayFilter(VideoOsd_Ptr p_osd);
    virtual ~OverlayFilter(void);

    void setOsdType(Srod::PipeVideo::VIDEO_OSD_TYPE p_type);
    int getOsdType();
    void disable(bool p_disable);
    int modifyOSD(const char* p_osdName, const char* p_newText);

    void recount(int p_frameRate);
    bool checkOverlayCnt();
    void makeZero();

    int init(AVFrame* p_srcFrame);
    void close();
    void overlay(AVFrame* p_srcFrame, unsigned char* p_dstBuff, AVFrame** p_dstFrame);
    void setWindow(int p_width, int p_height);
private:
    int apostrophe(std::string& p_test);
    std::string CN2Utf8(const char* szU8);

    VideoOsd_Ptr               m_videoOSD;
    OsdIndexMap                m_indexMap;
    bool                       m_bDisable;    //禁用标识
    int                        m_nOverlayCnt; //叠加计数

    AVFrame*                   m_frameOut;
    AVFilterContext*           m_filterCtxSink;
    AVFilterContext*           m_filterCtxSrc;
    AVFilterGraph*             m_filterGraph;
    Srod::PipeVideo::VIDEO_OSD_TYPE m_OSDType;
    std::map<std::string, std::string> m_headOSD;
    int m_OsdWidth;
    int m_OsdHeight;
private:
    OverlayFilter(const OverlayFilter& ) = delete;
    OverlayFilter& operator=(const OverlayFilter& ) = delete;
};

#endif //_OVERLAYFILTER_H_