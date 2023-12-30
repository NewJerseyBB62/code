#ifndef _TS_UNS_COMMAND_H_
#define _TS_UNS_COMMAND_H_

#include "UsrDomain.h"
#include "CommandConst.h"
/**********************************************************************/
//此处用于控制文件编译字节对齐，拷贝时两行注释间内容需一起拷贝，
//结束处的“恢复默认对齐状态”部分也要一起拷贝，否则win32下pragma pack入栈出栈不匹配
#ifndef WIN32
    #ifndef _PACKED_1_
        #define _PACKED_1_ __attribute__((packed, aligned(1)))    // for gcc
    #endif
#else
    #pragma pack(push, 1)

    #ifndef _PACKED_1_
        #define _PACKED_1_
    #endif
#endif
/**********************************************************************/

/***** 数据包头 *****/
typedef struct TsPacketHead
{
    unsigned short        uMagicCode;        //魔法码，固定值为0xAA 0x55
    unsigned short        uPacketSeq;        //包编号，用于分包发送时，目前预留
    unsigned short        uPayloadType;    //负载类型，参见：TePacketPayloadType
    unsigned int        nPayloadLen;    //负载长度

    TsPacketHead();
    void SetPacketParam(TePacketPayloadType payloadType, unsigned int payloadLen);
} _PACKED_1_ TsPacketHead;
const int CST_PACKET_HEAD_LEN = sizeof(TsPacketHead);

/***** 命令头 *****/
typedef struct TsCommandHead
{
    ushort        uMagicCode;        //魔法码，固定值为0xAA 0x55
    uint        nCommandID;        //命令ID
    uint        nSeq;           //命令序列号
    uint        nPayloadLen;    //负载长度

    TsCommandHead();
    void InitHead(uint cmdID, uint seq, uint payloadLen);
} _PACKED_1_ TsCommandHead;

const int CST_CMD_HEAD_LEN = sizeof(TsCommandHead);


/***** 简单请求命令 *****/
typedef struct TsSimpleRequestCmd
{
    TsCommandHead        tsHead;        //命令头

    void SetCmdParam(uint cmdID, uint seq);
} _PACKED_1_ TsSimpleRequestCmd;

/***** 简单应答命令 *****/
typedef struct TsSimpleResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果

    TsSimpleResponseCmd();
    void SetCmdParam(unsigned int cmdID, uint seq, short errorCode);
} _PACKED_1_ TsSimpleResponseCmd;

/***** 登录请求 *****/
typedef struct TsLoginRequestCmd
{
    TsCommandHead    tsHead;
    TsLoginInfo        tsLoginInfo;

    TsLoginRequestCmd(uint seq);
    void SetCmdParam(const TsLoginInfo& loginInfo);
} _PACKED_1_ TsLoginRequestCmd;

/***** 登录应答 *****/
typedef struct TsLoginResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果
    int                    nMediaPort;        //媒体数据端口

    TsLoginResponseCmd(uint seq);
    void SetCmdParam(short errorCode, int mediaPort);
} _PACKED_1_ TsLoginResponseCmd;

/***** 新增角色命令 *****/
typedef struct TsAddRoleInfoCmd
{
    TsCommandHead    tsHead;
    TsRoleInfo        tsRoleInfo;

    TsAddRoleInfoCmd(uint seq);
    void SetCmdParam(const TsRoleInfo& roleInfo);
} _PACKED_1_ TsAddRoleInfoCmd;

typedef struct TsAddRoleInfoResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果
    uint                nRoleID;        //角色ID

    TsAddRoleInfoResponseCmd(uint seq);
} _PACKED_1_ TsAddRoleInfoResponseCmd;

/***** 获取角色命令 *****/
typedef struct TsGetRoleInfoCmd
{
    TsCommandHead        tsHead;
    TsQueryCondition    tsQueryCondition;

    TsGetRoleInfoCmd(uint seq);
} _PACKED_1_ TsGetRoleInfoCmd;

typedef struct TsGetRoleInfoResponseCmd
{
    TsCommandHead            tsHead;            //命令头
    short                    nResultCode;    //处理结果
    TsRoleInfoQueryResult   tsQueryResult;

    TsGetRoleInfoResponseCmd(uint seq);
} _PACKED_1_ TsGetRoleInfoResponseCmd;

/***** 设置角色命令 *****/
typedef struct TsSetRoleInfoCmd
{
    TsCommandHead    tsHead;
    TsRoleInfo        tsRoleInfo;

    TsSetRoleInfoCmd(uint seq);
    void SetCmdParam(const TsRoleInfo& roleInfo);
} _PACKED_1_ TsSetRoleInfoCmd;

/***** 删除角色命令 *****/
typedef struct TsDeleteRoleInfoCmd
{
    TsCommandHead    tsHead;
    uint            nRoleID;

    TsDeleteRoleInfoCmd(uint seq);
} _PACKED_1_ TsDeleteRoleInfoCmd;

/***** 设置角色权限命令 *****/
typedef struct TsSetRolePrivilegeCmd
{
    TsCommandHead    tsHead;
    TsRolePrivilege    tsRolePrivilege;

    TsSetRolePrivilegeCmd(uint seq);
    void SetCmdParam(const TsRolePrivilege& rolePrivilege);
} _PACKED_1_ TsSetRolePrivilegeCmd;

/***** 获取角色权限命令 *****/
typedef struct TsGetRolePrivilegeCmd
{
    TsCommandHead    tsHead;
    uint            nRoleID;

    TsGetRolePrivilegeCmd(uint seq);
} _PACKED_1_ TsGetRolePrivilegeCmd;

typedef struct TsGetRolePrivilegeResponseCmd
{
    TsCommandHead            tsHead;            //命令头
    short                    nResultCode;    //处理结果
    TsRolePrivilege         tsRolePrivilege;

    TsGetRolePrivilegeResponseCmd(uint seq);
} _PACKED_1_ TsGetRolePrivilegeResponseCmd;

/***** 检测用户是否存在命令 *****/
typedef struct TsCheckUserExistedCmd
{
    TsCommandHead    tsHead;
    char            szUserID[MAX_USER_ID_LEN];

    TsCheckUserExistedCmd(uint seq);
    void SetCmdParam(const char* userID);
} _PACKED_1_ TsCheckUserExistedCmd;

typedef struct TsCheckUserExistedResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果
    uchar                nExistedFlag;    //角色ID

    TsCheckUserExistedResponseCmd(uint seq);
} _PACKED_1_ TsCheckUserExistedResponseCmd;

/***** 添加用户命令 *****/
typedef struct TsAddUserInfoCmd
{
    TsCommandHead        tsHead;
    TsUserInfo            tsUserInfo;

    TsAddUserInfoCmd(uint seq);
    void SetCmdParam(const TsUserInfo& userInfo);
} _PACKED_1_ TsAddUserInfoCmd;

/***** 获取用户命令 *****/
typedef struct TsGetUserInfoCmd
{
    TsCommandHead        tsHead;
    TsQueryCondition    tsQueryCondition;

    TsGetUserInfoCmd(uint seq);
} _PACKED_1_ TsGetUserInfoCmd;

typedef struct TsGetUserInfoResponseCmd
{
    TsCommandHead            tsHead;            //命令头
    short                    nResultCode;    //处理结果
    TsUserInfoQueryResult   tsQueryResult;

    TsGetUserInfoResponseCmd(uint seq);
} _PACKED_1_ TsGetUserInfoResponseCmd;

/***** 设置用户命令 *****/
typedef struct TsSetUserInfoCmd
{
    TsCommandHead        tsHead;
    TsUserInfo            tsUserInfo;

    TsSetUserInfoCmd(uint seq);
    void SetCmdParam(const TsUserInfo& userInfo);
} _PACKED_1_ TsSetUserInfoCmd;

/***** 删除用户命令 *****/
typedef struct TsDeleteUserInfoCmd
{
    TsCommandHead    tsHead;
    char            szUserID[MAX_USER_ID_LEN];

    TsDeleteUserInfoCmd(uint seq);
    void SetCmdParam(const char* userID);
} _PACKED_1_ TsDeleteUserInfoCmd;

/***** 查询机器人信息命令 *****/
typedef struct TsGetRobotInfoCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsQueryCondition                tsQueryCondition;    //查询条件

    TsGetRobotInfoCmd(uint seq);
} _PACKED_1_ TsGetRobotInfoCmd;

/***** 查询机器人信息应答命令 *****/
typedef struct TsGetRobotInfoResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsRobotInfoQueryResult      tsQueryResult;    //管廊信息查询结果

    TsGetRobotInfoResponseCmd(uint seq);
} _PACKED_1_ TsGetRobotInfoResponseCmd;

/***** 查询机器人状态命令 *****/
typedef struct TsGetRobotStatusCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsQueryCondition                tsQueryCondition;    //查询条件

    TsGetRobotStatusCmd(uint seq);
} _PACKED_1_ TsGetRobotStatusCmd;

/***** 查询机器人状态应答命令 *****/
typedef struct TsGetRobotStatusResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsRobotStatusQueryResult    tsQueryResult;    //管廊信息查询结果

    TsGetRobotStatusResponseCmd(uint seq);
} _PACKED_1_ TsGetRobotStatusResponseCmd;

/***** 查询流媒体状态应答命令 *****/
typedef struct TsGetRobotMediaStatusResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsRobotMediaStatus          mediaStatus;    //流媒体信息

    TsGetRobotMediaStatusResponseCmd(uint seq);
} _PACKED_1_ TsGetRobotMediaStatusResponseCmd;


/***** 查询机器人上下线统计命令 *****/
typedef struct TsGetRobotOnlineCountCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsRobotOnlineQueryCondition tsQueryCondition;    //查询条件

    TsGetRobotOnlineCountCmd(uint seq);
} _PACKED_1_ TsGetRobotOnlineCountCmd;

/***** 查询机器人上下线应答 *****/
typedef struct TsGetRobotOnlineCountResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsRobotOnlineCountQueryResult      tsQueryResult;    //管廊信息查询结果

    TsGetRobotOnlineCountResponseCmd(uint seq);
} _PACKED_1_ TsGetRobotOnlineCountResponseCmd;

/***** 查询操作记录 *****/
typedef struct TsGetOperationRecordCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsOperationRecordQueryCondition tsQueryCondition;    //查询条件

    TsGetOperationRecordCmd(uint seq);
} _PACKED_1_ TsGetOperationRecordCmd;

/***** 查询操作记录应答 *****/
typedef struct TsGetOperationRecordResponseCmd
{
    TsCommandHead                    tsHead;            //命令头
    short                            nResultCode;    //处理结果
    TsOperationRecordQueryResult      tsQueryResult;    //操作记录查询结果

    TsGetOperationRecordResponseCmd(uint seq);
} _PACKED_1_ TsGetOperationRecordResponseCmd;

/***** 查询传感器数据记录命令 *****/
typedef struct TsCarStatusRecordCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsCarStatusQueryCondition    tsQueryCondition;    //查询条件

    TsCarStatusRecordCmd(uint seq);
} _PACKED_1_ TsCarStatusRecordCmd;

/***** 查询传感器数据记录应答 *****/
typedef struct TsCarStatusRecordResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsCarStatusRecordQueryResult      tsQueryResult;    //管廊信息查询结果

    TsCarStatusRecordResponseCmd(uint seq);
} _PACKED_1_ TsCarStatusRecordResponseCmd;


/***** 查询传感器数据记录统计命令 *****/
typedef struct TsCarStatusRecordSummaryCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsCarStatusQueryCondition    tsQueryCondition;    //查询条件

    TsCarStatusRecordSummaryCmd(uint seq);
} _PACKED_1_ TsCarStatusRecordSummaryCmd;

/***** 查询传感器数据记录应答 *****/
typedef struct TsCarStatusRecordSummaryResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsCarStatusRecordQueryResult      tsQueryResult;    //管廊信息查询结果

    TsCarStatusRecordSummaryResponseCmd(uint seq);
} _PACKED_1_ TsCarStatusRecordSummaryResponseCmd;

/***** 查询路基设备数据记录命令 *****/
typedef struct TsMonitoredDvsRecordCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsMonitoredDvsRecrdQueryCondition    tsQueryCondition;    //查询条件

    TsMonitoredDvsRecordCmd(uint seq);
} _PACKED_1_ TsMonitoredDvsRecordCmd;

/***** 查询路基设备数据数据记录应答 *****/
typedef struct TsMonitoredDvsRecordResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsMonitoredDvsRecordQueryResult      tsQueryResult;    //管廊信息查询结果

    TsMonitoredDvsRecordResponseCmd(uint seq);
} _PACKED_1_ TsMonitoredDvsRecordResponseCmd;

/***** 查询路基设备数据记录统计命令 *****/
typedef struct TsMonitoredDvsRecordSummaryCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsMonitoredDvsRecrdQueryCondition    tsQueryCondition;    //查询条件

    TsMonitoredDvsRecordSummaryCmd(uint seq);
} _PACKED_1_ TsMonitoredDvsRecordSummaryCmd;

/***** 查询路基设备数据数据记录统计应答 *****/
typedef struct TsMonitoredDvsRecordSummaryResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsMonitoredDvsRecordQueryResult      tsQueryResult;    //管廊信息查询结果

    TsMonitoredDvsRecordSummaryResponseCmd(uint seq);
} _PACKED_1_ TsMonitoredDvsRecordSummaryResponseCmd;

/***** 查询机器人位置记录命令 *****/
typedef struct TsLocationRecordCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsCarStatusQueryCondition    tsQueryCondition;    //查询条件

    TsLocationRecordCmd(uint seq);
} _PACKED_1_ TsLocationRecordCmd;

/***** 查询机器人位置记录应答 *****/
typedef struct TsLocationResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsCarStatusRecordQueryResult      tsQueryResult;    //管廊信息查询结果

    TsLocationResponseCmd(uint seq);
} _PACKED_1_ TsLocationResponseCmd;

/***** 机器人简单请求命令 *****/
typedef struct TsRobotSimpleRequestCmd
{
    TsCommandHead        tsHead;                        //命令头
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID

    TsRobotSimpleRequestCmd();
    void SetCmdParam(unsigned int cmdID, uint seq, const char* robotID);
} _PACKED_1_ TsRobotSimpleRequestCmd;

/***** 获取媒体摘要信息命令 *****/
typedef struct TsGetVersionResponseCmd
{
    TsCommandHead                    tsHead;                        //命令头
    short                            nResultCode;                //处理结果
    char                            szVersion[MAX_VERSION_LEN];    //媒体摘要信息

    TsGetVersionResponseCmd(uint seq);
    void SetCmdParam(const char* version);
} _PACKED_1_ TsGetVersionResponseCmd;

/***** 获取媒体摘要信息命令 *****/
typedef struct TsGetMediaSummaryInfoResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;       //处理结果
    RobotMediaSummaryInfo        tsSummaryInfo;     //媒体摘要信息

    TsGetMediaSummaryInfoResponseCmd(uint seq);
} _PACKED_1_ TsGetMediaSummaryInfoResponseCmd;

/***** 设置机器人名称命令 *****/
typedef struct TsSetRobotNameCmd
{
    TsCommandHead        tsHead;                        //命令头
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    char                sName[DEV_NAME_LEN];        //机器人名称

    TsSetRobotNameCmd(uint seq);
    void SetCmdParam(const char* robotID, const char* name);
} _PACKED_1_ TsSetRobotNameCmd;

/***** 获取机器人名称命令 *****/
typedef struct TsGetRobotNameResponseCmd
{
    TsCommandHead        tsHead;                        //命令头
    short                nResultCode;                //处理结果
    char                sName[DEV_NAME_LEN];        //机器人名称

    TsGetRobotNameResponseCmd(uint seq);
    void SetCmdParam(const char* name);
} _PACKED_1_ TsGetRobotNameResponseCmd;

/***** 设置机器人名称命令 *****/
typedef struct TsGetUnsDateTimeResponseCmd
{
    TsCommandHead        tsHead;         //命令头
    short                nResultCode;    //处理结果
    unsigned int        nSeconds;       //秒

    TsGetUnsDateTimeResponseCmd(uint seq);
} _PACKED_1_ TsGetUnsDateTimeResponseCmd;

/***** 创建数据通道应答 *****/
typedef struct TsCreateDataChannelResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果
    unsigned short        nDataChannelID;    //数据通道编号

    TsCreateDataChannelResponseCmd(uint seq);
    void SetCmdParam(short resultCode, unsigned short dataChannelID);
} _PACKED_1_ TsCreateDataChannelResponseCmd;

/***** 开始视频预览 *****/
typedef struct TsStartLivePreviewCmd
{
    TsCommandHead        tsHead;                //命令头
    TsMediaSourceID        tsMediaSourceID;    //数据源ID
    unsigned short        nDataChannelID;        //数据通道ID, Client使用，Robot无意义

    TsStartLivePreviewCmd(uint seq);
    void SetCmdParam(const TsMediaSourceID& mediaSourceID, unsigned short dataChannelID);
} _PACKED_1_ TsStartLivePreviewCmd;

/***** 开始视频预览应答 *****/
typedef struct TsStartLivePreviewResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果
    unsigned short        nConsumerID;    //消费者ID，Client使用, Robot不用

    TsStartLivePreviewResponseCmd(uint seq);
} _PACKED_1_ TsStartLivePreviewResponseCmd;

/***** 停止视频预览命令 *****/
typedef struct TsStopLivePreviewCmd
{
    TsCommandHead        tsHead;                //命令头
    unsigned short        nConsumerID;        //消费者ID
    TsMediaSourceID        tsMediaSourceID;    //数据源ID

    TsStopLivePreviewCmd(uint seq);
} _PACKED_1_ TsStopLivePreviewCmd;

/***** 开始对讲 *****/
typedef struct TsStartTalkbackCmd
{
    TsCommandHead        tsHead;                //命令头
    TsMediaSourceID        tsMediaSourceID;    //数据源ID
    int                 nConsumerID;        //消费者ID, Client使用，Robot无意义

    TsStartTalkbackCmd(uint seq);
    void SetCmdParam(const TsMediaSourceID& mediaSourceID, int consumerID);
} _PACKED_1_ TsStartTalkbackCmd;

/***** 开始对讲预览应答 *****/
typedef struct TsStartTalkbackResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果
    unsigned short        nConsumerID;    //消费者ID，Client使用, Robot不用

    TsStartTalkbackResponseCmd(uint seq);
} _PACKED_1_ TsStartTalkbackResponseCmd;

/***** 停止对讲 *****/
typedef struct TsStopTalkbackCmd
{
    TsCommandHead        tsHead;                //命令头
    TsMediaSourceID        tsMediaSourceID;    //数据源ID
    int                 nConsumerID;        //消费者ID, Client使用，Robot无意义

    TsStopTalkbackCmd(uint seq);
    void SetCmdParam(const TsMediaSourceID& mediaSourceID, int consumerID);
} _PACKED_1_ TsStopTalkbackCmd;

/***** 停止对讲预览应答 *****/
typedef struct TsStopTalkbackResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果
    unsigned short        nConsumerID;    //消费者ID，Client使用, Robot不用

    TsStopTalkbackResponseCmd(uint seq);
} _PACKED_1_ TsStopTalkbackResponseCmd;


/***** 启动视频代理 *****/
typedef struct TsStartMediaProxyCmd
{
    TsCommandHead        tsHead;                //命令头
    RobotMediaInfo       tsChannelInfo;      //IPC信息

    TsStartMediaProxyCmd(uint seq);
    void SetCmdParam(const RobotMediaInfo& channelInfo);
} _PACKED_1_ TsStartMediaProxyCmd;

/***** 查询录像策略命令 *****/
typedef struct TsGetRecordPolicyCmd
{
    TsCommandHead    tsHead;                        //命令头
    char            sRobotID[ROBOT_ID_LEN];        //机器人ID

    TsGetRecordPolicyCmd(uint seq);
    void SetCmdParam(const char* robotID);
} _PACKED_1_ TsGetRecordPolicyCmd;

/***** 查询录像策略应答命令 *****/
typedef struct TsGetRecordPolicyResponseCmd
{
    TsCommandHead    tsHead;            //命令头
    short            nResultCode;    //处理结果
    TsRecordPolicy    arrRecordPolicy[MAX_ROBOT_NUM];
    unsigned short    nCount;            //录像策略个数

    TsGetRecordPolicyResponseCmd(uint seq);
    void SetCmdParam(short ret, TsRecordPolicy* pRecordPolicy, unsigned short count);
} _PACKED_1_ TsGetRecordPolicyResponseCmd;

/***** 设置录像策略命令 *****/
typedef struct TsSetRecordPolicyCmd
{
    TsCommandHead        tsHead;            //命令头
    TsRecordPolicy        tsRecordPolicy;    //录像策略

    TsSetRecordPolicyCmd(uint seq);
    void SetCmdParam(const TsRecordPolicy& recordPolicy);
} _PACKED_1_ TsSetRecordPolicyCmd;

/***** 获取录像状态命令 *****/
typedef struct TsGetRecordStatusResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short               nResult;        //处理结果
    TsRobotMediaStatus    tsStatus;        //录像状态

    TsGetRecordStatusResponseCmd(uint seq);
    void SetCmdParam(const TsRobotMediaStatus& status);
} _PACKED_1_ TsGetRecordStatusResponseCmd;

/***** 查询录像保留期限应答命令 *****/
typedef struct TsGetRecordExpireTimeResponseCmd
{
    TsCommandHead    tsHead;            //命令头
    short            nResultCode;    //处理结果
    unsigned int    nExpireTime;    //录像保留期限

    TsGetRecordExpireTimeResponseCmd(uint seq);
    void SetCmdParam(short ret, unsigned int expireTime);
} _PACKED_1_ TsGetRecordExpireTimeResponseCmd;

/***** 设置录像保留期限命令 *****/
typedef struct TsSetRecordExpireTimeCmd
{
    TsCommandHead        tsHead;            //命令头
    unsigned int        nExpireTime;    //录像保留期限

    TsSetRecordExpireTimeCmd(uint seq);
    void SetCmdParam(unsigned int expireTime);
} _PACKED_1_ TsSetRecordExpireTimeCmd;

/***** 获取录像日历命令 *****/
typedef struct TsGetRecordCalendarCmd
{
    TsCommandHead        tsHead;                    //命令头
    char                sRobotID[ROBOT_ID_LEN];    //机器人ID
    unsigned int        nYearMonth;             //年月，如：201811

    TsGetRecordCalendarCmd(uint seq);
    void SetCmdParam(const char* robotID, unsigned int yearMonth);
} _PACKED_1_ TsGetRecordCalendarCmd;

/***** 获取录像日历应答命令 *****/
typedef struct TsGetRecordCalendarResponseCmd
{
    TsCommandHead        tsHead;                //命令头
    short                nResultCode;        //处理结果
    TsRecordCalendar    tsRecordCalenar;    //录像日历

    TsGetRecordCalendarResponseCmd(uint seq);
} _PACKED_1_ TsGetRecordCalendarResponseCmd;

/***** 存储查询命令 *****/
typedef struct TsStorageQueryCmd
{
    TsCommandHead            tsHead;                //命令头
    TsStorageQueryCondition    tsQueryCondition;    //查询条件

    TsStorageQueryCmd(uint seq);
    void SetCmdParam(uint seq, TeStorageType storageType, const TsStorageQueryCondition& queryCondition);
} _PACKED_1_ TsStorageQueryCmd;

/***** 存储查询应答命令 *****/
typedef struct TsStorageQueryResponseCmd
{
    TsCommandHead            tsHead;                //命令头
    short                    nResultCode;        //处理结果
    TsStorageQueryResult    tsQueryResult;        //录像结果

    TsStorageQueryResponseCmd(uint seq);
    void SetCmdParam(uint seq, TeStorageType storageType, short ret, const TsStorageQueryResult* queryResult);
} _PACKED_1_ TsStorageQueryResponseCmd;


/***** 开始回放命令 *****/
typedef struct TsStartRetrievalCmd
{
    TsCommandHead            tsHead;                //命令头
    TsRetrievalInfo            tsRecordInfo;        //查询条件
    unsigned short            nDataChannelID;        //数据通道ID
    bool                    bSkipSpace;            //跳过录像空白

    TsStartRetrievalCmd(uint seq);
    void SetCmdParam(const TsRetrievalInfo& recordInfo, unsigned short dataChannelID, bool skipSpace);
} _PACKED_1_ TsStartRetrievalCmd;

/***** 开始回放应答命令 *****/
typedef struct TsStartRetrievalResponseCmd
{
    TsCommandHead            tsHead;                //命令头
    short                    nResultCode;        //处理结果
    unsigned short            nRetrievalID;        //消费者ID
    unsigned int            nRecordBeginTime;    //录像开始的时间点

    TsStartRetrievalResponseCmd(uint seq);
    void SetCmdParam(short resultCode, unsigned short retrievalID, unsigned int recordBeginTime);
} _PACKED_1_ TsStartRetrievalResponseCmd;

/***** 停止回放命令 *****/
typedef struct TsStopRetrievalCmd
{
    TsCommandHead            tsHead;                //命令头
    unsigned short            nRetrievalID;        //消费者ID

    TsStopRetrievalCmd(uint seq);
    void SetCmdParam(unsigned short retrievalID);
} _PACKED_1_ TsStopRetrievalCmd;

/***** 回放控制命令 *****/
typedef struct TsRetrievalCtrlCmd
{
    TsCommandHead            tsHead;                //命令头
    unsigned short            nRetrievalID;        //消费者ID
    unsigned short            nCtrlType;            //控制类型,参考TeRetrievalType
    double                    dCtrlParam;            //控制参数

    TsRetrievalCtrlCmd(uint seq);
    void SetCmdParam(unsigned short retrievalID, unsigned short ctrlType, double ctrlParam);
} _PACKED_1_ TsRetrievalCtrlCmd;

/***** 回放状态命令 *****/
// typedef struct TsRetrievalStatusCmd
// {
//     TsCommandHead            tsHead;                //命令头
//     unsigned short            nRetrievalID;        //消费者ID
//     int                        nRetrievalStatus;    //回放状态码
//
//     TsRetrievalStatusCmd(uint seq);
//     void SetCmdParam(unsigned short retrievalID, int retrievalStatus);
// }_PACKED_1_ TsRetrievalStatusCmd;

/***** 设置回放时间命令 *****/
typedef struct TsSetRetrievalTimeCmd
{
    TsCommandHead            tsHead;                //命令头
    uint                    nBeginSecond;
    uint                    nEndSecond;
    TsSetRetrievalTimeCmd(uint seq);
    void SetCmdParam(uint beginSecond, uint endSecond);
} _PACKED_1_ TsSetRetrievalTimeCmd;

/***** 设置跳过空白区域命令 *****/
typedef struct TsSetSkipBlandSpaceCmd
{
    TsCommandHead            tsHead;                //命令头
    bool                    bFlag;
    TsSetSkipBlandSpaceCmd(uint seq);
} _PACKED_1_ TsSetSkipBlandSpaceCmd;

/***** 设置回放速率命令 *****/
typedef struct TsSetRetrievalRateCmd
{
    TsCommandHead            tsHead;                //命令头
    float                   fRate;              //回放速率
    INT64                   nCurrRetrievalMsec; //当前回放的时间

    TsSetRetrievalRateCmd(uint seq);
    void SetCmdParam(float rate, INT64 currRetrievalMsec);
} _PACKED_1_ TsSetRetrievalRateCmd;

/***** 回放时间定位命令 *****/
typedef struct TsSetRetrievalRateResponseCmd
{
    TsCommandHead            tsHead;                //命令头
    short                    nResultCode;        //处理结果
    INT64                   nLocateTimestamp;
    TsSetRetrievalRateResponseCmd(uint seq);
} _PACKED_1_ TsSetRetrievalRateResponseCmd;

/***** 请求通道视频命令 *****/
typedef struct TsStartChannelMediaCmd
{
    TsCommandHead            tsHead;                //命令头
    ushort                  nChannelID;         //通道
    uint                    nDataChannelID;     //数据通道
    INT64                   nBeginMsec;         //开始时间,单位：毫秒
    INT64                   nEndMsec;          //结束时间,单位：毫秒
    TsStartChannelMediaCmd(uint seq);
    void SetCmdParam(ushort channelID, uint dataChannelID, INT64 beginMsec, INT64 endMsec);
} _PACKED_1_ TsStartChannelMediaCmd;

/***** 停止通道视频命令 *****/
typedef struct TsStopChannelMediaCmd
{
    TsCommandHead            tsHead;                //命令头
    ushort                  nChannelID;
    TsStopChannelMediaCmd(uint seq);
} _PACKED_1_ TsStopChannelMediaCmd;

/***** 回放时间定位命令 *****/
typedef struct TsRetrievalLocateTimeCmd
{
    TsCommandHead            tsHead;                //命令头
    uint                    nSecond;
    TsRetrievalLocateTimeCmd(uint seq);
} _PACKED_1_ TsRetrievalLocateTimeCmd;

/***** 回放时间定位命令 *****/
typedef struct TsRetrievalLocateTimeResponseCmd
{
    TsCommandHead            tsHead;                //命令头
    short                    nResultCode;        //处理结果
    TsRetrievalLocateTime   tsRetrievalLocateTime;   //定位的帧的时间
    TsRetrievalLocateTimeResponseCmd(uint seq);
} _PACKED_1_ TsRetrievalLocateTimeResponseCmd;

/***** 设置拖动时间命令 *****/
typedef struct TsBrowseCmd
{
    TsCommandHead            tsHead;                //命令头
    uint                    nSecond;
    TsBrowseCmd(uint seq);
} _PACKED_1_ TsBrowseCmd;


/***** 抓拍控制命令 *****/
typedef struct TsSnapshotCtrlCmd
{
    TsCommandHead        tsHead;                //命令头
    TsMediaSourceID        tsMediaSourceID;    //数据源ID
    unsigned short        nCtrlType;            //控制类型，参见TeSnapshotCtrlType
    TsSnapshotTask        tsSnapshotTask;        //抓拍任务，nCtrlType 取值为 ENM_START_SNAPSHOT 时生效

    TsSnapshotCtrlCmd(uint seq);
    void SetCmdParam(const TsMediaSourceID& mediaSourceID, unsigned short snapshotCtrlType, const TsSnapshotTask* snapshotTask = 0);
} _PACKED_1_ TsSnapshotCtrlCmd;

/***** 抓拍控制命令 *****/
typedef struct TsSnapshotResponseCmd
{
    TsCommandHead        tsHead;                //命令头
    short                nResultCode;        //处理结果
    TsMediaFrameHead    tsMediaFrameHead;   //视频帧头信息
    //char*               psFrame;            //视频数据

    TsSnapshotResponseCmd(uint seq);
    void SetCmdParam(const TsMediaFrameHead& frameHead);
} _PACKED_1_ TsSnapshotResponseCmd;


/***** 开始消息传输命令 *****/
typedef struct TsStartMsgTransmitCmd
{
    TsCommandHead            tsHead;                //命令头
    unsigned short            nDataChannel;        //数据通道ID

    TsStartMsgTransmitCmd(uint seq);
} _PACKED_1_ TsStartMsgTransmitCmd;


/***** 升级请求命令 *****/
typedef struct TsDvsUpgradeCmd
{
    TsCommandHead        tsHead;                        //命令头
    unsigned short        nDvsType;                    //设备类型，见TeDvsType
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID，设备类型为机器人时生效
    char                sFileName[MAX_FILE_NAME_LEN];    //升级文件名
    unsigned int        nFileSize;                    //升级文件总长度，单位：字节
    unsigned short        nDataChannelID;                //文件传输通道编号

    TsDvsUpgradeCmd(uint seq);
    void SetCmdParam(unsigned short dvsType, const char* robotID, const char* fileName, unsigned int fileSize, unsigned short dataChannelID);
} _PACKED_1_ TsDvsUpgradeCmd;

/***** 升级应答命令 *****/
typedef struct TsDvsUpgradeResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果
    unsigned short        nDataChannelID;    //文件传输通道编号，Robot端需要返回该值，Client不处理该值

    TsDvsUpgradeResponseCmd(uint seq);
    void SetCmdParam(short resuleCode, unsigned short dataChannelID);
} _PACKED_1_ TsDvsUpgradeResponseCmd;

/***** 升级状态命令 *****/
typedef struct TsDvsUpgradeStatusCmd
{
    TsCommandHead        tsHead;            //命令头
    TsDvsUpgradeStatus    tsStatus;        //升级详细状态

    TsDvsUpgradeStatusCmd(uint seq);
    void SetCmdParam(const TsDvsUpgradeStatus& upGradeStatus);
} _PACKED_1_ TsDvsUpgradeStatusCmd;


/***** 机器人运动控制命令 *****/
typedef struct TsCtrlRobotMotionCmd
{
    TsCommandHead        tsHead;                //命令头
    TsRobotMotion        tsRobotMotion;        //机器人运动参数

    TsCtrlRobotMotionCmd(uint seq);
    void SetCmdParam(const char* robotID, short speed);
} _PACKED_1_ TsCtrlRobotMotionCmd;

/***** 机器人压力轮控制命令 *****/
typedef struct TsSetRobotPressureCmd
{
    TsCommandHead        tsHead;                //命令头
    TsRobotPressure        tsRobotPressure;    //机器人压力轮参数

    TsSetRobotPressureCmd(uint seq);
    void SetCmdParam(const char* robotID, unsigned short pressure);
} _PACKED_1_ TsSetRobotPressureCmd;

/***** 机器人灯光状态获取命令 *****/
typedef struct TsGetRobotLampResponseCmd
{
    TsCommandHead        tsHead;            //命令头
    short                nResultCode;    //处理结果
    TsRobotLampStatus    tsLampStatus;    //机器人灯光参数

    TsGetRobotLampResponseCmd(uint seq);
} _PACKED_1_ TsGetRobotLampResponseCmd;

/***** 机器人灯光控制命令 *****/
typedef struct TsSetRobotLampCmd
{
    TsCommandHead        tsHead;                //命令头
    TsRobotLamp            tsRobotLamp;        //机器人灯光参数

    TsSetRobotLampCmd(uint seq);
    void SetCmdParam(const char* robotID, unsigned short lampID, unsigned char lamp);
} _PACKED_1_ TsSetRobotLampCmd;

/***** 机器人避障状态获取命令 *****/
typedef struct TsGetRobotAvoidObstacleResponseCmd
{
    TsCommandHead            tsHead;                //命令头
    short                    nResultCode;        //处理结果
    TsRobotAvoidObstacle    tsAvoidObstacle;    //避障参数

    TsGetRobotAvoidObstacleResponseCmd(uint seq);
} _PACKED_1_ TsGetRobotAvoidObstacleResponseCmd;

/***** 机器人避障开关控制 *****/
typedef struct TsSetRobotAvoidObstacleCmd
{
    TsCommandHead            tsHead;                //命令头
    TsRobotAvoidObstacle    tsAvoidObstacle;    //避障参数

    TsSetRobotAvoidObstacleCmd(uint seq);
    void SetCmdParam(const char* robotID, ushort avoidObstacle);
} _PACKED_1_ TsSetRobotAvoidObstacleCmd;

/***** 机器人驻车控制命令 *****/
typedef struct TsRobotParkingCmd
{
    TsCommandHead        tsHead;                //命令头
    TsRobotParking        tsRobotParking;        //机器人驻车参数

    TsRobotParkingCmd(uint seq);
    void SetCmdParam(const char* robotID, unsigned char parking);
} _PACKED_1_ TsRobotParkingCmd;

/***** 机器人巡检控制命令 *****/
typedef struct TsRobotTourCtrlCmd
{
    TsCommandHead        tsHead;                //命令头
    TsRobotTourCtrl        tsRobotTourCtrl;        //机器人暂停巡检参数

    TsRobotTourCtrlCmd(uint seq);
    void SetCmdParam(const char* robotID, unsigned char action);
} _PACKED_1_ TsRobotTourCtrlCmd;



/***** 机器人位置校正命令 *****/
typedef struct TsRobotLocationCmd
{
    TsCommandHead            tsHead;                //命令头
    TsRobotLocation         tsLocation;    //机器人位置校正

    TsRobotLocationCmd(uint cmdID, uint seq);
    void SetCmdParam(const char* robotID, int location);
} _PACKED_1_ TsRobotLocationCmd;

/***** 机器人手动巡检命令 *****/
typedef struct TsRobotManualTourCmd
{
    TsCommandHead            tsHead;                //命令头
    TsManualTourParam       tsManualTourParam;    //机器人位置校正

    TsRobotManualTourCmd(uint seq);
    void SetCmdParam(const char* robotID, ushort action);
} _PACKED_1_ TsRobotManualTourCmd;

/***** 机器人巡检策略配置命令 *****/
typedef struct TsSetRobotTourCmd
{
    TsCommandHead            tsHead;                //命令头
    TsRobotTour                tsRobotTour;        //机器人巡检参数

    TsSetRobotTourCmd(uint seq);
    void SetCmdParam(const TsRobotTour& robotTour);
} _PACKED_1_ TsSetRobotTourCmd;

/***** 机器人巡检策略查询应答 *****/
typedef struct TsGetRobotTourResponseCmd
{
    TsCommandHead            tsHead;            //命令头
    short                    nResultCode;    //处理结果
    TsRobotTour                tsRobotTour;    //机器人巡检参数

    TsGetRobotTourResponseCmd(uint seq);
} _PACKED_1_ TsGetRobotTourResponseCmd;

/***** 机器人自动巡检 *****/
typedef struct TsRobotAutoTourCmd
{
    TsCommandHead            tsHead;            //命令头
    TsRobotAutoTour            tsAutoTour;        //自动巡检参数

    TsRobotAutoTourCmd(uint seq);
    void SetCmdParam(const TsRobotAutoTour& autoTour);
} _PACKED_1_ TsRobotAutoTourCmd;

/***** 充电控制命令 *****/
typedef struct TsRobotChargeCmd
{
    TsCommandHead            tsHead;            //命令头
    TsRobotChargeCtrl        tsChargeCtrl;        //充电控制参数

    TsRobotChargeCmd(uint seq);
    void SetCmdParam(const TsRobotChargeCtrl& chargeCtrl);
} _PACKED_1_ TsRobotChargeCmd;

/***** 云台控制命令 *****/
typedef struct TsRobotPtzCtrlCmd
{
    TsCommandHead            tsHead;            //命令头
    TsRobotPtzCtrl            tsPtzCtrl;        //云台控制参数

    TsRobotPtzCtrlCmd(uint seq);
    void SetCmdParam(const TsRobotPtzCtrl& ptzCtrl);
} _PACKED_1_ TsRobotPtzCtrlCmd;

/***** 云台3d位置命令 *****/
typedef struct TsPtzThreeDimensionalPosCmd
{
    TsCommandHead            tsHead;            //命令头
    TsPtz3DParam            tsPtz3DParam;        //云台3d控制参数

    TsPtzThreeDimensionalPosCmd(uint seq);
    void SetCmdParam(const TsPtz3DParam& ptz3DParam);
} _PACKED_1_ TsPtzThreeDimensionalPosCmd;

/***** 机械臂控制命令 *****/
typedef struct TsRobotArmCtrlCmd
{
    TsCommandHead            tsHead;            //命令头
    TsRobotArmCtrl            tsArmCtrl;        //机械臂控制参数

    TsRobotArmCtrlCmd(uint seq);
    void SetCmdParam(const TsRobotArmCtrl& armCtrl);
} _PACKED_1_ TsRobotArmAngleCmd;

/***** 获取报警参数应答命令 *****/
typedef struct TsGetAlarmPolicyResponseCmd
{
    TsCommandHead            tsHead;            //命令头
    short                    nResultCode;    //处理结果
    TsAlarmPolicy            tsAlarmPolicy;

    TsGetAlarmPolicyResponseCmd(uint seq, uint cmdID = CST_CMD_GET_ALARM_POLICY + 1);
    void SetCmdParam(short resultCode, const TsAlarmPolicy& alarmPolicy);
} _PACKED_1_ TsGetAlarmPolicyResponseCmd;

/***** 设置报警参数命令 *****/
typedef struct TsSetAlarmPolicyCmd
{
    TsCommandHead            tsHead;            //命令头
    TsAlarmPolicy            tsAlarmPolicy;

    TsSetAlarmPolicyCmd(uint seq);
    void SetCmd(uint cmdID);
    void SetCmdParam(const TsAlarmPolicy& alarmPolicy);
} _PACKED_1_ TsSetAlarmPolicyCmd;

/***** 报警日志查询命令 *****/
typedef struct TsAlarmLogQueryCmd
{
    TsCommandHead                        tsHead;                //命令头
    TsAlarmLogQueryCondition            tsQueryCondition;    //查询条件

    TsAlarmLogQueryCmd(uint seq);
    void SetCmdParam(const TsAlarmLogQueryCondition& queryCondition);
} _PACKED_1_ TsAlarmLogQueryCmd;

/***** 报警查询返回命令 *****/
typedef struct TsAlarmLogQueryResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsAlarmLogQueryResult        tsQueryResult;    //查询结果

    TsAlarmLogQueryResponseCmd(uint seq);
    void SetCmdParam(short resultCode, const TsAlarmLogQueryResult& queryResult);
} _PACKED_1_ TsAlarmLogQueryResponseCmd;

/***** 报警统计数据查询命令 *****/
typedef struct TsAlarmSummaryQueryCmd
{
    TsCommandHead                        tsHead;                //命令头
    TsAlarmLogQueryCondition            tsQueryCondition;    //查询条件

    TsAlarmSummaryQueryCmd(uint seq);
    void SetCmdParam(const TsAlarmLogQueryCondition& queryCondition);
} _PACKED_1_ TsAlarmSummaryQueryCmd;

/***** 报警摘要查询返回命令 *****/
typedef struct TsAlarmSummaryQueryResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsAlarmSummaryQueryResult    tsQueryResult;    //查询结果

    TsAlarmSummaryQueryResponseCmd(uint seq);
    void SetCmdParam(short resultCode, const TsAlarmSummaryQueryResult& queryResult);
} _PACKED_1_ TsAlarmSummaryQueryResponseCmd;



/***** 新增管廊命令 *****/
typedef struct TsAddPipeGalleryCmd
{
    TsCommandHead                tsHead;            //命令头
    TsPipeGallery                tsPipeGallery;    //管廊信息

    TsAddPipeGalleryCmd(uint seq);
} _PACKED_1_ TsAddPipeGalleryCmd;

/***** 新增管廊应答命令 *****/
typedef struct TsAddPipeGalleryResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    unsigned short                nGalleryID;        //管廊ID

    TsAddPipeGalleryResponseCmd(uint seq);
} _PACKED_1_ TsAddPipeGalleryResponseCmd;

/***** 查询管廊命令 *****/
typedef struct TsGetPipeGalleryCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsQueryCondition                tsQueryCondition;    //查询条件

    TsGetPipeGalleryCmd(uint seq);
} _PACKED_1_ TsGetPipeGalleryCmd;

/***** 查询管廊应答命令 *****/
typedef struct TsGetPipeGalleryResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsPipeGalleryQueryResult    tsQueryResult;    //管廊信息查询结果

    TsGetPipeGalleryResponseCmd(uint seq);
} _PACKED_1_ TsGetPipeGalleryResponseCmd;

/***** 设置管廊命令 *****/
typedef struct TsSetPipeGalleryCmd
{
    TsCommandHead                tsHead;            //命令头
    TsPipeGallery                tsPipeGallery;    //管廊信息

    TsSetPipeGalleryCmd(uint seq);
} _PACKED_1_ TsSetPipeGalleryCmd;

/***** 删除管廊命令 *****/
typedef struct TsDelPipeGalleryCmd
{
    TsCommandHead                tsHead;            //命令头
    unsigned short                nGalleryID;        //管廊ID

    TsDelPipeGalleryCmd(uint seq);
} _PACKED_1_ TsDelPipeGalleryCmd;


/***** 新增站点命令 *****/
typedef struct TsAddTourStationCmd
{
    TsCommandHead                tsHead;            //命令头
    TsTourStation                tsTourStation;    //站点信息

    TsAddTourStationCmd(uint seq);
} _PACKED_1_ TsAddTourStationCmd;

/***** 新增站点应答命令 *****/
typedef struct TsAddTourStationResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    unsigned short                nStationID;        //站点ID

    TsAddTourStationResponseCmd(uint seq);
} _PACKED_1_ TsAddTourStationResponseCmd;

/***** 查询站点命令 *****/
typedef struct TsGetTourStationCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsQueryCondition                tsQueryCondition;    //查询条件

    TsGetTourStationCmd(uint seq);
} _PACKED_1_ TsGetTourStationCmd;

/***** 查询站点应答命令 *****/
typedef struct TsGetTourStationResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsTourStationQueryResult    tsQueryResult;    //站点信息查询结果

    TsGetTourStationResponseCmd(uint seq);
} _PACKED_1_ TsGetTourStationResponseCmd;

/***** 设置站点命令 *****/
typedef struct TsSetTourStationCmd
{
    TsCommandHead                tsHead;            //命令头
    TsTourStation                tsTourStation;    //站点信息

    TsSetTourStationCmd(uint seq);
} _PACKED_1_ TsSetTourStationCmd;

/***** 删除站点命令 *****/
typedef struct TsDelTourStationCmd
{
    TsCommandHead                tsHead;            //命令头
    unsigned short                nStationID;        //站点ID

    TsDelTourStationCmd(uint seq);
} _PACKED_1_ TsDelTourStationCmd;


/***** 新增线路命令 *****/
typedef struct TsAddTourLineCmd
{
    TsCommandHead                tsHead;            //命令头
    TsTourLine                    tsTourLine;    //线路信息

    TsAddTourLineCmd(uint seq);
} _PACKED_1_ TsAddTourLineCmd;

/***** 新增线路应答命令 *****/
typedef struct TsAddTourLineResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    unsigned short                nLineID;        //线路ID

    TsAddTourLineResponseCmd(uint seq);
} _PACKED_1_ TsAddTourLineResponseCmd;

/***** 查询线路命令 *****/
typedef struct TsGetTourLineCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsQueryCondition                tsQueryCondition;    //查询条件

    TsGetTourLineCmd(uint seq);
} _PACKED_1_ TsGetTourLineCmd;

/***** 查询线路应答命令 *****/
typedef struct TsGetTourLineResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsTourLineQueryResult        tsQueryResult;    //线路信息查询结果

    TsGetTourLineResponseCmd(uint seq);
} _PACKED_1_ TsGetTourLineResponseCmd;

/***** 设置线路命令 *****/
typedef struct TsSetTourLineCmd
{
    TsCommandHead                tsHead;            //命令头
    TsTourLine                    tsTourLine;    //线路信息

    TsSetTourLineCmd(uint seq);
} _PACKED_1_ TsSetTourLineCmd;

/***** 删除线路命令 *****/
typedef struct TsDelTourLineCmd
{
    TsCommandHead                tsHead;            //命令头
    unsigned short                nLineID;        //线路ID

    TsDelTourLineCmd(uint seq);
} _PACKED_1_ TsDelTourLineCmd;


/***** 新增任务命令 *****/
typedef struct TsAddTourTaskCmd
{
    TsCommandHead                tsHead;            //命令头
    TsTourTask                    tsTourTask;    //任务信息

    TsAddTourTaskCmd(uint seq);
} _PACKED_1_ TsAddTourTaskCmd;

/***** 新增任务应答命令 *****/
typedef struct TsAddTourTaskResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    ushort                        nTaskID;        //任务ID
    uint                        nPerformTime;    //开始执行时间，仅对立即执行命令有效

    TsAddTourTaskResponseCmd(uint seq);
} _PACKED_1_ TsAddTourTaskResponseCmd;

/***** 查询任务命令 *****/
typedef struct TsGetTourTaskCmd
{
    TsCommandHead                    tsHead;                //命令头
    TsQueryCondition                tsQueryCondition;    //查询条件

    TsGetTourTaskCmd(uint seq);
} _PACKED_1_ TsGetTourTaskCmd;

/***** 查询任务应答命令 *****/
typedef struct TsGetTourTaskResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsTourTaskQueryResult        tsQueryResult;    //任务信息查询结果

    TsGetTourTaskResponseCmd(uint seq);
} _PACKED_1_ TsGetTourTaskResponseCmd;

/***** 设置任务命令 *****/
typedef struct TsSetTourTaskCmd
{
    TsCommandHead                tsHead;            //命令头
    TsTourTask                    tsTourTask;    //任务信息

    TsSetTourTaskCmd(uint seq);
} _PACKED_1_ TsSetTourTaskCmd;

/***** 删除任务命令 *****/
typedef struct TsDelTourTaskCmd
{
    TsCommandHead                tsHead;            //命令头
    unsigned short                nTaskID;        //任务ID

    TsDelTourTaskCmd(uint seq);
} _PACKED_1_ TsDelTourTaskCmd;

/***** 执行站点巡检命令 *****/
typedef struct TsPerformStationDetectionCmd
{
    TsCommandHead                tsHead;                                //命令头
    TsStationDetection          arrStationDetection[MAX_ROBOT_NUM]; //站点巡检参数
    ushort                      nNum;                               //巡检任务个数

    TsPerformStationDetectionCmd(uint seq);
} _PACKED_1_ TsPerformStationDetectionCmd;

/***** 查询巡检状态应答命令 *****/
typedef struct TsGetTourStatusResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsTourStatus                tourStatus;        //巡检状态

    TsGetTourStatusResponseCmd(uint seq);
} _PACKED_1_ TsGetTourStatusResponseCmd;

/***** 上传下载巡检报告命令 *****/
typedef struct TsUploadDownloadTourReportCmd
{
    TsCommandHead                tsHead;            //命令头
    TsUploadDownloadTourReport    tsParam;        //巡检报告参数

    TsUploadDownloadTourReportCmd(uint seq);
} _PACKED_1_ TsUploadDownloadTourReportCmd;

/***** 上传下载巡检报告应答命令 *****/
typedef struct TsUploadDownloadTourReportResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    uint                        nReportFileLen;    //巡检报告文件长度，下载时使用

    TsUploadDownloadTourReportResponseCmd(uint seq);
} _PACKED_1_ TsUploadDownloadTourReportResponseCmd;

/***** 巡检报告查询命令 *****/
typedef struct TsTourReportQueryCmd
{
    TsCommandHead                tsHead;                //命令头
    TsTourReportQueryCondition    tsQueryCondition;    //巡检报告查询参数

    TsTourReportQueryCmd(uint seq);
} _PACKED_1_ TsTourReportQueryCmd;

/***** 巡检报告查询结果命令 *****/
typedef struct TsTourReportQueryResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsTourReportQueryResult        tsQueryResult;    //巡检报告查询结果

    TsTourReportQueryResponseCmd(uint seq);
} _PACKED_1_ TsTourReportQueryResponseCmd;

/***** 巡检报告摘要查询命令 *****/
typedef struct TsSummaryTourReportQueryCmd
{
    TsCommandHead                tsHead;                //命令头
    TsTourReportQueryCondition    tsQueryCondition;    //巡检报告查询参数

    TsSummaryTourReportQueryCmd(uint seq);
} _PACKED_1_ TsSummaryTourReportQueryCmd;

/***** 巡检报告摘要查询结果命令 *****/
typedef struct TsSummaryTourReportQueryResponseCmd
{
    TsCommandHead                tsHead;            //命令头
    short                        nResultCode;    //处理结果
    TsSummaryTourReportQueryResult        tsQueryResult;    //巡检报告查询结果

    TsSummaryTourReportQueryResponseCmd(uint seq);
} _PACKED_1_ TsSummaryTourReportQueryResponseCmd;

/***** 路基设备控制 *****/
typedef struct TsRoadbaseCtrlCmd
{
    TsCommandHead            tsHead;            //命令头
    TsRoadbaseCtrl            tsRoadbaseCtrl;    //路基控制参数

    TsRoadbaseCtrlCmd(uint seq);
    void SetCmdParam(const TsRoadbaseCtrl& roadbaseCtrl);
} _PACKED_1_ TsRoadbaseCtrlCmd;

/***** 新增路基转换器命令 *****/
typedef struct TsAddRoadbaseS2ECmd
{
    TsCommandHead   tsHead;                //命令头
    TsRoadbaseS2E   tsRoadbaseS2E;    //查询条件

    TsAddRoadbaseS2ECmd(uint seq);
    void SetCmdParam(const TsRoadbaseS2E& roadbaseS2E);
} _PACKED_1_ TsAddRoadbaseS2ECmd;

/***** 新增路基转换器应答 *****/
typedef struct TsAddRoadbaseS2EResponseCmd
{
    TsCommandHead   tsHead;         //命令头
    short            nResultCode;    //处理结果
    ushort          nS2EID;         //新增转换器的ID

    TsAddRoadbaseS2EResponseCmd(uint seq);
} _PACKED_1_ TsAddRoadbaseS2EResponseCmd;

/***** 查询路基转换器命令 *****/
typedef struct TsGetRoadbaseS2ECmd
{
    TsCommandHead                    tsHead;                //命令头
    TsQueryCondition                tsQueryCondition;    //查询条件

    TsGetRoadbaseS2ECmd(uint seq);
    void SetCmdParam(const TsQueryCondition& queryCondition);
} _PACKED_1_ TsGetRoadbaseS2ECmd;

/***** 查询路基转换器应答 *****/
typedef struct TsGetRoadbaseS2EResponseCmd
{
    TsCommandHead                tsHead;         //命令头
    short                        nResultCode;    //处理结果
    TsRoadbaseS2EQueryResult    queryResult;    //查询结果

    TsGetRoadbaseS2EResponseCmd(uint seq);
} _PACKED_1_ TsGetRoadbaseS2EResponseCmd;

/***** 设置路基转换器 *****/
typedef struct TsSetRoadbaseS2ECmd
{
    TsCommandHead        tsHead;                //命令头
    TsRoadbaseS2E        tsRoadbaseS2E;    //路基转换器信息

    TsSetRoadbaseS2ECmd(uint seq);
    void SetCmdParam(const TsRoadbaseS2E& rdbsTransverter);
} _PACKED_1_ TsSetRoadbaseS2ECmd;

/***** 删除路基转换器 *****/
typedef struct TsDeleteRoadbaseS2ECmd
{
    TsCommandHead            tsHead;                     //命令头
    ushort                    nS2EID;                     //路基转换器ID
    TsDeleteRoadbaseS2ECmd(uint seq);
} _PACKED_1_ TsDeleteRoadbaseS2ECmd;

/***** 激活路基转换器代理 *****/
typedef struct TsActivateRoadbaseS2ECmd
{
    TsCommandHead            tsHead;        //命令头
    ushort                    nS2EID;        //路基转换器ID

    TsActivateRoadbaseS2ECmd(uint seq);
} _PACKED_1_ TsActivateRoadbaseS2ECmd;

/***** 查询路基设备 *****/
typedef struct TsGetRoadbaseRequestCmd
{
    TsCommandHead            tsHead;                //命令头
    TsQueryCondition        tsQueryCondition;     //查询条件

    TsGetRoadbaseRequestCmd(uint seq);
    void SetCmdParam(const TsQueryCondition& queryCondition);
} _PACKED_1_ TsGetRoadbaseRequestCmd;

/***** 查询路基设备应答 *****/
typedef struct TsGetRoadbaseResponseCmd
{
    TsCommandHead            tsHead;         //命令头
    short                    nResultCode;    //处理结果
    TsRoadbaseQueryResult   queryResult;    //路基设备查询结果

    TsGetRoadbaseResponseCmd(uint seq);
} _PACKED_1_ TsGetRoadbaseResponseCmd;

/***** 新增路基设备 *****/
typedef struct TsAddRoadbaseCmd
{
    TsCommandHead    tsHead;         //命令头
    TsRoadbase        m_Roadbase;        //路基组信息

    TsAddRoadbaseCmd(uint seq);
    void SetCmdParam(const TsRoadbase& roadbase);
} _PACKED_1_ TsAddRoadbaseCmd;

/***** 新增路基设备 *****/
typedef struct TsAddRoadbaseResponseCmd
{
    TsCommandHead    tsHead;         //命令头
    int              nResultCode;
    ushort           nRoadbaseID;    //路基ID
    TsAddRoadbaseResponseCmd(uint seq);

} _PACKED_1_ TsAddRoadbaseResponseCmd;


/***** 设置路基设备 *****/
typedef struct TsSetRoadbaseCmd
{
    TsCommandHead    tsHead;         //命令头
    TsRoadbase        m_Roadbase;        //路基组信息

    TsSetRoadbaseCmd(uint seq);
    void SetCmdParam(const TsRoadbase& roadbase);
} _PACKED_1_ TsSetRoadbaseCmd;

/***** 删除路基设备 *****/
typedef struct TsDeleteRoadbaseCmd
{
    TsCommandHead   tsHead;                    //命令头
    ushort            nS2EID;            //路基转换器ID
    ushort            nRoadbaseID;            //路基设备ID

    TsDeleteRoadbaseCmd(uint seq);
    void SetCmdParam(ushort transverterID, ushort roadbaseID);
} _PACKED_1_ TsDeleteRoadbaseCmd;

typedef struct TsGetRoadbaseBatteryCmd
{
    TsCommandHead   tsHead;                    //命令头
    TsGetRoadbaseBatteryCmd(uint seq);
    // void SetCmdParam(ushort transverterID, ushort roadbaseID);
} _PACKED_1_ TsGetRoadbaseBatteryCmd;

/***** 查询分析软件状态 *****/
typedef struct TsIvasGetStatusResponseCmd
{
    TsCommandHead            tsHead;         //命令头
    short                    nResultCode;    //处理结果
    int                     nStatus;        //分析软件状态，见TeIvasStatus

    TsIvasGetStatusResponseCmd(uint seq);
} _PACKED_1_ TsIvasGetStatusResponseCmd;

/***** 上传样本 *****/
typedef struct TsIvasUploadSampleCmd
{
    TsCommandHead    tsHead;         //命令头
    ushort            nDataChannelID;    //数据通道ID

    TsIvasUploadSampleCmd(uint seq);
} _PACKED_1_ TsIvasUploadSampleCmd;

/***** 添加样本 *****/
typedef struct TsIvasAddSampleCmd
{
    TsCommandHead    tsHead;             //命令头
    char            szSampleInfo[MAX_SAMPLE_INFO_LEN];    //样本信息

    TsIvasAddSampleCmd(uint seq);
    void SetCmdParam(uint imageSize);
} _PACKED_1_ TsIvasAddSampleCmd;

/***** 图片分析 *****/
typedef struct TsIvasImageAnalyzingCmd
{
    TsCommandHead    tsHead;             //命令头
    char            szImageInfo[MAX_SAMPLE_INFO_LEN];    //路基组信息

    TsIvasImageAnalyzingCmd(uint seq);
    void SetCmdParam(uint imageSize);
} _PACKED_1_ TsIvasImageAnalyzingCmd;

typedef struct TsIvasImageAnalyzingResponseCmd
{
    TsCommandHead    tsHead;             //命令头
    short            nResultCode;        //处理结果
    int             nAnalyzingResult;   //等级百分比，80以上表示正常，60 - 80表示稍不正常，60以下表示不正常

    TsIvasImageAnalyzingResponseCmd(uint seq);
} _PACKED_1_ TsIvasImageAnalyzingResponseCmd;

typedef struct TsRobotAddr
{
    unsigned short           nFrequency; //第一个无线模块为433，后面的无线模块累加
    unsigned char            nAddr;      //接到同一个无线模块默上的机器人地址   第一台地址为：0x03 后台的机器人地址累加
} _PACKED_1_ TsRobotAddr;

typedef struct TsRobotWirelessAddrResponseCmd
{
    TsCommandHead            tsHead;
    short                    nResultCode;    //处理结果
    TsRobotAddr              tsAddr;

    TsRobotWirelessAddrResponseCmd(uint seq);
    void SetCmdParam(unsigned short  frequency, unsigned char addr);
} _PACKED_1_ TsRobotWirelessAddrResponseCmd;


typedef struct TsRobotRtspMediaInfoResponseCmd
{
    TsCommandHead            tsHead;
    short                    nResultCode;    //处理结果
    RobotRtspMediaInfo       mediaInfo;

    TsRobotRtspMediaInfoResponseCmd(uint seq);
} _PACKED_1_ TsRobotRtspMediaInfoResponseCmd;


/***** 机器人就绪通知 *****/
typedef struct TsRobotReadyNotification
{
    TsCommandHead    tsHead;            //命令头
    TsRobotInfo        tsRobotInfo;    //机器人信息

    TsRobotReadyNotification(uint seq);
    void SetCmdParam(const TsRobotInfo& robotInfo);
} _PACKED_1_ TsRobotReadyNotification;


/***** 机器人在线状态通知 *****/
typedef struct TsRobotStatusNotification
{
    TsCommandHead    tsHead;            //命令头
    TsRobotStatus    tsRobotStatus;    //机器人在线状态

    TsRobotStatusNotification(uint seq);
    void SetCmdParam(const char* robotID, const TeRobotStatus status);
} _PACKED_1_ TsRobotStatusNotification;


/***** 机器人电池状态通知 *****/
typedef struct TsRobotBatteryNotification
{
    TsCommandHead    tsHead;            //命令头
    TsBatteryInfo    tsBatteryInfo;    //传感器信息

    TsRobotBatteryNotification(uint seq);
    void SetCmdParam(const TsBatteryInfo& batteryInfo);
} _PACKED_1_ TsRobotBatteryNotification;


/***** 机器人车体状态通知 *****/
typedef struct TsRobotCarStatusNotification
{
    TsCommandHead        tsHead;                    //命令头
    TsCarStatus            tsCarStatus;            //车体状态

    TsRobotCarStatusNotification(uint seq);
    void SetCmdParam(const TsCarStatus& carStatus);
} _PACKED_1_ TsRobotCarStatusNotification;


/***** 机器人传感器信息通知 *****/
typedef struct TsRobotSensorNotification
{
    TsCommandHead    tsHead;            //命令头
    TsCarStatus        tsCarInfo;    //传感器信息

    TsRobotSensorNotification(uint seq);
    void SetCmdParam(const TsCarStatus& carInfo);
} _PACKED_1_ TsRobotSensorNotification;


/***** 机器人热成像仪最高温通知 *****/
typedef struct TsRobotThermalNotification
{
    TsCommandHead        tsHead;                    //命令头
    TsRobotThermal        tsRobotThermal;            //车体状态

    TsRobotThermalNotification(uint seq);
    void SetCmdParam(const TsRobotThermal& robotThermal);
} _PACKED_1_ TsRobotThermalNotification;


/***** 机器人运行状态通知 *****/
typedef struct TsRobotRunningLogNotification
{
    TsCommandHead                tsHead;                    //命令头
    TsRobotRunningLog            tsRunningLog;        //机器人运行状态

    TsRobotRunningLogNotification(uint seq);
    void SetCmdParam(const TsRobotRunningLog& runningStatus);
} _PACKED_1_ TsRobotRunningLogNotification;

/***** 机械臂状态通知 *****/
typedef struct TsRobotArmStatusNotification
{
    TsCommandHead                tsHead;                    //命令头
    TsRobotArmStatus            tsArmStatus;            //机械臂状态

    TsRobotArmStatusNotification(uint seq);
    void SetCmdParam(const TsRobotArmStatus& armStatus);
} _PACKED_1_ TsRobotArmStatusNotification;

/***** 云台状态通知 *****/
typedef struct TsRobotPtzStatusNotification
{
    TsCommandHead                tsHead;                    //命令头
    TsRobotPtzStatus            tsPtzStatus;            //机械臂状态

    TsRobotPtzStatusNotification(uint seq);
    void SetCmdParam(const TsRobotPtzStatus& ptzStatus);
} _PACKED_1_ TsRobotPtzStatusNotification;

/***** 路基状态通知 *****/
typedef struct TsRoadbaseStatusNotification
{
    TsCommandHead        tsHead;                    //命令头
    TsRoadbase            tsRoadbase;                //路基设备信息

    TsRoadbaseStatusNotification(uint seq);
    void SetCmdParam(const TsRoadbase& roadbase);
} _PACKED_1_ TsRoadbaseStatusNotification;

/***** 液位传感器状态通知 *****/
typedef struct TsLevelSensorStatusNotification
{
    TsCommandHead         tsHead;                    //命令头
    TsLevelSensorStatus  tsLeverSensor;                //路基设备信息

    TsLevelSensorStatusNotification(uint seq);
    void SetCmdParam(const TsLevelSensorStatus& levelSensor);
} _PACKED_1_ TsLevelSensorStatusNotification;

/***** 路基充电电池状态通知 *****/
typedef struct TsRoadbaseBatteryStatusNotification
{
    TsCommandHead        tsHead;                    //命令头
    TsRoadbaseBattery   tsBattery;
    TsRoadbaseBatteryStatusNotification(uint seq);
    void SetCmdParam(const TsRoadbaseBattery& battery);
} _PACKED_1_ TsRoadbaseBatteryStatusNotification;

/***** 报警通知 *****/
typedef struct TsAlarmInfoNotification
{
    TsCommandHead        tsHead;                    //命令头
    TsAlarmInfo            tsAlarmInfo;            //报警信息

    TsAlarmInfoNotification(uint seq);
    void SetCmdParam(const TsAlarmInfo& alarmInfo);
} _PACKED_1_ TsAlarmInfoNotification;

/***** 巡检状态通知 *****/
typedef struct TsTourStatusNotification
{
    TsCommandHead        tsHead;                    //命令头
    TsTourStatus        tsTourStatus;            //巡检状态

    TsTourStatusNotification(uint seq);
    void SetCmdParam(const TsTourStatus& tourStatus);
    void SetNotifySingleStationStatus();
} _PACKED_1_ TsTourStatusNotification;

/***** 回放状态通知 *****/
typedef struct TsRetrievalStatusNotification
{
    TsCommandHead        tsHead;                    //命令头
    TsRetrievalStatus    tsRetrievalStatus;        //巡检状态

    TsRetrievalStatusNotification(uint seq);
    void SetCmdParam(const TsRetrievalStatus& retrievalStatus);
} _PACKED_1_ TsRetrievalStatusNotification;

typedef struct TsRobotRecordStatusNotification
{
    TsCommandHead           tsHead;
    TsRobotMediaStatus      tsStatus;

    TsRobotRecordStatusNotification(uint seq);
    void SetCmdParam(const TsRobotMediaStatus& status);
} _PACKED_1_ TsRobotRecordStatusNotification;

typedef struct TsRobotMediaStatusNotification
{
    TsCommandHead           tsHead;
    TsRobotMediaStatus      tsStatus;

    TsRobotMediaStatusNotification(uint seq);
    void SetCmdParam(const TsRobotMediaStatus& status);
} _PACKED_1_ TsRobotMediaStatusNotification;


/**********************************************************************/
//恢复默认对齐状态
#ifdef WIN32
    #pragma pack(pop)
#endif
/**********************************************************************/

#endif //_TS_UNS_COMMAND_H_