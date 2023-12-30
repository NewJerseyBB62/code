#include "OverlayFilter.h"
extern "C" {
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libavutil/opt.h"
}
#include "SrodPipeVideoDefine.pb.h"
#include "SrodError.pb.h"
#include "logger.h"
#include "windows.h"
#include "iostream"
#include "string"
#include "codecvt"

OverlayFilter::OverlayFilter(VideoOsd_Ptr p_osd)
    : m_videoOSD(p_osd)
    , m_nOverlayCnt(0)
    , m_bDisable(false)
    , m_frameOut(nullptr)
{
    m_headOSD["task_name"] = "任务名称\\\\:";
    m_headOSD["task_number"] = "任务编号\\\\:";
    m_headOSD["inspect_location"] = "检测地点\\\:";
    m_headOSD["inspect_org"] = "检测单位\\\:";
    m_headOSD["inspector"] = "检测人员\\\:";
    m_headOSD["inspect_date"] = "检测日期\\\\:";
    m_headOSD["inspect_direction"] = "检测方向\\\:";
    m_headOSD["start_manhole_code"] = "起始井号\\\\:";
    m_headOSD["end_manhole_code"] = "结束井号\\\\:";
    m_headOSD["manhole_start_depth"] = "沙井深度\\\\:";
    m_headOSD["pipe_type"] = "管道类型\\\\:";
    m_headOSD["pipe_matrial"] = "管道材料\\\\:";
    m_headOSD["pipe_diameter"] = "管径\\\\:";
    m_headOSD["pipe_length"] = "管道长度\\\\:";
    m_headOSD["longitude"] = "经度\\\\:";
    m_headOSD["latitude"] = "纬度\\\\:";
    m_headOSD["altitude"] = "海拔\\\\:";
    m_headOSD["remark"] = "备注\\\\:";
    m_headOSD["time"] = "";
    m_headOSD["distance"] = "计米距离\\\\:";
    m_headOSD["speed"] = "速度\\\\:";
    m_headOSD["slope"] = "坡度\\\\:";
    m_headOSD["zoom"] = "倍数\\\\:";
    m_headOSD["title"] = "";
}

OverlayFilter::~OverlayFilter(void)
{
    //log("./player.log", "%s %d %s\n", __FUNCTION__, __LINE__, "release OverlayFilter");
}

void OverlayFilter::setOsdType(Srod::PipeVideo::VIDEO_OSD_TYPE p_type)
{
    m_OSDType = p_type;
    if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TITLES)
        m_headOSD["title"] = "起始录像";
    else if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TRAILER)
        m_headOSD["title"] = "结束录像";
}

int OverlayFilter::getOsdType()
{
    return m_OSDType;
}

void OverlayFilter::disable(bool p_disable)
{
    m_bDisable = p_disable;
}

int OverlayFilter::modifyOSD(const char* p_osdName, const char* p_newText)
{
    if (NULL == m_frameOut)
        return Srod::Error::SROD_ERR_SUCCESS;
    /*{
        auto osds = m_videoOSD->mutable_osds();
        auto iter = osds->find(p_osdName);
        if (osds->end() == iter)
            return Srod::Error::SROD_ERR_NOT_FOUND;
        iter->second.set_text(p_newText);
        return Srod::Error::SROD_ERR_SUCCESS;
    }*/

    auto iter = m_indexMap.find(p_osdName);
    if (m_indexMap.end() == iter)
        return Srod::Error::SROD_ERR_NOT_FOUND;

    int index = iter->second + 2;
    if (index >= m_filterGraph->nb_filters)
        return Srod::Error::SROD_ERR_INVALID_PARAM;

    AVFilterContext* filter_ctx1 = m_filterGraph->filters[index];
    av_opt_set(filter_ctx1->priv, "text", p_newText, 0);
    return Srod::Error::SROD_ERR_SUCCESS;
}

void OverlayFilter::recount(int p_frameRate)
{
    int effective = 0;
    if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TITLES)
        effective = m_videoOSD->head_effective();
    else if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO)
        effective = m_videoOSD->body_effective();
    else if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TRAILER)
        effective = m_videoOSD->tail_effective();
    m_nOverlayCnt = effective * p_frameRate;
}

bool OverlayFilter::checkOverlayCnt()
{
    if (Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO == m_OSDType)
        return true;

    if (m_bDisable)
        return true;

    if (m_nOverlayCnt > 0)
        return true;

    return false;
}

void OverlayFilter::makeZero()
{
    m_nOverlayCnt = 0;
}

int OverlayFilter::init(AVFrame* p_srcFrame)
{
    int nPos = 0;

    //avfilter_register_all();

#if 0
    av_log_set_level(AV_LOG_DEBUG);
    av_log_set_flags(AV_LOG_SKIP_REPEATED);
    av_log_set_callback(libffmpeg_log_callback);
#endif

    char args[512] = {0};
    const AVFilter* buffersrc  = avfilter_get_by_name("buffer");
    const AVFilter* buffersink = avfilter_get_by_name("buffersink");
    AVFilterInOut* outputs = avfilter_inout_alloc();
    AVFilterInOut* inputs  = avfilter_inout_alloc();
    static enum AVPixelFormat pix_fmts[] = { AV_PIX_FMT_YUV420P, AV_PIX_FMT_NONE };
    AVBufferSinkParams* buffersink_params;

    m_filterGraph = avfilter_graph_alloc();

    /* buffer video source: the decoded frames from the decoder will be inserted here. */
    snprintf(args, sizeof(args), "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
             p_srcFrame->width, p_srcFrame->height, p_srcFrame->format, 1, 25, 1, 1);

    int ret = avfilter_graph_create_filter(&m_filterCtxSrc, buffersrc, "in", args, NULL, m_filterGraph);
    if (ret < 0)
    {
        char errbuf[1024] = { 0 };
        int nLen = av_strerror(ret, errbuf, 1024);
        log("player.log", "%s %d avfilter_graph_create_filter %s args:%s\n", __FUNCTION__, __LINE__, errbuf, args);
        return ret;
    }

    /* buffer video sink: to terminate the filter chain. */
    buffersink_params = av_buffersink_params_alloc();
    buffersink_params->pixel_fmts = pix_fmts;
    ret = avfilter_graph_create_filter(&m_filterCtxSink, buffersink, "out", NULL, buffersink_params, m_filterGraph);
    av_free(buffersink_params);
    if (ret < 0)
    {
        char errbuf[1024] = { 0 };
        int nLen = av_strerror(ret, errbuf, 1024);
        log("player.log", "%s %d avfilter_graph_create_filter %s\n", __FUNCTION__, __LINE__, errbuf);
        return ret;
    }

    /* Endpoints for the filter graph. */
    outputs->name       = av_strdup("in");
    outputs->filter_ctx = m_filterCtxSrc;
    outputs->pad_idx    = 0;
    outputs->next       = NULL;

    inputs->name       = av_strdup("out");
    inputs->filter_ctx = m_filterCtxSink;
    inputs->pad_idx    = 0;
    inputs->next       = NULL;

    char filter_image_descr[1024 * 5] = {0};
    nPos = 0;
    //nPos += sprintf(filter_image_descr + nPos, "[in]drawtext=fontfile=simfang.ttf:fontcolor=white:fontsize=30:text='%%{localtime}':x=w-tw:y=0[t1];[t1]drawtext=fontfile=simfang.ttf:fontcolor=white:fontsize=30:x=0:y=300:text='HelloWorld'[t2]");

    /*
    字幕转义字符规则
    单引号中的 " : \ % 转义字符
      \"
      \\:
      \\\\
      \\\\%
    单引号 ' 只能在通过无引号方式输出 转义字符为 \\\\\\'
    */
    nPos += sprintf(filter_image_descr + nPos, "[in]");
    auto osds = m_videoOSD->osds();
    Srod::PipeVideo::OsdFont font;
    if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TITLES)
        font = m_videoOSD->head_font();
    else if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO)
        font = m_videoOSD->body_font();
    else if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TRAILER)
        font = m_videoOSD->tail_font();
    int index = 0;
    for (auto iter = osds.begin(); iter != osds.end(); ++iter)
    {
        auto osdField = iter->second;
        int enable = 1;
        if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TITLES)
            enable = osdField.enable() & 0x01;
        else if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO)
            enable = osdField.enable() & 0x02;
        else if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TRAILER)
            enable = osdField.enable() & 0x04;
        if (enable == 0)
            continue;

        if (index)
            nPos += sprintf(filter_image_descr + nPos, "[t%d];[t%d]", index - 1, index - 1);

        nPos += sprintf(filter_image_descr + nPos, "drawtext=");
        if (!font.file().empty())
            nPos += sprintf(filter_image_descr + nPos, "fontfile=%s:fontcolor=#%s:fontsize=%d:",
                            font.file().c_str(), font.color().c_str(), font.size());


        Srod::PipeVideo::OSDPosition position;
        if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TITLES)
            position = osdField.head_pos();
        else if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO)
            position = osdField.body_pos();
        else if (m_OSDType == Srod::PipeVideo::VIDEO_OSD_TYPE_TRAILER)
            position = osdField.tail_pos();
        int nWidth, nHeight;
        float scaleW = position.x() / (m_OsdWidth + 0.0);
        float scaleH = position.y() / (m_OsdHeight + 0.0);
        nWidth = scaleW * p_srcFrame->width;
        nHeight = scaleH * p_srcFrame->height;
        if (Srod::PipeVideo::OSD_FIELD_TIME == osdField.type())
            nPos += sprintf(filter_image_descr + nPos, "text='%%{localtime}':x=%d:y=%d", nWidth, nHeight);
        else if (Srod::PipeVideo::OSD_FIELD_TEXT == osdField.type())
        {
            std::string head = m_headOSD[iter->first];
            if (iter->first != "title")
                head += osdField.text();
            //apostrophe(strTest);
            nPos += sprintf(filter_image_descr + nPos, "text=%s:x=%d:y=%d", head.c_str(), nWidth, nHeight);
        }
        m_indexMap.insert(std::make_pair(iter->first, index++));
    }
    nPos += sprintf(filter_image_descr + nPos, "[out]");

    if ((ret = avfilter_graph_parse_ptr(m_filterGraph, filter_image_descr, &inputs, &outputs, NULL)) < 0)
    {
        char errbuf[1024] = {0};
        int nLen = av_strerror(ret, errbuf, 1024);
        log("player.log", "%s %d %s\n", __FUNCTION__, __LINE__, errbuf);
        return ret;
    }

    if ((ret = avfilter_graph_config(m_filterGraph, NULL)) < 0)
    {
        char errbuf[1024] = {0};
        int nLen = av_strerror(ret, errbuf, 1024);
        log("player.log", "%s %d %s\n", __FUNCTION__, __LINE__, errbuf);
        return ret;
    }

    m_frameOut = av_frame_alloc();
    //av_image_fill_arrays(m_frameOut->data, m_frameOut->linesize, dstBuff, (AVPixelFormat)srcFrame->format, srcFrame->width, srcFrame->height, 1);

    for (int i = 0; i < m_filterGraph->nb_filters; i++)
    {
        AVFilterContext* filter_ctxn = m_filterGraph->filters[i];
        //log("player.log", "%s %d %2d %s\n", __FUNCTION__, __LINE__, i, filter_ctxn->name);
    }
    return 0;
}

void OverlayFilter::close()
{
    if (NULL == m_filterGraph)
        return;
    av_frame_free(&m_frameOut);
    avfilter_graph_free(&m_filterGraph);
    m_frameOut = NULL;
    m_filterGraph = NULL;
}

void OverlayFilter::overlay(AVFrame* p_srcFrame, unsigned char* p_dstBuff, AVFrame** p_dstFrame)
{
    *p_dstFrame = p_srcFrame;
    if (m_bDisable)
        return;

    if (NULL == m_frameOut)
        init(p_srcFrame);
    else
        av_frame_unref(m_frameOut);

    int nRet = av_buffersrc_add_frame_flags(m_filterCtxSrc, p_srcFrame, AV_BUFFERSRC_FLAG_KEEP_REF);
    if (nRet < 0)
    {
        char szErr[AV_ERROR_MAX_STRING_SIZE] = { 0 };
        av_make_error_string(szErr, AV_ERROR_MAX_STRING_SIZE, nRet);
        log("player.log", "%s %d err:%d %s\n", __FUNCTION__, __LINE__, nRet, szErr);
        return;
    }

    /* pull filtered pictures from the filtergraph */
    nRet = av_buffersink_get_frame(m_filterCtxSink, m_frameOut);
    if (nRet < 0)
    {
        char szErr[AV_ERROR_MAX_STRING_SIZE] = { 0 };
        av_make_error_string(szErr, AV_ERROR_MAX_STRING_SIZE, nRet);
        log("player.log", "%s %d err:%d %s\n", __FUNCTION__, __LINE__, nRet, szErr);
        return;
    }
    *p_dstFrame = m_frameOut;

    if (Srod::PipeVideo::VIDEO_OSD_TYPE_VIDEO == m_OSDType)
        return ;

    m_nOverlayCnt--;
    //av_frame_unref(frame_out);
}

void OverlayFilter::setWindow(int p_width, int p_height)
{
    m_OsdWidth = p_width;
    m_OsdHeight = p_height;
}

int OverlayFilter::apostrophe(std::string& p_test)
{
    /*int srcLen = p_test.length();
    if (srcLen <= 0)
    {
        p_test.append("");
        return -1;
    }

    std::list<int> indexList;
    int nIndex = 0;
    int nLastIndex = 0;

    while (1)
    {
        int nRet = p_test.find('\'', nIndex);
        if (nRet < 0)
            break;
        indexList.push_back(nRet);
        nIndex = nRet + 1;
    }

    if (indexList.size() <= 0)
    {
        p_test.insert(0, 1, '\'');
        p_test.append("'");
        return 0;
    }

    auto it = --indexList.end();
    for (int i = 0; i < indexList.size(); i++)
    {
        p_test.replace(*it, 1, "\\\\\\'");
        if (it != indexList.begin())
            it--;
    }

    auto it1 = indexList.begin();
    int nLast = -1;
    int addcnt = 0;
    for (int i = 0; i < indexList.size(); i++)
    {
        if (*it1 == 0)
        {
            nLast = *it1;
            it1++;
            continue;
        }

        if (i == indexList.size() - 1 && *it1 < srcLen - 1)
        {
            int len = srcLen - *it1 - 1;
            int idx = p_test.length() - len;
            p_test.insert(idx, 1, '\'');
            p_test.append("'");
        }
        int currIdx = (i * 3) + *it1 + addcnt;
        p_test.insert(currIdx, 1, '\'');
        p_test.insert((i * 3) + nLast + 1 + addcnt, 1, '\'');

        addcnt += 2;
        nLast = *it1;
        it1++;
    }*/
    return 1;
}

std::string OverlayFilter::CN2Utf8(const char* szU8)
{
    return "";
}