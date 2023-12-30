#include "SrodMediaInfo.h"
extern "C" {
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
}
#include <iostream>

int SrodMediaInfo::GetMediaDuration(const char* p_file, long long* p_duration, unsigned char* p_data)
{
    if (p_file == NULL)
    {
        printf("getMp4_duration_filename erro");
        return -1;
    }
    AVFormatContext* ifmt_ctx = NULL;
    AVPacket* pkt = nullptr;
    AVFrame* temp_frame = nullptr;
    SwsContext* sws_ctx = nullptr;
    int ret = 0;
    int videoindex = -1;
    int audioindex = -1;

    ret = avformat_open_input(&ifmt_ctx, p_file, NULL, NULL);
    if (ret < 0)
    {
        char buf[1024] = { 0 };
        av_strerror(ret, buf, sizeof(buf) - 1);
        printf("open %s failed:%s\n", p_file, buf);
        goto failed;
    }
    ret = avformat_find_stream_info(ifmt_ctx, NULL);
    if (ret < 0)
    {
        char buf[1024] = { 0 };
        av_strerror(ret, buf, sizeof(buf) - 1);
        printf("avformat_find_stream_info %s failed:%s\n", p_file, buf);
        goto failed;
    }

    av_dump_format(ifmt_ctx, 0, p_file, 0);

    // duration: 媒体文件时长，单位微妙
    *p_duration = (ifmt_ctx->duration) / AV_TIME_BASE;

    pkt = av_packet_alloc();
    temp_frame = av_frame_alloc();

    for (int i = 0; i < int(ifmt_ctx->nb_streams); i++)
    {
        if (ifmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            AVCodec* codec = avcodec_find_decoder(ifmt_ctx->streams[i]->codecpar->codec_id);
            AVCodecContext* codec_ctx = avcodec_alloc_context3(codec);
            avcodec_parameters_to_context(codec_ctx, ifmt_ctx->streams[i]->codecpar);
            avcodec_open2(codec_ctx, codec, nullptr);
            while (av_read_frame(ifmt_ctx, pkt) >= 0)
            {
                av_frame_unref(temp_frame);
                while ((ret = avcodec_receive_frame(codec_ctx, temp_frame)) == AVERROR(EAGAIN))
                {
                    ret = avcodec_send_packet(codec_ctx, pkt);
                    if (ret < 0)

                        break;
                }

                if (ret < 0 && ret != AVERROR_EOF)
                {
                    std::cout << "Failed to receive packet from decoder." << ret << std::endl;
                    continue;
                }
                sws_ctx = sws_getContext(
                              temp_frame->width,
                              temp_frame->height,
                              static_cast<AVPixelFormat>(temp_frame->format),
                              temp_frame->width,
                              temp_frame->height,
                              static_cast<AVPixelFormat>(AV_PIX_FMT_RGBA),
                              SWS_FAST_BILINEAR,
                              nullptr,
                              nullptr,
                              nullptr
                          );
                int linesize[AV_NUM_DATA_POINTERS];
                linesize[0] = temp_frame->width * 4;

                //生成图片
                unsigned char* data = p_data;
                sws_scale(sws_ctx,
                          temp_frame->data,
                          temp_frame->linesize,
                          0,
                          temp_frame->height,
                          &data,
                          linesize);
                sws_freeContext(sws_ctx);
                avcodec_close(codec_ctx);
                avcodec_free_context(&codec_ctx);
                goto failed;
            }
        }
    }
    //释放资源

failed:
    if (temp_frame)
        av_frame_free(&temp_frame);
    if (pkt)
        av_packet_free(&pkt);
    if (ifmt_ctx)
        avformat_close_input(&ifmt_ctx);
    return 0;
}