#ifndef _USR_COMMON_CONST_H_
#define _USR_COMMON_CONST_H_

#include <memory.h>

#if (defined(WIN32) || defined(_WIN32_WCE))
struct iovec
{
    void* iov_base;	/* Pointer to data.  */
    size_t iov_len;	/* Length of data.  */
};

#ifndef CALL_METHOD
    #define CALL_METHOD	__stdcall  //__cdecl
#endif

typedef __int64				INT64;

#define SPLIT_CHAR			'\\'

#define strcasecmp _stricmp
//	#define snprintf _snprintf

#define MSG_NOSIGNAL 0

#else
#ifndef CALL_METHOD
    #define CALL_METHOD
#endif

typedef long long			INT64;
typedef unsigned long	        HANDLE;

#define SPLIT_CHAR			'/'

#define _strncasecmp strncasecmp
#define strtok_s     strtok_r

#ifndef MAX_PATH
    #define MAX_PATH          260
#endif
#endif

typedef unsigned int        uint;
typedef unsigned short      ushort;
typedef unsigned char       uchar;
typedef unsigned long	    ulong;

#define CACHE_1M	        		1048576				//1M缓存
#define CACHE_512K                  524288              //512k缓存         

#define MAX_MEDIA_FRAME_TIMESTAMP	0x7FFFFFFFFFFFFFFF	//INT64存放的最大值

#define MAX_ROBOT_MSG_LEN			10240

#define MAX_LENGTH_IP		48							//IP地址最大长度

#define FILE_BUFF_SIZE		10240						//文件传输缓存，10 k

#define UNS_ZERO(entity)    memset(&entity, 0, sizeof(entity))

#define BLANK_SPACE_SEC			5		//录像空白区域，单位：秒
#define BLANK_SPACE_MSEC		(5000)	//录像空白区域，单位：毫秒

#define Second_2_MicroSec	1000000	//秒转微秒(1 * 1000 * 1000)
#define Millisec_2_Microsec 1000	//毫秒秒转微秒
#define Sec_2_Millisec      1000    //秒转毫秒

/*************************************************
概    述：SDK连接状态回调
参    数：errCode [in] 连接错误码
          connectCount [in] 连接次数
          dwUser [in] 用户数据
说    明：回调中不要做复杂逻辑
**************************************************/
typedef void (CALL_METHOD* funcCallbackConnectStatus)(int errCode, unsigned int connectCount, unsigned long dwUser);

/*************************************************
概    述：消息回调
参    数：cmdID [in] 命令编号
          inParam [in] 请求参数
          inParamLen [in] 请求参数的长度
          outParam [out] 应答参数
          outParamSize [in] 应答参数的缓冲大小
          dwUser [in] 用户数据
**************************************************/
typedef int (CALL_METHOD* funcCallbackHandleMessage)(unsigned int cmdID, void* inParam, unsigned short inParamLen, void* outParam, unsigned short outParamSize, unsigned long dwUser);

/*************************************************
概    述：文件传输的消息回调
参    数：status [in] 0 表示成功，小于 0 表示传输出错的错误码
          transmittalLen [in] 已传输的数据长度
          totalLen [in] 文件总长
          dwUser [in] 用户数据
**************************************************/
typedef void (CALL_METHOD* funcCallbackFileTransfer)(int status, uint transmittalLen, uint totalLen, unsigned long dwUser);

/*************************************************
概    述：流媒体状态回调
参    数：playWnd [in] 播放窗口
          errCode [in] 错误码
          dwUser [in] 用户数据
**************************************************/
typedef void (CALL_METHOD* funcCallbackMediaStatus)(unsigned long playWnd, int errCode, unsigned long dwUser);

/*************************************************
概    述：播放状态回调
参    数：playWnd [in] 播放窗口
          errCode [in] 错误码
          dwUser [in] 用户数据
**************************************************/
typedef void (CALL_METHOD* funcCBPlayStatus)(unsigned long playWnd, int errCode, unsigned long dwUser);

/*************************************************
概    述：回放状态回调
参    数：errCode [in] 错误码
          channelID [in] 通道号
          playSecond [in] 当前回放时间，秒
          dwUser [in] 用户数据
**************************************************/
typedef void (CALL_METHOD* funcCBPlaybackStatus)(int errCode, ushort channelID, uint playSecond, unsigned long dwUser);

typedef void (CALL_METHOD* funcCBMediaStatus)(char* robotID, ushort channelID, ushort streamID, int status, ulong dwUser);

struct TsRobotMediaStatus;
typedef void (CALL_METHOD* funcCBMediaStatusV2)(TsRobotMediaStatus* status, ulong dwUser);

/*!
@brief  录像状态回调
@param  [in] status 录像状态
@param  [in] dwUser 用户数据
@note
*         录像状态                       | 描述
*         ------------------------------|------
*         USR_ERR_RECORD_BEGIN          | 录像开始
*         USR_ERR_RECORD_AT_BLANK_SPACE | 录像无数据
*         USR_ERR_RECORD_FAILED         | 录像失败
*         USR_ERR_RECORD_STOP           | 录像停止
*/
typedef void (CALL_METHOD* funcCBRecordStatus)(int status, ulong dwUser);

typedef void (CALL_METHOD* funcCBStreamYUV)(uchar* yuv, int* linesize, int width, int height, int& record, char* file, ulong dwUser);

/*************************************************
概    述：播放格式化回调
参    数：width [in] 图像宽
         height [in] 图像高
说   明：回调中需要分配足够的解码数据空间，width * height * 4
**************************************************/
typedef unsigned long (CALL_METHOD* funcCallbackFormat)(unsigned int width, unsigned int height);
/*************************************************
概    述：获取解码空间回调
返 回 值：解码数据空间首地址
**************************************************/
typedef unsigned long (CALL_METHOD* funcCallbackGetCache)();
/*************************************************
概    述：播放回调
返 回 值：播放状态
说    明：后台解码完成后通知界面播放
**************************************************/
typedef int (CALL_METHOD* funcCallbackDisplay)();

#endif //_USR_COMMON_CONST_H_