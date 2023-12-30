#ifndef _SRODDECODER_H_
#define _SRODDECODER_H_

#include "mediacommon.h"
extern "C" {
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
}

class SrodDecoder
{
public:
    SrodDecoder(void);
    virtual ~SrodDecoder(void);

    int decode(const void* p_SRODFrame);
    AVFrame* getYUV();
    void uninitFfmpeg();
private:
    int initFfmpeg(EncodingType p_encodingType);
    int ffmpegDecode(unsigned char* avpkt_data, int avpkt_size);

private:
    SrodDecoder(const SrodDecoder& ) = delete;
    SrodDecoder& operator=(const SrodDecoder& ) = delete;

    EncodingType	m_encodingType;
    AVCodec*		m_codec;
    AVCodecContext* m_codecCtx;
    AVFrame*		m_frameYUV;
};

#endif //_SRODDECODER_H_