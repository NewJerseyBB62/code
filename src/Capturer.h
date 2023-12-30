#ifndef _SRODCAPTURER_H_
#define _SRODCAPTURER_H_

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}
#include <atomic>

class SrodCapturer
{
public:
    SrodCapturer();
    ~SrodCapturer();

    int snapshot(const char* p_file);
    void writeFrame(AVFrame* frameYUV);

private:
    int saveFile(const char* p_file);
private:
    enum SnapshotStatus
    {
        SNAPSHOT_IDLE = 0,
        SNAPSHOT_START,
        SNAPSHOT_READY
    };
    std::atomic<SnapshotStatus> m_status;      //抓拍控制标记

    char*                   m_frameBuff;
    int                     m_buffSize;
    AVFrame                 m_frameYUV;                 //帧信息
};


#endif //_SRODCAPTURER_H_

