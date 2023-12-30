#ifndef _SRODPLAYER_H_
#define _SRODPLAYER_H_

#include "IMediaPlayer.h"
#include <memory>
#include <thread>
#include <mutex>

class SrodDecoder;
class SrodRender;
class SrodMuxer;
class SrodOverlay;
class SrodCapturer;
using SrodDecoder_Ptr = std::shared_ptr<SrodDecoder>;
using SrodRender_Ptr = std::shared_ptr<SrodRender>;
using SrodMuxer_Ptr = std::shared_ptr<SrodMuxer>;
using SrodOverlay_Ptr = std::shared_ptr<SrodOverlay>;
using SrodCapturer_Ptr = std::shared_ptr<SrodCapturer>;

class SrodPlayer : public IMediaPlayer
{
public:
    SrodPlayer();
    virtual ~SrodPlayer(void);

    virtual void setPlayWnd(long long p_playWnd);
    virtual void setCBPlayStatus(lpMediaStatusCallback p_cbStatus, void* p_dwUser);
    virtual void setStretch(bool p_bStretch);
    virtual void resizeWindow(int p_width, int p_height);
    virtual int audioOn();
    virtual int audioOff();

    virtual int setOSD(void* p_videoOSD, int p_len);
    virtual int modifyOSD(int p_osdType, const char* p_osdName, const char* p_newText);
    virtual int disableOSD(int p_osdType, int p_disable);

    virtual int startRecord(const char* p_file, lpRecordStatusCallback p_cbFunc, void* p_dwUser);
    virtual int pauseRecord(int p_pause);
    virtual int stopRecord(bool p_forceStop);

    virtual int snapshot(const char* p_file);
    virtual int setWindow(int p_width, int p_height);

    virtual void close();


private:
    virtual void consumeFrame(void* p_srodFrame);
    void ThreadStart();
    void ThreadStop();
    void ThreadFunc();

private:
    SrodPlayer(const SrodPlayer& ) = delete;
    SrodPlayer& operator=(const SrodPlayer& ) = delete;

private:
    lpMediaStatusCallback       m_cbStatus;
    void*                       m_dwUser;

    SrodDecoder_Ptr      m_decoder;     //解码器
    SrodRender_Ptr       m_render;      //渲染器
    SrodOverlay_Ptr      m_overlay;     //叠加器
    SrodMuxer_Ptr        m_muxer;       //封装器
    SrodCapturer_Ptr     m_capturer;    //抓拍器
    std::thread*	       m_Thread;
    bool                 m_ThreadStop;
    long long            m_TimeStamp;
    long long            m_LastTimeStamp;
    int                  m_Count;
    int                  m_OsdSrcWidth;
    int                  m_OsdSrcHeight;
    bool				         m_Close;
    int                  m_RecordCnt;
    int                  m_NoDataCnt;
    std::mutex           m_Mutex;
};
#endif //_SRODPLAYER_H_