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
    std::atomic<int>          m_status;      //¼����Ʊ��
    std::string               m_szRecordFile; //¼���ļ�
    lpRecordStatusCallback    m_cbFunc;
    void*                     m_dwUser;

    PMemPool                m_memPool;
    SrodMemQueue            m_memQueue;
    PThread                 m_thread;

    AVFrame                 m_frameYUV;                 //֡��Ϣ
    int                     m_nFrameRate;               //֡��
    EncodingType            m_encodingType;             //¼���������
    bool                    m_bFrameInit;               //��ʼ�����
    bool                    m_bInitFlag;                //��ʼ�����

    AVCodec*                m_codec;
    AVCodecContext*         m_codecCtx;
    AVFormatContext*        m_formatCtx;
    AVPacket                m_pkt;
    int64_t                 m_nFrameIndex;
};


#endif //_SROD_MUXER_H_

