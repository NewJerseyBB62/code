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

#define CACHE_1M	        		1048576				//1M����
#define CACHE_512K                  524288              //512k����         

#define MAX_MEDIA_FRAME_TIMESTAMP	0x7FFFFFFFFFFFFFFF	//INT64��ŵ����ֵ

#define MAX_ROBOT_MSG_LEN			10240

#define MAX_LENGTH_IP		48							//IP��ַ��󳤶�

#define FILE_BUFF_SIZE		10240						//�ļ����仺�棬10 k

#define UNS_ZERO(entity)    memset(&entity, 0, sizeof(entity))

#define BLANK_SPACE_SEC			5		//¼��հ����򣬵�λ����
#define BLANK_SPACE_MSEC		(5000)	//¼��հ����򣬵�λ������

#define Second_2_MicroSec	1000000	//��ת΢��(1 * 1000 * 1000)
#define Millisec_2_Microsec 1000	//������ת΢��
#define Sec_2_Millisec      1000    //��ת����

/*************************************************
��    ����SDK����״̬�ص�
��    ����errCode [in] ���Ӵ�����
          connectCount [in] ���Ӵ���
          dwUser [in] �û�����
˵    �����ص��в�Ҫ�������߼�
**************************************************/
typedef void (CALL_METHOD* funcCallbackConnectStatus)(int errCode, unsigned int connectCount, unsigned long dwUser);

/*************************************************
��    ������Ϣ�ص�
��    ����cmdID [in] ������
          inParam [in] �������
          inParamLen [in] ��������ĳ���
          outParam [out] Ӧ�����
          outParamSize [in] Ӧ������Ļ����С
          dwUser [in] �û�����
**************************************************/
typedef int (CALL_METHOD* funcCallbackHandleMessage)(unsigned int cmdID, void* inParam, unsigned short inParamLen, void* outParam, unsigned short outParamSize, unsigned long dwUser);

/*************************************************
��    �����ļ��������Ϣ�ص�
��    ����status [in] 0 ��ʾ�ɹ���С�� 0 ��ʾ�������Ĵ�����
          transmittalLen [in] �Ѵ�������ݳ���
          totalLen [in] �ļ��ܳ�
          dwUser [in] �û�����
**************************************************/
typedef void (CALL_METHOD* funcCallbackFileTransfer)(int status, uint transmittalLen, uint totalLen, unsigned long dwUser);

/*************************************************
��    ������ý��״̬�ص�
��    ����playWnd [in] ���Ŵ���
          errCode [in] ������
          dwUser [in] �û�����
**************************************************/
typedef void (CALL_METHOD* funcCallbackMediaStatus)(unsigned long playWnd, int errCode, unsigned long dwUser);

/*************************************************
��    ��������״̬�ص�
��    ����playWnd [in] ���Ŵ���
          errCode [in] ������
          dwUser [in] �û�����
**************************************************/
typedef void (CALL_METHOD* funcCBPlayStatus)(unsigned long playWnd, int errCode, unsigned long dwUser);

/*************************************************
��    �����ط�״̬�ص�
��    ����errCode [in] ������
          channelID [in] ͨ����
          playSecond [in] ��ǰ�ط�ʱ�䣬��
          dwUser [in] �û�����
**************************************************/
typedef void (CALL_METHOD* funcCBPlaybackStatus)(int errCode, ushort channelID, uint playSecond, unsigned long dwUser);

typedef void (CALL_METHOD* funcCBMediaStatus)(char* robotID, ushort channelID, ushort streamID, int status, ulong dwUser);

struct TsRobotMediaStatus;
typedef void (CALL_METHOD* funcCBMediaStatusV2)(TsRobotMediaStatus* status, ulong dwUser);

/*!
@brief  ¼��״̬�ص�
@param  [in] status ¼��״̬
@param  [in] dwUser �û�����
@note
*         ¼��״̬                       | ����
*         ------------------------------|------
*         USR_ERR_RECORD_BEGIN          | ¼��ʼ
*         USR_ERR_RECORD_AT_BLANK_SPACE | ¼��������
*         USR_ERR_RECORD_FAILED         | ¼��ʧ��
*         USR_ERR_RECORD_STOP           | ¼��ֹͣ
*/
typedef void (CALL_METHOD* funcCBRecordStatus)(int status, ulong dwUser);

typedef void (CALL_METHOD* funcCBStreamYUV)(uchar* yuv, int* linesize, int width, int height, int& record, char* file, ulong dwUser);

/*************************************************
��    �������Ÿ�ʽ���ص�
��    ����width [in] ͼ���
         height [in] ͼ���
˵   �����ص�����Ҫ�����㹻�Ľ������ݿռ䣬width * height * 4
**************************************************/
typedef unsigned long (CALL_METHOD* funcCallbackFormat)(unsigned int width, unsigned int height);
/*************************************************
��    ������ȡ����ռ�ص�
�� �� ֵ���������ݿռ��׵�ַ
**************************************************/
typedef unsigned long (CALL_METHOD* funcCallbackGetCache)();
/*************************************************
��    �������Żص�
�� �� ֵ������״̬
˵    ������̨������ɺ�֪ͨ���沥��
**************************************************/
typedef int (CALL_METHOD* funcCallbackDisplay)();

#endif //_USR_COMMON_CONST_H_