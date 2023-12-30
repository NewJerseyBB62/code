#ifndef _SROD_MUXER_H_
#define _SROD_MUXER_H_

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include "SrodCallback.h"
#include "mediacommon.h"
#include "SrodMemPool.h"

using PThread = std::shared_ptr<std::thread>;

class SrodMuxer
{
public:
    SrodMuxer();
    ~SrodMuxer();

    int startRecord(const char* p_file, lpRecordStatusCallback p_cbFunc, void* p_dwUser);
    int pauseRecord(bool p_pause);
    int stopRecord(int p_forceStop);

    void writeFrame(AVFrame* frameYUV);

private:
    void run();

    int init();
    int openMp4();
    int writeMp4(const char* yuvBuff);
    int closeMp4();

private:
    std::atomic<int>          m_status;      //录像控制标记
    std::string               m_szRecordFile; //录像文件
    lpRecordStatusCallback    m_cbFunc;
    void*                     m_dwUser;

    PMemPool                m_memPool;
    SrodMemQueue            m_memQueue;
    PThread                 m_thread;

    AVFrame                 m_frameYUV;                 //帧信息
    int                     m_nFrameRate;               //帧率
    EncodingType            m_encodingType;             //录像编码类型
    bool                    m_bFrameInit;               //初始化标记
    bool                    m_bInitFlag;                //初始化标记

    AVCodec*                m_codec;
    AVCodecContext*         m_codecCtx;
    AVFormatContext*        m_formatCtx;
    AVPacket                m_pkt;
    int64_t                 m_nFrameIndex;
};


#endif //_SROD_MUXER_H_

