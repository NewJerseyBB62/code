#ifndef _QCAPMEDIASOURCE_H_
#define _QCAPMEDIASOURCE_H_

#include <string>
#include "mediacommon.h"
#include "IMediaSource.h"
#include <windows.h>
#include "QCAP.H"
#include <mutex>

#define W_QCAP 0
#define R_QCAP 0

#include <thread>
using Thread_Ptr = std::shared_ptr<std::thread>;

class QcapMediaSource : public IMediaSource
{
public:
    QcapMediaSource(void);
    virtual ~QcapMediaSource(void);

    virtual int init(const char* p_url, const char* p_user, const char* p_pwd, int p_streamID);
    virtual void uninit();
    virtual int openStream(CallbackFrame p_cbFrame, void* p_dwUser);
    virtual int closeStream(void* p_dwUser);

private:
    QcapMediaSource(const QcapMediaSource& ) = delete;
    QcapMediaSource& operator=(const QcapMediaSource& ) = delete;

    static QRETURN QCAP_EXPORT callbackVideoPreview(PVOID pDevice /*IN*/, double dSampleTime /*IN*/, BYTE* pFrameBuffer /*IN*/, ULONG nFrameBufferLen /*IN*/, PVOID pUserData /*IN*/);
    void callbackVideoPreview(PVOID pDevice /*IN*/, double dSampleTime /*IN*/, BYTE* pFrameBuffer /*IN*/, ULONG nFrameBufferLen /*IN*/);

    void run();

private:
    std::string		    m_strUri;
    std::string		    m_user;
    std::string		    m_pwd;
    void*               m_videoDevice;
    SrodFrame           m_frame;
    CallbackFrame		m_cbFrame;
    void*			    m_dwUser;
    std::mutex			m_StopMutex;

#if W_QCAP
    FILE*               m_pf;
    int                 m_nCnt;
#endif
#if R_QCAP
    FILE*               m_pf;
    Thread_Ptr          m_thread;
    bool                m_bRun;
#endif
};

#endif //_QCAPMEDIASOURCE_H_