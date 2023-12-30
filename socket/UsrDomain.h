#ifndef _USR_DOMAIN_H_
#define _USR_DOMAIN_H_

#include "UsrCommonConst.h"

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
#define PROTOCOL_VERSIONS   "1.13"      //协议版本号

#define MAX_GROUP_LEN                16        //用户组的最大长度
#define MAX_USER_ID_LEN                16        //用户ID的长度
#define MAX_USER_NAME_LEN            32        //登录用户名的长度
#define MAX_PWD_LEN                    16        //登录密码长度
#define ROBOT_ID_LEN                8        //机器人ID的长度
#define DEV_NAME_LEN                32        //设备名称的长度
#define MAX_TYPE_LEN                17        //设备类型的最大长度
#define MAX_MODEL_LEN                17        //设备型号的最大长度
#define IPV4_LEN                    16        //IPV4的长度
#define MAX_IPC_NUM                    4        //每个机器人上摄像机最大个数
#define MAX_ROBOT_NUM                32        //系统管理的机器人的最大个数
#define MAX_LOG_LEN                    230        //一条日志的最大长度
#define MAX_VERSION_LEN             128     //版本号的最大长度
#define MAX_LAMP_NUM                4       //机器人上最大的灯光个数
#define ENM_MAX_MOUNT_DVS           2       //挂载设备的个数，机械臂、左右云台、升降云台

#define MAX_DISK_NUM                4        //最大磁盘个数
#define DISK_PART_NUM                2        //磁盘分区个数
#define DISK_PATH_LEN                32        //磁盘路径长度
#define DISK_VERSION                8        //磁盘版本

#define MAX_ROADBASE_GROUP            128        //路基组最大个数
#define MAX_ROADBASE_NUM            128        //每个路基组中路基设备最大个数

#define MAX_FILE_NAME_LEN            64        //文件名的最大长度
#define MAX_FILE_PATH_LEN            128        //文件路径的最大长度
#define MAX_SAMPLE_INFO_LEN         128     //采样数据信息最大长度

#define UNS_MAIN_STREAM                0        //主码流ID
#define UNS_SUB_STREAM                1        //子码流ID

#define MAX_STORAGE_SLIP            20        //查询录像、抓拍时，一次最多返回10个段

#define MAX_RETRIEVAL_NUM           16      //服务器支持的最大回放机器人个数
#define MAX_RETRIEVAL_CONSUMER_NUM  64      //最大的回放消费者个数，MAX_RETRIEVAL_NUM * MAX_IPC_NUM

#define MAX_MARK_NAME_LEN            64        //最大的标记名称长度
#define MAX_TOUR_ACTION_NUM            10        //每个巡检站点最多的动作个数
#define MAX_TOUR_CONCERN_NUM        16        //最大的关注点个数

#define MAX_ALARM_LOG_NUM            10        //报警日志查询一次最多返回10条
#define MAX_PAGE_NUM                10        //分页查询时每页的最大个数

#define MAX_PRIVILEGE_MODULE        32      //最大模块个数
#define MAX_MOBILE_LEN              16      //最大的电话

#define MAX_OPERATION_EXPLAIN       128    //操作说明 

#define MAX_VIA_GALLERY_NUM         20     //途经管线个数
#define MAX_RELATED_GALLERY_NUM     3      //最大关联管线个数

#define uns_deprecated              //弃用标记

enum TeDvsType
{
    ENM_DVS_ROBOT = 0,     //Robot
    ENM_DVS_CLIENT,          //Client

    ENM_MEDIA_PRODUCER,      //媒体生产者
    ENM_MEDIA_CONSUMER,      //媒体消费者

    ENM_S2E_PROXY,          //路基转换器代理

    ENM_DVS_IVAS = 10,       //图片分析
    ENM_DVS_SERVER,          //服务器
    ENM_DVS_SDK              //sdk
};

/**
* @brief 登录信息
*/
typedef struct TsLoginInfo
{
    char            sUser[MAX_USER_ID_LEN];    ///< 用户账号
    char            sPwd[MAX_PWD_LEN];        ///< 密码
    char            sDvsID[ROBOT_ID_LEN];    ///< 设备ID，设备类型为机器人时有效
    char            nDvsType;                ///< 设备类型，见TeDvsType
    ushort          nTimeout;               ///< 会话超时时间，单位豪秒，取值[0,30000]，默认5000毫秒
} _PACKED_1_ TsLoginInfo;

enum TeQueryType
{
    ENM_QUERY_SELECTED = 1,        //指定记录查询，查询 1 - MAX_PAGE_NUM 条
    ENM_QUERY_LIST,                    //列表查询
    ENM_QUERY_LIST_BY_GALLERY        //根据管廊查询列表(目前用于查询管廊内的站点)
};

/***** 查询条件 *****/
typedef struct TsQueryCondition
{
    unsigned short            nQueryType;                        //查询类型，见TeQueryType
    unsigned short            nQueryNum;                        //指定查询记录数的个数
    unsigned short            arrQueryParam[MAX_PAGE_NUM];    //查询参数，指定记录查询时填充指定参数，列表查询时为起始位置
} _PACKED_1_ TsQueryCondition;

/***** 角色信息 *****/
typedef struct TsRoleInfo
{
    uint                nRoleID;                        //角色ID
    char                szRoleName[MAX_MARK_NAME_LEN];  //角色名称
} _PACKED_1_ TsRoleInfo;

/***** 角色信息查询结果 *****/
typedef struct TsRoleInfoQueryResult
{
    unsigned short        nBeginPos;            //开始位置
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsRoleInfo            arrRoleInfo[MAX_PAGE_NUM];
} _PACKED_1_ TsRoleInfoQueryResult;

enum TeModule
{
    ENM_MODULE_MIN = 1,                    //模块开始

    ENM_MODULE_RT_INFO = ENM_MODULE_MIN,    //实时界面->实时信息查询
    ENM_MODULE_RT_LIVE_PRIVIEW,             //实时界面->实时视频控制
    ENM_MODULE_RT_ROBOT_CTRL,               //实时界面->机器人控制
    ENM_MODULE_RT_MOUNT_CTRL,               //实时界面->挂载设备控制
    ENM_MODULE_RT_ROADBASE_CTRL,            //实时界面->路基控制

    ENM_MODULE_DATA_ALARM,                  //数据报表界面->报警信息查询
    ENM_MODULE_DATA_TOUR_REPORT,            //数据报表界面->巡检报告查询

    ENM_MODULE_SYS_TOUR,                    //系统配置->巡检配置
    ENM_MODULE_SYS_ROADBASE,                //系统配置->路基配置
    ENM_MODULE_SYS_ALARM,                   //系统配置->告警配置
    ENM_MODULE_SYS_USER,                    //系统配置->用户管理
    ENM_MODULE_SYS_ROLE,                    //系统配置->角色管理

    ENM_MODULE_MAX = ENM_MODULE_SYS_ROLE    //模块最大值
};
/***** 模块权限 *****/
typedef struct TsModulePrivilege
{
    uint        nModuleID;      //模块ID，见 TeModule
    uint        nPrivilege;     //模块权限
} _PACKED_1_ TsModulePrivilege;

//角色权限
typedef struct TsRolePrivilege
{
    uint                nRoleID;                                //角色ID
    ushort              nPrivilegeNum;                          //权限个数
    TsModulePrivilege   arrPrivilege[MAX_PRIVILEGE_MODULE];     //角色模块权限
} _PACKED_1_ TsRolePrivilege;

/***** 用户信息 *****/
typedef struct TsUserInfo
{
    char        szUserID[MAX_USER_ID_LEN];          //用户账号
    char        szUserName[MAX_USER_NAME_LEN];      //用户名称
    char        szPwd[MAX_PWD_LEN];                 //用户密码
    uint        nRoleID;                            //用户ID
    char        szDepartment[MAX_MARK_NAME_LEN];    //用户部门
    char        szPosition[MAX_MARK_NAME_LEN];      //用户职务
    char        szMobile[MAX_MOBILE_LEN];           //用户电话
} _PACKED_1_ TsUserInfo;

/***** 用户信息查询结果 *****/
typedef struct TsUserInfoQueryResult
{
    unsigned short        nBeginPos;            //开始位置
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsUserInfo            arrUserInfo[MAX_PAGE_NUM];
} _PACKED_1_ TsUserInfoQueryResult;

/***** 摄像机类型 *****/
enum TeIPCameraType
{
    ENM_IPC_XM = 0,                        //雄迈
    ENM_IPC_HYDF,                        //华源大方
    ENM_IPC_HYK,                        //海运康
    ENM_IPC_HIKVISION_THERMAL            //海康双视云台
};

/***** 音频支持类型 *****/
enum TeAudioSupported
{
    AUDIO_NO = 0,        //不支持音频
    AUDIO_ONE_WAY,        //单向音频
    AUDIO_TALKBACK      //对讲
};

/***** 摄像机信息 *****/
uns_deprecated typedef struct TsIPCameraInfo    //长度为86 Bytes
{
    unsigned short        uChannelID;                     //通道ID
    unsigned short        uDvsType;                     //设备类型
    char                sName[DEV_NAME_LEN];         //通道名称
    char                sIP[IPV4_LEN];                 //设备IP
    unsigned short        uPort;                         //设备端口
    char                sUser[MAX_USER_ID_LEN];         //用户账号
    char                sPwd[MAX_PWD_LEN];             //密码
    short               nAudioSupported;             //是否支持音频,见TeAudioSupported
} _PACKED_1_ TsIPCameraInfo;

/***** 摄像机摘要信息 *****/
uns_deprecated typedef struct TsIPCSummaryInfo
{
    unsigned short        uChannelID;                     //通道ID
    char                sName[DEV_NAME_LEN];         //通道名称
    short               nAudioSupported;             //是否支持音频,见TeAudioSupported
} _PACKED_1_ TsIPCSummaryInfo;


/***** 媒体通道信息 *****/
uns_deprecated typedef struct TsMediaChannelInfo
{
    char                    sRobotID[ROBOT_ID_LEN];            //机器人ID
    unsigned short            nCameraNum;                        //摄像机个数
    TsIPCameraInfo          arrIPCameraInfo[MAX_IPC_NUM];    //机器人信息列表
} _PACKED_1_ TsMediaChannelInfo;

/***** 媒体通道摘要信息 *****/
uns_deprecated typedef struct TsMediaSummaryInfo
{
    char                    sRobotID[ROBOT_ID_LEN];            //机器人ID
    unsigned short            nCameraNum;                        //摄像机个数
    TsIPCSummaryInfo        arrIPCSummaryInfo[MAX_IPC_NUM];    //机器人信息列表
} _PACKED_1_ TsMediaSummaryInfo;


/***** 摄像机信息 *****/
typedef struct IpcInfo    //长度为86 Bytes
{
    unsigned short      _ipcID;                 //通道ID
    unsigned short      _dvsType;               //设备类型
    char                _ip[IPV4_LEN];          //设备IP
    unsigned short      _port;                  //设备端口
    char                _user[MAX_USER_ID_LEN]; //用户账号
    char                _pwd[MAX_PWD_LEN];      //密码
} _PACKED_1_ IpcInfo;

/***** 摄像机信息 *****/
typedef struct RtspIpcInfo    //长度为86 Bytes
{
    unsigned short      _ipcID;                 //通道ID
    unsigned short      _dvsType;               //设备类型
    char                _ip[IPV4_LEN];          //设备IP
    unsigned short      _port;                  //设备端口
    char                _user[MAX_USER_ID_LEN]; //用户账号
    char                _pwd[MAX_PWD_LEN];      //密码
    char                _streamUri[256];       //rtsp拉流地址
    char                _snapshotUri[256];     //rtsp抓拍地址
} _PACKED_1_ RtspIpcInfo;

/***** 媒体通道信息 *****/
typedef struct ChannelInfo
{
    ushort      _channelID;                 //机器人ID
    char        _channelName[DEV_NAME_LEN]; //通道名称
    ushort      _ipcID;                     //通道对应的的IPC的ID
    short       _audioSupportedType;        //是否支持音频,见TeAudioSupported
    ushort      _streamType;                //使用的流类型，0 - MainStream, 1 - SubStream
    ushort      _mainStreamID;              //主码流ID
    ushort      _subStreamID;               //字码流ID
} _PACKED_1_ ChannelInfo;

/***** 媒体通道信息 *****/
typedef struct ChannelSummaryInfo
{
    ushort      _channelID;                 //机器人ID
    char        _channelName[DEV_NAME_LEN]; //通道名称
    short       _audioSupportedType;        //是否支持音频,见TeAudioSupported
} _PACKED_1_ ChannelSummaryInfo;

/***** 媒体通道信息 *****/
typedef struct RobotMediaInfo
{
    char                _robotID[ROBOT_ID_LEN];     //机器人ID
    unsigned short      _channelNum;                //通道个数
    ChannelInfo         _channelInfos[MAX_IPC_NUM]; //通道信息列表
    ushort              _ipcNum;                    //IPC个数
    IpcInfo             _ipcInfos[MAX_IPC_NUM];     //IPC信息列表
} _PACKED_1_ RobotMediaInfo;

/***** 媒体通道摘要信息 *****/
typedef struct RobotMediaSummaryInfo
{
    char               _robotID[ROBOT_ID_LEN];            //机器人ID
    unsigned short     _channelNum;                       //摄像机个数
    ChannelSummaryInfo _channelSummaryInfos[MAX_IPC_NUM]; //机器人信息列表
} _PACKED_1_ RobotMediaSummaryInfo;

/***** 媒体通道信息 *****/
typedef struct RobotRtspMediaInfo
{
    char                _robotID[ROBOT_ID_LEN];     //机器人ID
    unsigned short      _channelNum;                //通道个数
    ChannelInfo         _channelInfos[MAX_IPC_NUM]; //通道信息列表
    ushort              _ipcNum;                    //IPC个数
    RtspIpcInfo         _rtsIpcInfos[MAX_IPC_NUM];     //IPC信息列表

} _PACKED_1_ RobotRtspMediaInfo;

/***** 机器人延伸臂类型 *****/
enum TeRobotArmType
{
    ENM_ARM_NON = 0,    //无
    ENM_ARM_SixAxis,            //六轴机械臂
    ENM_ARM_CRANE               //升降架
};

static const unsigned int CST_SENSOR_O2 = 0x00000001;       //氧气
static const unsigned int CST_SENSOR_CH4 = 0x00000002;       //甲烷
static const unsigned int CST_SENSOR_H2S = 0x00000004;       //硫化氢
static const unsigned int CST_SENSOR_NH3 = 0x00000008;       //氨气
static const unsigned int CST_SENSOR_Temperature = 0x00000010;       //温度
static const unsigned int CST_SENSOR_Humidity = 0x00000020;       //湿度

/***** 机器人信息 *****/
typedef struct TsRobotInfo
{
    char            sRobotID[ROBOT_ID_LEN];     //机器人ID
    char            sName[DEV_NAME_LEN];        //机器人名称
    char            sType[MAX_TYPE_LEN];        //机器人类型
    char            sModel[MAX_MODEL_LEN];      //机器人型号
    float           nMaxSpeed;                  //最大速度, 单位：m/s
    float           nRatedSpeed;                //额定速度, 单位：m/s
    //续航时间
    //量程
    unsigned short  nCameraNum;                 //摄像机个数
    unsigned char   bSupportedThermal;          //是否支持热成像
    unsigned char   nPtzNum;                    //云台个数
    unsigned char   nArmType;                   //是否支持机械臂
    unsigned int    nSensorType;                //气体传感器类型
} _PACKED_1_ TsRobotInfo;

/***** 机器人信息查询结果 *****/
typedef struct TsRobotInfoQueryResult
{
    unsigned short        nBeginPos;            //开始位置
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsRobotInfo            arrRobotInfo[MAX_PAGE_NUM];
} _PACKED_1_ TsRobotInfoQueryResult;


/***** 数据源信息 *****/
typedef struct TsMediaSourceID
{
    char                sRobotID[ROBOT_ID_LEN];
    unsigned short        nChannelID;
    unsigned short        nStreamID;
} _PACKED_1_ TsMediaSourceID;


/***** 数据包类型 *****/
enum TePacketPayloadType
{
    ENM_PACKET_PAYLOAD_CMD = 0, //命令
    ENM_PACKET_PAYLOAD_MEDIA,    //媒体数据
    ENM_PACKET_PAYLOAD_FILE        //文件
};

/***** 流数据类型 *****/
enum TeStreamType
{
    ENM_STREAM_TYPE_UNKNOWN = 0,    //未知类型
    ENM_STREAM_TYPE_VIDEO = 1,    //视频流
    ENM_STREAM_TYPE_AUDIO = 2    //音频流
};

/***** 流编码类型 *****/
enum TeEncoderType
{
    ENM_ENCODER_TYPE_UNKNOWN = 0,    //未知类型
    ENM_ENCODER_TYPE_H264 = 1,    //视频H264编码
    ENM_ENCODER_TYPE_H265 = 2,    //视频H265编码

    ENM_ENCODER_TYPE_G711 = 10    //音频G711编码
};

/***** 帧类型 *****/
enum TeFrameType
{
    ENM_FRAME_TYPE_UNKNOWN = 0,    //未知类型
    ENM_FRAME_TYPE_I = 1,    //I帧
    ENM_FRAME_TYPE_P = 2    //P帧
};

/***** 视频制式 *****/
enum TeVideoFormat
{
    ENM_VIDEO_FORMAT_UNKNOWN = 0,    //未知类型
    ENM_VIDEO_FORMAT_NTSC = 1,        //N制
    ENM_VIDEO_FORMAT_PAL = 2        //P制
};

/***** 视频数据头 *****/
typedef struct TsMediaFrameHead
{
    char            sDeviceID[ROBOT_ID_LEN];    //设备ID
    unsigned short    nChannelID;                    //视频通道号
    unsigned short    nStreamID;                    //流编号

    unsigned short    nStreamType;                //流类型，TeStreamType
    unsigned short    nEncoderType;                //编码格式,TeEncoderType
    unsigned int    nSequenceId;                //数据帧序号
    unsigned short    nFrameType;                    //数据帧类型,TeFrameType
    unsigned short    nFrameRate;                    //帧率
    unsigned short    nBitRate;                    //当前码率　
    unsigned short    nImageWidth;                //视频宽度
    unsigned short    nImageHeight;                //视频高度
    unsigned short    nVideoFormat;                //当前视频制式,TeVideoFormat
    INT64            nTimestamp;                    //数据采集时间戳，单位为毫秒
    //int m_nTimezone;                            //时区
    //int m_nDaylightSavingTime;                //夏令时
    unsigned int    nDataLength;                //数据有效长度
} _PACKED_1_ TsMediaFrameHead;
const int CST_MEDIA_FRAME_HEAD_LEN = sizeof(TsMediaFrameHead);

/***** 视频帧 *****/
typedef struct TsMediaFrame
{
    TsMediaFrameHead    tsMediaFrameHead;

    char*                pszData;                                //数据
    unsigned int        nDataBufSize;                            //当前缓冲长度
} _PACKED_1_ TsMediaFrame;


/***** 存储类型 *****/
enum TeStorageType
{
    ENM_STORAGE_T_RECORD = 0,    //录像存储
    ENM_STORAGE_T_SNAPSHOT        //抓拍存储
};

/***** 回放控制类型 *****/
enum TeRetrievalCtrlType
{
    ENM_RETRIEVAL_NEXT_FRAME = 0,        //下一帧，对应操作：正常播放、慢播、单帧
    ENM_RETRIEVAL_NEXT_I_FRAME,            //下一个I帧，对应操作：快进
    ENM_RETRIEVAL_PREVIOUS_I_FRAME,        //上一个I帧，对应操作：快退
    ENM_RETRIEVAL_LOCATE,                //定位，对应操作：定位时间点
    ENM_RETRIEVAL_PAUSE,                //暂停，对应操作：暂停
};

/***** 抓拍控制 *****/
enum TeSnapshotCtrlType
{
    ENM_START_SNAPSHOT = 0,    //开始抓拍
    ENM_STOP_SNAPSHOT        //停止抓拍
};

//媒体SDK类型
enum TeMediaSdkType
{
    SDK_LIVE_PREVIEW = 0,    //实时预览
    SDK_STORAGE_RETRIEVAL            //录像取回
};

/***** 通道录像策略 *****/
typedef struct TsChannelRecordPolicy    //长度5
{
    unsigned short        uChannelID;                            //通道ID
    unsigned short        uStreamID;                            //通道ID
    bool                bEnable;                            //使能
} _PACKED_1_ TsChannelRecordPolicy;

/***** 机器人录像策略 *****/
typedef struct TsRecordPolicy    //长度746
{
    char                    sRobotID[ROBOT_ID_LEN];                    //机器人ID
    unsigned char            nPolicyNum;
    TsChannelRecordPolicy    arrChannelRecordPolicy[MAX_IPC_NUM];
} _PACKED_1_ TsRecordPolicy;


/***** 机器人录像日历 *****/
typedef struct TsRecordCalendar
{
    char                    sRobotID[ROBOT_ID_LEN];                    //机器人ID
    unsigned int            nYearMonth;
    unsigned int            nRecordCalendar;
} _PACKED_1_ TsRecordCalendar;

/***** 存储查询条件 *****/
typedef struct TsStorageQueryCondition
{
    char            sRobotID[ROBOT_ID_LEN];    //机器人ID
    unsigned short    nChannelID;
    unsigned short    nStorageType;    //存储类型，参见TeStorageType
    INT64            nBeginTime;        //单位：毫秒
    INT64            nEndTime;        //单位：毫秒
} _PACKED_1_ TsStorageQueryCondition;


/***** 录像片段 *****/
typedef struct TsRecordSlip
{
    INT64            nBeginTime;
    INT64            nEndTime;
} _PACKED_1_ TsRecordSlip;

/***** 抓拍片段 *****/
typedef INT64 TsSnapshotSlip;

/***** 存储片段 *****/
union TuStorageSlip
{
    TsRecordSlip        arrRecordSlip[MAX_STORAGE_SLIP];        //录像段列表，一次查询最多返回的段
    TsSnapshotSlip        arrSnapshotSlip[MAX_STORAGE_SLIP * 2];
};

/***** 存储查询结果 *****/
typedef struct TsStorageQueryResult
{
    char                sRobotID[ROBOT_ID_LEN];    //机器人ID
    unsigned short        nChannelID;                //通道ID
    unsigned short        nTotalSlip;                //查询总分片个数
    unsigned short        nSlipNum;                //当前分片个数
    TuStorageSlip        tuStorageSlip;            //录像、抓拍数据分片
} _PACKED_1_ TsStorageQueryResult;


/***** 存储数据回放条件 *****/
typedef struct TsRetrievalInfo
{
    char                    sRobotID[ROBOT_ID_LEN];    //机器人ID
    unsigned short            nChannelID;                //通道ID
    unsigned short            nStorageType;            //存储类型，参见：TeStorageType
    INT64                    nBeginTime;                //开始时间，单位：毫秒(为兼容抓拍时间)
    INT64                    nEndTime;                //结束时间，单位：毫秒
} _PACKED_1_ TsRetrievalInfo;

/***** 机器人回放定位时间 *****/
typedef struct TsRetrievalLocateTime
{
    char            sRobotID[ROBOT_ID_LEN];    //机器人ID
    INT64           arrFrameTimestamp[MAX_IPC_NUM];
} _PACKED_1_ TsRetrievalLocateTime;

/***** 抓拍类型 *****/
enum TeSnapshotType
{
    ENM_SNAPSHOT_MANUAL,        //手动抓拍
    ENM_SNAPSHOT_SCHEDULE        //计划抓拍
};

/***** 抓拍任务 *****/
typedef struct TsSnapshotTask
{
    unsigned short        usSnapshotType;        //抓拍类型，0 手动抓拍，1 计划抓拍
    unsigned short        usSnapshotTime;        //抓拍次数
    unsigned short        usIntervalSec;        //抓拍间隔，单位:秒
} _PACKED_1_ TsSnapshotTask, *PTsSnapshotTask;

/***** 磁盘使用情况 *****/
typedef struct TsDiskState
{
    char            sName[DISK_PATH_LEN];//磁盘名称,不含/dev，如sdb
    INT64            nTotalSize;
    INT64            nRemainSize;

} _PACKED_1_ TsDiskState;

/***** 磁盘使用概览 *****/
typedef struct TsDiskOverview
{
    unsigned short        nDiskNum;
    TsDiskState            arrDiskState[MAX_DISK_NUM];

} _PACKED_1_ TsDiskOverview;


/***** 升级状态 *****/
typedef struct TsDvsUpgradeStatus
{
    int                    nStatus;        //升级状态
    unsigned int        nDataLen;        //已接收的数据长度，字节
    unsigned int        nTotalSize;        //数据总长，字节
} _PACKED_1_ TsDvsUpgradeStatus;


/***** 机器人运动控制参数 *****/
typedef struct TsRobotMotion
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    short                nSpeed;                        //机器人运行速度，单位：毫米每秒，取值[-1000, 1000]。符号表示方向，> 0 表示前进，= 0 表示停止，< 0 表示后退；速度值越大，车速越快
} _PACKED_1_ TsRobotMotion;

/***** 机器人压力轮参数 *****/
typedef struct TsRobotPressure
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    unsigned short        nPressure;                    //压力值，取值[0, 100]
} _PACKED_1_ TsRobotPressure;

/***** 灯光参数 *****/
typedef struct TsLampParam
{
    unsigned short        nLampID;                    //灯编号
    unsigned char        nLamp;                        //灯光亮度，取值[0, 100]
} _PACKED_1_ TsLampParam;

/***** 机器人灯光控制参数 *****/
typedef struct TsRobotLamp
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    TsLampParam         lamp;                       //灯光参数
} _PACKED_1_ TsRobotLamp;

/***** 机器人灯光状态参数 *****/
typedef struct TsRobotLampStatus
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    ushort              nLampNum;                   //灯光参数个数
    TsLampParam         arrLamp[MAX_LAMP_NUM];      //灯光参数
} _PACKED_1_ TsRobotLampStatus;

/***** 机器人避障参数 *****/
typedef struct TsRobotAvoidObstacle
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    ushort              nAvoidObstacle;             //避障开关，0 表示关，非 0 表示开
} _PACKED_1_ TsRobotAvoidObstacle;

/***** 机器人驻车控制 *****/
typedef struct TsRobotParking
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    unsigned char        nParking;                    //驻车标识，取值[0, 1]。1 表示驻车， 0 表示未驻车
} _PACKED_1_ TsRobotParking;

/***** 机器人暂停巡检控制 *****/
typedef struct TsRobotTourCtrl
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    unsigned char        nAction;                    //驻车标识，取值[0,255]。 TeRobotTourCtrl
} _PACKED_1_ TsRobotTourCtrl;

/***** 机器人位置 *****/
typedef struct TsRobotLocation
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    int                    nLocation;                    //位置，单位：毫米
} _PACKED_1_ TsRobotLocation;


/***** 机械臂角度 *****/
typedef struct TsRobotArmAngle
{
    float        arm1; //机械臂转动角度，取值[-180, 180],云台水平角度
    float        arm2; //云台垂直角度
    float        arm3; //升降架高度
    float        arm4;
    float        arm5;
    float        arm6;
} _PACKED_1_ TsRobotArmAngle;


enum TeRobotArmCmdType
{
    ENM_ROBOT_ARM_CMD_TYPE_MOVE_REL_J = 0,
    ENM_ROBOT_ARM_CMD_TYPE_MOVE_J,
    ENM_ROBOT_ARM_CMD_TYPE_PICKUP,          //机械臂收起
    ENM_ROBOT_ARM_CMD_TYPE_POWER_ON,        //使能
    ENM_ROBOT_ARM_CMD_TYPE_POWER_OFF,       //去使能
    ENM_ROBOT_ARM_CMD_TYPE_TEACH_ON,        //开启零力示教
    ENM_ROBOT_ARM_CMD_TYPE_TEACH_OFF,       //关闭零力示教
    ENM_ROBOT_ARM_CMD_TYPE_START_MASTER,    //启动主站
    ENM_ROBOT_ARM_CMD_TYPE_CLOSE_MASTER,    //关闭主站
    ENM_ROBOT_ARM_CMD_TYPE_SET_SPEED,       //设置机械臂运动速度

    ENM_ROBOT_ARM_CMD_TYPE_MOVE_STOP,       //运动停止
    ENM_ROBOT_ARM_CMD_TYPE_MOVE_FRONT,      //向前运动
    ENM_ROBOT_ARM_CMD_TYPE_MOVE_BACK,       //向后运动
    ENM_ROBOT_ARM_CMD_TYPE_MOVE_LEFT,       //向左运动
    ENM_ROBOT_ARM_CMD_TYPE_MOVE_RIGHT,      //向右运动
    ENM_ROBOT_ARM_CMD_TYPE_MOVE_UP,         //向上运动
    ENM_ROBOT_ARM_CMD_TYPE_MOVE_DOWN        //向下运动
};

/***** 机械臂控制命令 *****/
typedef struct TsRobotArmCtrl
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    short                armCtrlCmd;                    //TeRobotArmCmdType
    short                speed;                        //armCtrlCmd 为 SET_SPEED 时使用，范围[0, 100]
    short                armID;                        //armCtrlCmd 为 MOVE_REL_J 时使用，范围[1, 6]
    short                step;                        //配合 armID 使用,范围[1, 10]
    TsRobotArmAngle        armAngle;                    //armCtrlCmd 为 MOVE_J 时使用
} _PACKED_1_ TsRobotArmCtrl;

/***** 抓拍参数 *****/
//typedef struct TsSnapshotParam
//{
//    unsigned char        nSnapshotTimes;        //抓拍次数，0 不抓拍
//    unsigned char        nSnapshotInterval;    //抓拍间隔
//}_PACKED_1_ TsSnapshotParam;

enum TeRobotTourCtrl
{
    ENM_ROBOT_TOUR_CTR_IDE = 0,
    ENM_ROBOT_TOUR_PAUSE,       //暂停巡检
    ENM_ROBOT_TOUR_CONTINUE,      //继续巡检
    ENM_ROBOT_TOUR_STOP         //终止巡检
};


enum TeMountDvsType
{
    ENM_MOUNT_SENSOR = 1,    //传感器数据采集
    ENM_MOUNT_ARM,                //机械臂
    ENM_MOUNT_LIFT_PTZ,        //升降云台，含普通云台
    ENM_MOUNT_LR_PTZ           //左右云台
};

/***** 抓拍位置 *****/
typedef struct TsSnapshotPosition
{
    uchar               cEnable;        //抓拍使能标记
    TsRobotArmAngle     tsArmAngle;     //机械臂、云台角度等
    ushort              nZoom;          //镜头变倍，0 无意义，大于0 表示镜头倍数
    uchar               cThermal;       //采集热成像最高温的标记
} _PACKED_1_ TsSnapshotPosition;

/***** 巡检动作 *****/
typedef struct TsTourAction
{
    uchar                cType;                        //挂载设备类型，见 TeMountDvsType
    char                sName[MAX_MARK_NAME_LEN];    //动作名称
    uint                nDetectedDvsType;           //检测设备的类型，用于图片分析，根据项目专门配置
    ushort              nDelayTime;                 //准备时间
    uchar               nSnapshotTimes;             //抓拍次数
    uchar               nSnamshotInterval;          //抓拍间隔，秒
    TsSnapshotPosition  arrSnapshotPosition[ENM_MAX_MOUNT_DVS];     //抓拍位置（1、机械臂、升降云台只用第一个；2、左右云台，左云台用第一个、右云台用第二个
} _PACKED_1_ TsTourAction;

/***** 管廊信息 *****/
typedef struct TsPipeGallery
{
    unsigned short        nGalleryID;                    //管廊ID
    char                sName[MAX_MARK_NAME_LEN];    //管廊名称
    unsigned int        nLength;                    //管廊长度
    unsigned char        cIsCircle;                    //是否环形轨道
} _PACKED_1_ TsPipeGallery;

/***** 管廊信息查询结果 *****/
typedef struct TsPipeGalleryQueryResult
{
    unsigned short        nBeginPos;            //开始位置
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsPipeGallery        arrPipeGallery[MAX_PAGE_NUM];
} _PACKED_1_ TsPipeGalleryQueryResult;


/***** 机器人巡检站点 *****/
typedef struct TsTourStation
{
    unsigned short        nStationID;                            //巡检站点ID;
    unsigned short        nGalleryID;                            //巡检点所在的管廊ID
    char                sName[MAX_MARK_NAME_LEN];            //站点名称
    int                 nBeginLocation;                        //开始位置，单位：毫米
    int                 nEndLocation;                        //结束位置，单位：毫米
    unsigned short        nSpeed;                                //站点运行速度
    unsigned short        nActionNum;                            //动作个数
    TsTourAction        arrAction[MAX_TOUR_ACTION_NUM];        //站点动作列表
} _PACKED_1_ TsTourStation;

/***** 巡检站点查询结果 *****/
typedef struct TsTourStationQueryResult
{
    unsigned short        nBeginPos;            //开始位置,仅列表查询时有效
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsTourStation        arrTourStation[MAX_PAGE_NUM];
} _PACKED_1_ TsTourStationQueryResult;


#define    MAX_TOUR_LINE_STATION_NUM            64
/***** 机器人巡检线路 *****/
typedef struct TsTourLine
{
    unsigned short        nLineID;                                //巡检线路ID;
    char                sName[MAX_MARK_NAME_LEN];                //线路名称
    unsigned char        cStationNum;                            //巡检站点个数
    unsigned short        arrStation[MAX_TOUR_LINE_STATION_NUM];    //巡检站点ID列表
} _PACKED_1_ TsTourLine;

/***** 巡检线路查询结果 *****/
typedef struct TsTourLineQueryResult
{
    unsigned short        nBeginPos;            //开始位置,仅列表查询时有效
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsTourLine            arrTourLine[MAX_PAGE_NUM];
} _PACKED_1_ TsTourLineQueryResult;

enum TeWeekDay
{
    SUNDAY = 0,    //星期天, linux时间从0开始
    MONDAY = 1,    //星期一
    TUESDAY = 2,    //星期二
    WEDNESDAY = 3,    //星期三
    THURSDAY = 4,    //星期四
    FRIDAY = 5,    //星期五
    SATURDAY = 6        //星期六
};

#define MAX_WEEK_DAYS            7    //一周最大天数
#define MAX_DAY_SCHEDULE_NUM    3    //一天最多计划数

typedef struct TsScheduleItem
{
    unsigned int        nBeginTime;  //秒，0 - 86400
    char                sRobotID[ROBOT_ID_LEN];
} _PACKED_1_ TsScheduleItem;

typedef struct TsScheduleWeek
{
    unsigned char    cWeekDay;                                    //星期,见TeWeekDay
    unsigned char    cTimeNum;
    TsScheduleItem    arrScheduleItem[MAX_DAY_SCHEDULE_NUM];        //计划时间点列表
} _PACKED_1_ TsScheduleWeek;

enum TeTourType
{
    ENM_TOUR_TYPE_SCHEDULE = 0,    //计划巡检
    ENM_TOUR_TYPE_ONCE,                    //单次立即巡检
    ENM_TOUR_TYPE_MANUAL,                //手动巡检

    ENM_TOUR_TYPE_ALL = 10

};

/***** 机器人巡检任务 *****/
typedef struct TsTourTask
{
    ushort                nTaskID;                            //巡检任务ID;
    char                sName[MAX_MARK_NAME_LEN];            //任务名称
    ushort              nLineID;                            //巡检线路ID
    uchar               nEnable;                            //使能标记
    uchar               nTourType;                            //巡检类型，见TeTourType
    uchar               nIsIntelligentAnalysis;             //是否智能分析
    char                sRobotID[ROBOT_ID_LEN];                //单次立即执行时，机器人ID
    uint                nPerformTime;                       //执行时间，服务器下发任务到机器人时使用
    TsScheduleWeek        arrScheduleWeek[MAX_WEEK_DAYS];        //计划时间
} _PACKED_1_ TsTourTask;

/***** 巡检任务查询结果 *****/
typedef struct TsTourTaskQueryResult
{
    unsigned short        nBeginPos;            //开始位置,仅列表查询时有效
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsTourTask            arrTourTask[MAX_PAGE_NUM];
} _PACKED_1_ TsTourTaskQueryResult;


/***** 巡检任务调度查询条件 *****/
typedef struct TsTourTaskDispatchQueryCondition
{
    unsigned char        cWeekday;        //星期
    unsigned int        nBeginTime;        //开始时间
    unsigned int        nEndTime;        //结束时间
    unsigned short        nQueryPos;        //查询下标
} _PACKED_1_ TsTourTaskDispatchQueryCondition;

/***** 巡检任务ID查询结果 *****/
typedef struct TsTourTaskIDQueryResult
{
    unsigned short        nBeginPos;            //开始位置,仅列表查询时有效
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    unsigned short        arrTaskID[MAX_PAGE_NUM];
} _PACKED_1_ TsTourTaskIDQueryResult;

/***** 机器人手动巡检操作类型 *****/
enum TeManualTourAction
{
    ENM_MANUAL_TOUR_STOP = 0,    //停止手动巡检
    ENM_MANUAL_TOUR_START,              //开始手动巡检
    ENM_MANUAL_TOUR_SENSOR,             //气体传感器采集
    ENM_MANUAL_TOUR_SNAPSHOT,           //抓拍
    ENM_MANUAL_TOUR_THERMAL             //采集热成像最高温
};

/***** 机器人手动巡检参数 *****/
typedef struct TsManualTourParam
{
    char            sRobotID[ROBOT_ID_LEN];        //机器人ID
    ushort          nAction;                    //手动巡检动作，见 TeManualTourAction
} _PACKED_1_ TsManualTourParam;

/***** 站点检测参数 *****/
typedef struct TsStationDetection
{
    ushort          nTaskID;                            //任务ID
    uint            nBeginTime;                         //开始时间
    char            sRobotID[ROBOT_ID_LEN];                //机器人ID
    ushort          arrViaGallery[MAX_VIA_GALLERY_NUM]; //途经管线ID列表
    ushort          nNum;                               //途经管线个数
    ushort          stationID;                          //站点ID
} _PACKED_1_ TsStationDetection;

/***** 巡检报告 *****/
//typedef struct TsTourReport
//{
//    unsigned short        nTaskID;                    //任务ID
//    char                sName[MAX_MARK_NAME_LEN];    //任务名称
//    unsigned char        nPerformType;                //执行类型，见TePerformType
//    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
//    unsigned int        nBeginTime;                    //任务开始时间，单位秒
//    unsigned int        nEndTime;                    //任务结束时间，单位秒
//    char                sFile[MAX_FILE_NAME_LEN];    //报告文件名，不含路径
//    unsigned int        nFileLen;                    //文件长度
//}_PACKED_1_ TsTourReport;


///***** 巡检状态 *****/
typedef struct TsTourStatus
{
    ushort                nTaskID;                        //任务ID
    char                szTaskName[MAX_MARK_NAME_LEN];    //任务名称
    uchar                nTourType;                        //执行类型，见TeTourType
    uchar               bIsIntelligentAnalysis;         //是否智能分析
    char                sRobotID[ROBOT_ID_LEN];            //机器人ID
    char                sRobotName[MAX_MARK_NAME_LEN];  //机器人名称
    uint                nBeginTime;                        //开始时间，单位秒
    uint                   nUpdateTime;                    //更新状态的时间，任务结束后为结束时间，单位秒
    ushort              nDetectedNum;                   //已检测站点个数
    ushort              nTotalStationNum;               //总巡检点个数
    ushort                nStatus;                        //巡检状态，见TeTourStatus
    short                nStatusParam;                    //状态参数，Status为 RUNNING 的两种状态时，为StationID
    short               nErrCode;                       //0正常、<0 错误
    char                sFile[MAX_FILE_NAME_LEN];        //报告文件名，不含路径
    uint                nFileLen;                        //文件长度
} _PACKED_1_ TsTourStatus;

/***** 上传下载巡检报告 *****/
typedef struct TsUploadDownloadTourReport
{
    TsTourStatus        tourStatus;                     //巡检状态，下载时只用到文件名
    char                bGetImage;                      //是否下载图片标记
    unsigned short        nDataChannel;                    //数据传输通道
    char                bSingleStation;                 //单一站点的巡检信息
} _PACKED_1_ TsUploadDownloadTourReport;

/***** 巡检报告查询条件 *****/
typedef struct TsTourReportQueryCondition
{
    char                sRobotID[ROBOT_ID_LEN];            //机器人ID
    unsigned char       TourType;                        //巡检类型
    unsigned int        TourReportStatus;                //巡检报告状态
    unsigned int        nBeginTime;                        //开始时间，秒
    unsigned int        nEndTime;                        //结束时间，秒
    unsigned short        nQueryPos;                        //查询下标
} _PACKED_1_ TsTourReportQueryCondition;

/***** 巡检报告查询结果 *****/
typedef struct TsTourReportQueryResult
{
    unsigned short        nBeginPos;            //开始位置,仅列表查询时有效
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsTourStatus        arrReport[MAX_PAGE_NUM];    //巡检报告信息
} _PACKED_1_ TsTourReportQueryResult;

///***** 巡检状态摘要 *****/
typedef struct TsSummaryTourStatus
{
    char                sRobotID[ROBOT_ID_LEN];            //机器人ID
    ushort              nTourSucessNum;                 //巡检完成数量
    ushort              nTourringNum;                   //正在巡检的数量
    ushort              nTourFeiledNum;                 //巡检失败数量
} _PACKED_1_ TsSummaryTourStatus;


/***** 巡检报告查询结果 *****/
typedef struct TsSummaryTourReportQueryResult
{
    unsigned short        nBeginPos;            //开始位置,仅列表查询时有效
    unsigned short        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsSummaryTourStatus        arrReport[MAX_PAGE_NUM];    //巡检报告信息
} _PACKED_1_ TsSummaryTourReportQueryResult;


/***** 机器人巡检参数 *****/
typedef struct TsRobotTour
{
    char                sRobotID[ROBOT_ID_LEN];                //机器人ID
    unsigned short        nConcernNum;                        //兴趣点个数
    TsTourStation        arrStation[MAX_TOUR_CONCERN_NUM];    //巡检兴趣点
} _PACKED_1_ TsRobotTour;

/***** 机器人自动巡检参数 *****/
typedef struct TsRobotAutoTour
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    int                 nBeginLocation;                //巡检开始位置
    int                 nEndLocation;                //巡检开始位置
    unsigned char        nTourTime;                    //巡检次数
} _PACKED_1_ TsRobotAutoTour;

/***** 充电操作类型 *****/
enum TeChargeOperation
{
    ENM_CHARGE_STOP = 0,    //停止充电
    ENM_CHARGE_AUTO,        //自动充电
    ENM_CHARGE_START        //手动开始充电
};

/***** 机器人充电控制 *****/
typedef struct TsRobotChargeCtrl
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    unsigned char        cOperation;                    //充电操作,见TeChargeOperation
} _PACKED_1_ TsRobotChargeCtrl;

/***** 云台控制类型 *****/
enum TePtzCtrlType
{
    ENM_PTZ_CTRL_STOP = 0,    //云台停止
    ENM_PTZ_CTRL_LAMP_ON,        //开灯
    ENM_PTZ_CTRL_LAMP_OFF,        //关灯
    ENM_PTZ_CTRL_ZOOM_IN,        //变倍拉近
    ENM_PTZ_CTRL_ZOOM_OUT,        //变倍拉远
    ENM_PTZ_CTRL_FOUCS_NEAR,    //近焦
    ENM_PTZ_CTRL_FOUCS_FAR,        //远焦
    ENM_PTZ_CTRL_FOUCS_AUTO,    //自动聚焦
    ENM_PTZ_CTRL_WIPER_RUN,        //雨刮
    ENM_PTZ_CTRL_DEMIST_RUN,    //除雾
    ENM_PTZ_CTRL_ROTATE_UP,        //向上
    ENM_PTZ_CTRL_ROTATE_DOWN,    //向下
    ENM_PTZ_CTRL_ROTATE_LEFT,    //向左
    ENM_PTZ_CTRL_ROTATE_RIGHT,    //向右
    ENM_PTZ_CTRL_ROTATE_LEFT_UP,    //左上
    ENM_PTZ_CTRL_ROTATE_LEFT_DOWN,    //左下
    ENM_PTZ_CTRL_ROTATE_RIGHT_UP,    //右上
    ENM_PTZ_CTRL_ROTATE_RIGHT_DOWN,    //右下
    ENM_PTZ_CTRL_RESET,            //复位
    ENM_PTZ_CTRL_SET_CENTER,    //设置云台中心

    ENM_PTZ_PRESET_FRONT,       //前
    ENM_PTZ_PRESET_BACK,        //后
    ENM_PTZ_PRESET_LEFT,        //左
    ENM_PTZ_PRESET_RIGHT,       //右
    ENM_PTZ_PRESET_LEFT_FRONT,  //左前
    ENM_PTZ_PRESET_LEFT_BACK,   //左后
    ENM_PTZ_PRESET_RIGHT_FRONT, //右前
    ENM_PTZ_PRESET_RIGHT_BACK,  //右后
    ENM_PTZ_PRESET_DOWN,        //下

    ENM_LIFT_CTRL_RESET,        //升降架复位
    ENM_LIFT_CTRL_STOP,         //升降架停止
    ENM_LIFT_CTRL_UP,           //升降架上升
    ENM_LIFT_CTRL_DOWN,         //升降架下降

    ENM_PTZ_GOTO_PRESET         //调用预置位
};

/***** 云台控制参数 *****/
typedef struct TsRobotPtzCtrl
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    unsigned short        nPtzID;                        //云台ID
    unsigned short        nCtrlType;                    //控制类型，见TePtzCtrlType
    unsigned int        nCtrlParam;                    //控制参数，由控制类型确定
} _PACKED_1_ TsRobotPtzCtrl;

/***** 路基设备类型 *****/
enum TeRoadbaseType
{
    ENM_ROADBASE_UNKNOWN = 0,       //未定义类型
    ENM_ROADBASE_FIREDOOR,               //防火门 PLC控制
    ENM_ROADBASE_PLATE_TRANSFER,       //老变轨盘
    ENM_ROADBASE_CHARGE_STATION,       //充电桩
    ENM_ROADBASE_FLOOD_VALVE,           //防溢阀
    ENM_ROADBASE_PLATE_TRANSFER_V1,    //新变轨盘
    ENM_ROADBASE_BATTERY,              //北京高碑店485电池
    ENM_ROADBASE_FIREDOOR_V1,          //新防火门 单片机控制
    ENM_ROADBASE_LEVEL_SENSOR          //液位传感器, 型号:ABSD-136-C4
};

/***** 防火门状态 *****/
enum TeFireDoorStatus
{
    ENM_FIRE_DOOR_STATUS_CLOSE = 0,             //0 关闭状态
    ENM_FIRE_DOOR_STATUS_OPEN,               //1 打开状态
    ENM_FIRE_DOOR_STATUS_CLOSE_OPEN,         //2 正在打开防火门
    ENM_FIRE_DOOR_STATUS_OPEN_CLOSE,         //3 正在关闭防火门
    ENM_FIRE_DOOR_STATUS_FAULT,                 //4 故障
    ENM_FIRE_DOOR_STATUS_RUNNING,             //5 位置介于打开与关闭之间（或者正在运行）
    ENM_FIRE_DOOR_STATUS_DISCONNECT             //6 通信失败
};

/***** 变轨盘状态 *****/
enum TePlateTransferStatus
{
    ENM_PLATE_TRANSFER_STATUS_STRAIGHT = 0,               //0 直轨状态
    ENM_PLATE_TRANSFER_STATUS_CURVE,                       //1 弯轨状态
    ENM_PLATE_TRANSFER_STATUS_STRAIGHT_CHANGEING,          //2 变轨盘直轨变弯轨
    ENM_PLATE_TRANSFER_STATUS_CURVE_CHANGEING,             //3 变轨盘弯轨变直轨
    ENM_PLATE_TRANSFER_STATUS_FAULT,                       //4 故障
    ENM_PLATE_TRANSFER_STATUS_RUNNING,                       //5 位置介于打开与关闭之间（或者正在运行）
    ENM_PLATE_TRANSFER_STATUS_DISCONNECT                   //6 通信失败
};

/***** 充电电池状态 *****/
enum TeBatteryStatus
{
    ENM_BATTERY_IDEL = 0,                                      //
    ENM_BATTERY_TRANSFER_STATUS_FAULT,                           //1、功能码不存在
    ENM_BATTERY_TRANSFER_STATUS_ADDRESS,                       //2、通信地址错误（设备不存在）
    ENM_BATTERY_TRANSFER_STATUS_OPERATION,                     //3、不允许此操作
    ENM_BATTERY_TRANSFER_STATUS_DISCONNECT,                       //4、通信失败
    ENM_BATTERY_TRANSFER_STATUS_NORMAL                         //5、通信正常
};

/***** 液位传感器状态 *****/
enum TeLevelSensorStatus
{
    ENM_LEVEL_SENSOR_IDEL = 0,       //
    ENM_LEVEL_SENSOR_FAULT,             //1、功能码不存在
    ENM_LEVEL_SENSOR_ADDRESS,        //2、通信地址错误（设备不存在）
    ENM_LEVEL_SENSOR_OPERATION,      //3、不允许此操作
    ENM_LEVEL_SENSOR_DISCONNECT,     //4、通信失败
    ENM_LEVEL_SENSOR_USABLE          //5、通信正常
};

/**
 * 充电桩状态返回值说明
 * 从机器人端定义拷贝
union ChargeStatus
{
  UINT16 value;
  struct
  {
    UINT16 needle_in : 1;      ///< 充电顶针的状态
    UINT16 needle_out : 1;     ///< 充电顶针的状态
    UINT16 is_car_arrived : 1; ///< 小车是否已到达充电桩
    UINT16 is_relay_on : 1;    ///< 继电器是否打开
    UINT16 run_mode : 1;       ///< 小车当前运行的模式，true - 自动，false 手动
    UINT16 magnet : 1;         ///< 磁吸的状态
    UINT16 resv1 : 2;          ///< 保留字段
    UINT16 state : 3;          ///< 充电桩当前的运行状态
    UINT16 err : 5;
  } bit;
};
*/

/*****  UINT16 state : 3; 充电桩当前的运行状态  *****/
enum TeChargeStationStatus
{
    //ENM_CHARGE_STATION_STATUS_FREE    = 0,        //0 空闲状态
    //ENM_CHARGE_STATION_STATUS_RUNNING,            //1 正在充电状态
    //ENM_CHARGE_STATION_STATUS_TOUCH,            //2 充电顶针收起且磁吸传感器已触发（小车等待待充电）
    //ENM_CHARGE_STATION_STATUS_ARRIVED,            //3 小车抵达充电桩位置（磁吸位置）
    //ENM_CHARGE_STATION_STATUS_FAULT,            //4 充电桩故障
    //ENM_CHARGE_STATION_STATUS_DISCONNECT,        //5 通信失败
    //ENM_CHARGE_STATION_STATUS_NO_TOUCH            //6 充电顶针收起但磁吸传感器没触发（小车在充电桩待充电）

    ENM_CHARGE_STATION_STATUS_FREE = 0,            /**< 空闲状态 */
    ENM_CHARGE_STATION_STATUS_TOUCH,             /**< 充电顶针正在插入 */
    ENM_CHARGE_STATION_STATUS_WAIT_RELAY_ON,     /**< 等待继电器打开, 充电顶针插入后3s再打开继电器 */
    ENM_CHARGE_STATION_STATUS_CHARGING,          /**< 正在充电 */
    ENM_CHARGE_STATION_STATUS_NEEDLE_OUT,        /**< 充电顶针正在拔出 */

    ENM_CHARGE_STATION_STATUS_DISCONNECT = 10        /**< 通信失败 */
};

/***** 防溢阀状态 *****/
enum TeFloodValveStatus
{
    ENM_FLOOD_VALVE_STATUS_CLOSE = 1,        //1 关闭状态
    ENM_FLOOD_VALVE_STATUS_OPEN,            //2 打开状态
    ENM_FLOOD_VALVE_STATUS_FAULT,            //3 故障
    ENM_FLOOD_VALVE_STATUS_RUNNING,            //4 位置介于打开与关闭之间（或者正在运行）
    ENM_FLOOD_VALVE_STATUS_DISCONNECT        //5 通信失败
};

/***** 路基转换器 *****/
typedef struct TsRoadbaseS2E //S2E 是 serial port to ethernet module 的简写
{
    //路基设备按转换器分组
    ushort        nS2EID;                                    //路基转换器ID
    ushort      arrGalleryID[MAX_RELATED_GALLERY_NUM];    //路基组关联管廊ID
    ushort      nNum;                                   //路机组关联管廊个数
    char        sName[MAX_MARK_NAME_LEN];                //路基转换器名称
    char        sIP[MAX_LENGTH_IP];                        //路基转换器IP
    ushort      nPort;                                    //路基转换器端口
    char        nEnable;                                //使能标记
    char        nProxyEnable;                           //是否启用代理
    char        sProxyID[ROBOT_ID_LEN];                 //路基转换器代理ID,跟机器人ID保持一致
} _PACKED_1_ TsRoadbaseS2E;

/***** 路基转换器查询结果 *****/
typedef struct TsRoadbaseS2EQueryResult
{
    ushort                nBeginPos;                //开始位置,仅列表查询时有效
    ushort                nTotalNum;                //总条数
    ushort                nNum;                    //当前结果中的记录数
    TsRoadbaseS2E        arrS2E[MAX_PAGE_NUM];    //转换器信息
} _PACKED_1_ TsRoadbaseS2EQueryResult;

/***** 位置信息 *****/
typedef struct TsGalleryPosition
{
    ushort      galleryID;      //管线ID
    int         location;       //管线位置
} _PACKED_1_ TsGalleryPosition;

/***** 路基设备信息 *****/
typedef struct TsRoadbase
{
    ushort            nID;                                  //路基设备ID
    ushort            nAddr;                                //路基设备通讯地址
    ushort            nS2EID;                               //路基转换器ID
    ushort            nRoadbaseType;                        //路基设备类型，见TeRoadbaseType
    char              sName[MAX_MARK_NAME_LEN];             //路基设备名称
    ushort            nNum;                                 //线管线数量
    TsGalleryPosition arrPosition[MAX_RELATED_GALLERY_NUM]; //关联的管线位置
    ushort            nStatus;                              //路基设备状态
} _PACKED_1_ TsRoadbase;

//充电电池信息
typedef struct TsRoadbaseBattery
{
    TsRoadbase    roadbase;
    float         fVbat;         //充电电池电压
    float         fCurr[2];      //充电电池电流  Curr[0]充电电流，Curr[1]放电电流；
    ushort        nSoc;          //电池电量百分比
    float         fCapNow;       // 电池当前容量  0.1AH
} _PACKED_1_ TsRoadbaseBattery;

/***** 路基设备查询结果 *****/
typedef struct TsRoadbaseQueryResult
{
    ushort            nBeginPos;                    //开始位置,仅列表查询时有效
    ushort            nTotalNum;                    //总条数
    ushort            nNum;                        //当前结果中的记录数
    TsRoadbase        arrRoadbase[MAX_PAGE_NUM];    //路基设备信息
} _PACKED_1_ TsRoadbaseQueryResult;

//液位传感器状态
typedef struct TsLevelSensorStatus
{
    /*
    当测量值 <= 0, 实际液位 <= 零位偏移值
    当测量值 > 0,  实际液位 =  测量值 + 零位偏移值
    */
    TsRoadbase    roadbase;
    int           nDetectinValue;     //测量值,单位：毫米
    int           nZeroOffset;        //零位偏移,单位：毫米
    uint          nDetectSec;         //检测时间,单位：秒
    char          szGalleryName[MAX_MARK_NAME_LEN];   //箱涵名称
} _PACKED_1_ TsLevelSensorStatus;


/***** 路基设备操作类型 *****/
enum TeRoadbaseAction
{
    ENM_ROADBASE_CLOSE = 0,                                  //关闭
    ENM_ROADBASE_OPEN,                                       //打开
    ENM_ROADBASE_CURVE = ENM_ROADBASE_CLOSE,                 //弯轨
    ENM_ROADBASE_STRAIGHT = ENM_ROADBASE_OPEN,               //直轨
    ENM_ROADBASE_STOP_CHARGE = ENM_ROADBASE_CLOSE,           //停止充电
    ENM_ROADBASE_START_CHARGE = ENM_ROADBASE_OPEN,           //充电
    ENM_ROADBASE_PREPARE_CHARGE = 2,                         //准备开始充电
    ENM_ROADBASE_RESET,                                      //复位
    ENM_ROADBASE_READ = 10                                   //读状态
};

/***** 路基控制命令结构（下发到路基节点） *****/
typedef struct TsRoadbaseActionParam
{
    ushort       nRoadbaseType;        //路基设备类型，见TeRoadbaseType
    uchar        nAction;            //操作类型，见TeRoadbaseAction
    uchar        nFunction;            //功能码
    ushort        nAddr;                //地址
    ushort        nParam;                //参数
} _PACKED_1_ TsRoadbaseActionParam;

/***** 路基控制参数 *****/
typedef struct TsRoadbaseCtrl
{
    ushort        nGroupID;            //路基转换器ID
    uchar         nAddr;              //路基设备485地址
    ushort        nRoadbaseType;        //路基设备类型，见TeRoadbaseType
    ushort        nAction;            //路基控制类型，见TeRoadbaseAction
    int            nParam;                //路基控制参数
} _PACKED_1_ TsRoadbaseCtrl;

enum TeIvasStatus
{
    ENM_IVAS_DISCONNECT = 0,    //未连接
    ENM_IVAS_LEARNING,            //学习中
    ENM_IVAS_READY,                //就绪
    ENM_IVAS_ERROR                //异常
};


/***** 最大报警策略项个数 *****/
#define MAX_ALARM_POLICY_ITEM_NUM        9

/***** 报警设备类型 *****/
enum TeAlarmType
{
    ENM_BATTERY_PRIMARY = 1,                //动力电池
    ENM_BATTERY_AUXILIARY,                    //辅助电池（目前用于机械臂供电）
    ENM_O2,                                 //氧气
    ENM_H2S,                                //硫化氢
    ENM_CH4,                                //甲烷
    ENM_NH3,                                //氨气
    ENM_ENVIRONMENT_TEMPERATURE,            //环境温度
    ENM_HUMIDITY,                            //湿度
    ENM_THERMAL_TEMPERATURE,                //热成像最高温
    ENM_FOG,                                //烟感

    ENM_LEVEL_SENSOR = 100                  //液位传感器
};

/***** 报警策略项参数 *****/
typedef struct TsAlarmPolicyItem
{
    unsigned char    bType;                    //报警类型，见TeAlarmType
    unsigned char    bEnable;                //是否启用报警
    short            nEarlyWarning;            //预警阈值
    short            nAlarmThreshold;        //报警阈值
    unsigned short    nInterval;                //报警间隔，单位:秒
} _PACKED_1_ TsAlarmPolicyItem;

/***** 报警策略参数 *****/
typedef struct TsAlarmPolicy
{
    char                    robotID[ROBOT_ID_LEN];                //机器人ID,注：机器人ID为空时，配置系统通用报警策略
    unsigned char            applyToAll;                            //是否应用到所有机器人
    unsigned short            nItemNum;                            //配置项个数
    TsAlarmPolicyItem        arrItem[MAX_ALARM_POLICY_ITEM_NUM];    //配置项
} _PACKED_1_ TsAlarmPolicy;

/***** 报警级别 *****/
enum TeAlarmLevel
{
    ENM_EARLY_WARNING = 1,        //预警
    ENM_ALARM                    //报警
};

/***** 报警信息 *****/
typedef struct TsAlarmInfo
{
    char                    szAlarmID[ROBOT_ID_LEN];                //报警源ID {机器人ID 或者 （转换器ID*1000 + 路基ID）}
    unsigned char            cType;                                    //报警类型，见TeAlarmType
    unsigned char            cAlarmLevel;                            //报警级别，见TeAlarmLevel
    float                    nAlarmValue;                            //报警值
    INT64                    nAlarmTime;                                //报警时间
    int                     nLocation;                                //机器人位置
    char                    sPipeGalleryName[MAX_MARK_NAME_LEN];    //管廊名称
    char                    szAlarmSource[MAX_MARK_NAME_LEN];       //报警源名称
} _PACKED_1_ TsAlarmInfo;

/***** 报警日志查询条件 *****/
typedef struct TsAlarmLogQueryCondition
{
    char            robotID[ROBOT_ID_LEN];    //机器人ID，为空时，查所有机器人
    uchar            cType;                    //报警类型，见TeAlarmType
    uchar            cAlarmLevel;            //报警级别，见TeAlarmLevel
    INT64            nBeginTime;                //单位：毫秒
    INT64            nEndTime;                //单位：毫秒
    int             nBeginLocation;            //开始位置
    int             nEndLocation;            //结束位置
    uint            nBeginPos;                //开始位置，分页查询从第几条开始返回
} _PACKED_1_ TsAlarmLogQueryCondition;

/***** 报警日志查询结果 *****/
typedef struct TsAlarmLogQueryResult
{
    unsigned int        nBeginPos;            //开始位置
    unsigned int        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsAlarmInfo            arrAlarmInfo[MAX_ALARM_LOG_NUM];
} _PACKED_1_ TsAlarmLogQueryResult;

/***** 报警摘要 *****/
typedef struct TsAlarmSummary
{
    char            robotID[ROBOT_ID_LEN];    //机器人ID
    uint            nEarlyWarningCnt;       //预警数量
    uint            nAlarmCnt;              //报警数量
} _PACKED_1_ TsAlarmSummary;

/***** 报警摘要查询结果 *****/
typedef struct TsAlarmSummaryQueryResult
{
    unsigned short        nNum;                //当前结果中的记录数
    TsAlarmSummary      arrAlarmSummary[MAX_ROBOT_NUM];
} _PACKED_1_ TsAlarmSummaryQueryResult;

/****无线模块在线状态****/
enum TsWirelessStatus
{
    ENM_WIRELESS_STATUS_IDLE = 0,       //空闲
    ENM_WIRELESS_STATUS_ONLINE,         //在线
    ENM_WIRELESS_STATUS_OFFLINE         //离线
};

/********************************************** 以下是通知消息体 *********************************************************************/

/***** 机器人在线状态 *****/
enum TeRobotStatus
{
    ENM_ROBOT_STATUS_IDLE = 0,       //空闲
    ENM_ROBOT_STATUS_ONLINE,        //在线
    ENM_ROBOT_STATUS_READY,         //就绪
    ENM_ROBOT_STATUS_USING,         //占用
    ENM_ROBOT_STATUS_OFFLINE       //离线
};

/***** 机器人在线状态 *****/
typedef struct TsRobotStatus
{
    char            robotID[ROBOT_ID_LEN];    //机器人ID
    short            nStatus;                //机器人状态,参见 TeRobotStatus
} _PACKED_1_ TsRobotStatus;

/***** 报警日志查询结果 *****/
typedef struct TsRobotStatusQueryResult
{
    unsigned int        nBeginPos;            //开始位置
    unsigned int        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsRobotStatus        arrRobotStatus[MAX_PAGE_NUM];
} _PACKED_1_ TsRobotStatusQueryResult;

/***** 机器人运行状态 *****/
typedef struct TsRobotRunningLog
{
    char            robotID[ROBOT_ID_LEN];    //机器人ID
    char            sStatus[MAX_LOG_LEN + 1];
} _PACKED_1_ TsRobotRunningLog;


/***** 机器人上下线记录 *****/
typedef struct TsRobotOnlineCount
{
    char            sRobotID[ROBOT_ID_LEN];     //机器人ID
    char            sName[DEV_NAME_LEN];        //机器人名称
    int             onlineTime;                 //机器人上线时间
    int             offlineTime;                //机器人下线时间
} _PACKED_1_ TsRobotOnlineCount;

/*****  机器人上下线查询条件 *****/
typedef struct TsRobotOnlineQueryCondition
{
    char                sRobotID[ROBOT_ID_LEN];    // 机器人ID
    unsigned int        nBeginTime;                //开始时间
    unsigned int        nEndTime;                //结束时间
    unsigned short        nQueryPos;                //查询下标
} _PACKED_1_ TsRobotOnlineQueryCondition;


/***** 机器人上下线记录查询结果 *****/
typedef struct TsRobotOnlineCountQueryResult
{
    unsigned int        nBeginPos;            //开始位置
    unsigned int        nTotalNum;            //总条数
    unsigned short        nNum;                //当前结果中的记录数
    TsRobotOnlineCount        arrRobotOnlineCount[MAX_PAGE_NUM];
} _PACKED_1_ TsRobotOnlineCountQueryResult;

/***** 机器人传感器项 *****/
typedef struct TsSensorItem
{
    uchar    enable;                //是否支持
    float    value;                //采样值
    short    analysis;            //分析结果,取值见TeSensorStatus
} _PACKED_1_ TsSensorItem;


/***** 机器人传感器状态 *****/
typedef struct TsSensorInfo
{
    TsSensorItem    O2;                        //氧气浓度，取值[0.0, 100.0]
    TsSensorItem    CH4;                    //甲烷浓度，取值[0.0, 100.0]
    TsSensorItem    H2S;                    //硫化氢浓度，取值[0.0, 100.0]
    TsSensorItem    NH3;                    //氨气浓度，取值[0.0, 100.0]
    TsSensorItem    temperature;            //环境温度，单位：摄氏度，取值[0.0, 100.0]
    TsSensorItem    humidity;                //湿度，取值[0.0, 100.0]
} _PACKED_1_ TsSensorInfo;


/***** 机器人车体状态 *****/
typedef struct TsCarStatus
{
    char            robotID[ROBOT_ID_LEN];      // 机器人ID
    unsigned short    nGalleryID;                  //管廊ID
    int                location;                  // 计米位置，单位：毫米
    short            runSpeed;                  // 运行速度，单位：毫米每秒
    char            state[100];                  // 小车当前的状态
    INT64           nTimeSec;                 //  秒
    uchar            bIsSensor;                // 0:location 传感器数据为0     1:有传感器数据       2:机器人错误状态
    TsSensorInfo    sensorInfo;               //传感器信息
} _PACKED_1_ TsCarStatus;

enum TeSensorStatus
{
    SENSOR_LOW_ALARM = 1,        //低值报警
    SENSOR_LOW_WARNING,            //低值警告
    SENSOR_NORMAL,                //正常
    SENSOR_HIGH_WARNING,        //高值警告
    SENSOR_HIGH_ALARM,            //高值报警
};

//路基设备传感器类型
enum TeMonitoredDvsType
{
    MONITORED_DVS_LEVEL = 0           //液位传感器
};

/***** 设备传感器状态 *****/
typedef struct TsMonitoredDvsInfo
{
    char            sourceID[ROBOT_ID_LEN];    //机器人ID
    int             nDvsType;               //设备传感器类型
    TsSensorItem    levelSensor;            //液体传感器，取值[0.0, 100.0]
    INT64           nTimeSeconds;           //单位秒
} _PACKED_1_ TsMonitoredDvsInfo;


/***** 机器人电池单元状态 *****/
typedef struct TsBatteryCell
{
    unsigned char    batteryID;        //电池编号
    float            voltage;        //电压，单位：mV
    float            electricity;    //电流，单位：mA
    float            totalEnergy;    //总电量，单位：mAH
    float            remainEnergy;    //剩余电量，单位：mAH
    float            temperature;    //电池温度，单位：摄氏度
} _PACKED_1_ TsBatteryCell;

#define MAX_BATTERY_CELL    2        //目前USR最多两个电池单元
/***** 机器人电池参数 *****/
typedef struct TsBatteryInfo
{
    char            robotID[ROBOT_ID_LEN];                //机器人ID
    unsigned char    batteryNum;                            //电池个数，取值[0, 2]
    TsBatteryCell    arrBatteryCell[MAX_BATTERY_CELL];    //电池单元信息
} _PACKED_1_ TsBatteryInfo;

/***** 热成像仪最高温点参数 *****/
typedef struct TsRobotThermal
{
    char                sRobotID[ROBOT_ID_LEN];    //机器人ID
    unsigned short        uChannelID;                //通道ID
    unsigned int        nX;                        //最高温点 X 坐标
    unsigned int        nY;                        //最高温点 Y 坐标
    TsSensorItem        tsThermal;                //热成像采样
} _PACKED_1_ TsRobotThermal;

/***** 采样数据 *****/
typedef struct TsSnapshotSample
{
    char                sImage[MAX_FILE_NAME_LEN];          //采样图片名称
    char                sAnalysis[MAX_SAMPLE_INFO_LEN];     //图片分析结果
    TsSensorItem        tsThermal;                            //热成像采样
    uint                nSeconds;                           //抓拍的时间
} _PACKED_1_ TsSnapshotSample;

/***** 机械臂状态 *****/
typedef struct TsRobotArmStatus
{
    char                sRobotID[ROBOT_ID_LEN];    //机器人ID
    unsigned char        isConnected;            //是否连接
    unsigned char        isMoving;                //是否移动
    unsigned char        isPowerOn;                //是否上电
    unsigned char        isError;                //是否出错
    unsigned char        isBrake;                //抱闸
    short                errCode;                //错误码
    short                errAxis;                //出错的轴
    TsRobotArmAngle        armAngle;                //机械臂角度
} _PACKED_1_ TsRobotArmStatus;

typedef struct TsPtzStatus
{
    float   fHorizontalAngle;   //水平角度
    float   fVerticalAngle;     //垂直角度
    float   fLiftHeight;        //升降高度
    ushort  nZoom;              //镜头变倍，0 无意义，大于0 表示镜头倍数
} _PACKED_1_ TsPtzStatus;

typedef struct TsRobotPtzStatus
{
    char                sRobotID[ROBOT_ID_LEN];                //机器人ID
    uchar                cType;                                //设备类型，见TeMountDvsType
    TsPtzStatus         arrPtzStatus[ENM_MAX_MOUNT_DVS];    //云台状态
} _PACKED_1_ TsRobotPtzStatus;

/***** 巡检状态 *****/
enum TeTourStatus
{
    ENM_TOUR_STOP = 0,                    //等待巡检
    ENM_TOUR_DISPATCH,                    //等待调度
    ENM_TOUR_READY,                        //准备执行
    ENM_TOUR_RUNNING_MOVE,                //正在执行，移动到下一点
    ENM_TOUR_RUNNING_DETECTON,            //正在执行，站点检测
    ENM_TOUR_UPLOAD_REPORT,             //上传报告
    ENM_TOUR_INTELLIGENT_ANALYSIS,      //智能分析
    ENM_TOUR_FINISH,                    //任务结束
    ENM_ROBOT_STATUS_PAUSE              //巡检暂停
};
/***** 巡检报告状态 *****/
enum TeTourReportStatus
{
    ENM_TOUR_REPORT_ALL = 0,              //所有状态
    ENM_TOUR_REPOTR_SUCESS,               //巡检完成
    ENM_TOUR_COUNTTING,                   //正在巡查
    ENM_TOUR_REPOTR_FAILED                //巡查异常
};

///***** 巡检状态 *****/
//typedef struct TsTourStatus
//{
//    unsigned short        nTaskID;                    //任务ID
//    char                sName[MAX_MARK_NAME_LEN];    //任务名称
//    unsigned char        nPerformType;                //执行类型，见TePerformType
//    unsigned int        nScheduleTime;                //计划执行时间
//    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
//    unsigned int        nBeginTime;                    //开始时间，单位秒
//    unsigned int        nEndTime;                    //最后一次更新状态的时间，任务结束后为结束时间，单位秒
//    unsigned short        nStatus;                    //巡检状态，见TeTourStatus
//    short                nParam;                        //状态参数，Status为 RUNNING 的两种状态时，为StationID，其他情况未错误码
//}_PACKED_1_ TsTourStatus;

/***** 回放状态 *****/
typedef struct TsRetrievalStatus
{
    char                sRobotID[ROBOT_ID_LEN];        //机器人ID
    ushort              nChannelID;
    short               nStatus;
    INT64               nNextFrameTimestamp;
} _PACKED_1_ TsRetrievalStatus;

typedef struct TsChannelMediaStatus
{
    ushort    nChannelID;
    short   nMediaStatus;       //0 表示录像正常，负值 表示录像错误码
} _PACKED_1_ TsChannelMediaStatus;

typedef struct TsRobotMediaStatus
{
    char                    szRobotID[ROBOT_ID_LEN];
    ushort                  nCameraNum;
    TsChannelMediaStatus    arrStatus[MAX_IPC_NUM];
} _PACKED_1_ TsRobotMediaStatus;

enum TeLanguegeType
{
    ENM_LANGUEGE_CHINESE = 0,              //中文
    ENM_LANGUEGE_ENGLISH                   //英文
};

/***** 操作记录 *****/
typedef struct TsOperationRecord
{
    unsigned int          nTime;                                       //操作时间
    char                 sIP[IPV4_LEN];                               //操作机器IP
    char                 sName[MAX_USER_NAME_LEN];                    //操作用户
    int                  nCmdID;                                      //操作命令
    char                 sCmdIDExplain[MAX_OPERATION_EXPLAIN];        //操作命令说明
    int                  nOperationResult;                            //操作结果
    char                 sOperationExplain[MAX_OPERATION_EXPLAIN];    //操作重要参数
} _PACKED_1_ TsOperationRecord;

/*****  操作记录查询条件 *****/
typedef struct TsOperationRecordQueryCondition
{
    char                sIP[IPV4_LEN];             // IP
    unsigned int        nBeginTime;                 //开始时间
    unsigned int        nEndTime;                 //结束时间
    unsigned short        nQueryPos;                 //查询下标
} _PACKED_1_ TsOperationRecordQueryCondition;

/***** 操作记录查询结果 *****/
typedef struct TsOperationRecordQueryResult
{
    unsigned int           nBeginPos;            //开始位置
    unsigned int           nTotalNum;            //总条数
    unsigned short           nNum;                //当前结果中的记录数
    TsOperationRecord       arrOperationRecord[MAX_PAGE_NUM];
} _PACKED_1_ TsOperationRecordQueryResult;

/***** 液位传感器数据记录 *****/
typedef struct TsMonitoredDvsRecord
{
    char                 sSourceID[ROBOT_ID_LEN];         //传感器数的源ID
    int                  nDvsType;                        //
    int                  nValue;                          //单位： mm
    INT64                  nTimeSenconds;                           //操作时间 秒
} _PACKED_1_ TsMonitoredDvsRecord;

/*****  小车状态及传感器记录查询条件 *****/
typedef struct TsCarStatusQueryCondition
{
    char                  sSourceID[ROBOT_ID_LEN];     //传感器数的源ID
    int                   nLocationBeg;                //起始位置
    int                   nLocationEnd;                //结束位置
    INT64                 nBeginTime;                     //开始时间
    INT64                 nEndTime;                     //结束时间
    uchar                  cType;                       //查询数据类型 0：查询小车位置 1：传感器数据  2:机器人错误状态
    unsigned short        nQueryPos;                     //查询下标
} _PACKED_1_ TsCarStatusQueryCondition;

/***** 小车状态及传感器记录查询结果 *****/
typedef struct TsCarStatusRecordQueryResult
{
    unsigned int           nBeginPos;            //开始位置
    unsigned int           nTotalNum;            //总条数
    unsigned short           nNum;                //当前结果中的记录数
    TsCarStatus               arrRecord[MAX_PAGE_NUM];
} _PACKED_1_ TsCarStatusRecordQueryResult;

/*****  路基设备数据记录查询条件 *****/
typedef struct TsMonitoredDvsRecrdQueryCondition
{
    char                sSourceID[ROBOT_ID_LEN];     //传感器数的源ID
    int                 nDvsType;                    //路基设备类型
    INT64                nBeginTime;                     //开始时间
    INT64                nEndTime;                     //结束时间
    unsigned short        nQueryPos;                     //查询下标
} _PACKED_1_ TsMonitoredDvsRecrdQueryCondition;

/*****路基设备数据记录查询结果 *****/
typedef struct TsMonitoredDvsRecordQueryResult
{
    unsigned int           nBeginPos;            //开始位置
    unsigned int           nTotalNum;            //总条数
    unsigned short           nNum;                //当前结果中的记录数
    TsMonitoredDvsRecord       arrRecord[MAX_PAGE_NUM];
} _PACKED_1_ TsMonitoredDvsRecordQueryResult;

///***** 机器人位置记录 *****/
//typedef struct TsLocationRecord
//{
//    char                 sRobotID[ROBOT_ID_LEN];          //传感器数的源ID
//    unsigned short         nGalleryID;                      //管廊ID
//    int                  nLocation;                       //管廊位置 mm
//    INT64                  nTime;                           //操作时间 毫秒
//} _PACKED_1_ TsLocationRecord;


///*****  机器人位置记录查询条件 *****/
//typedef struct TsLocationRecordQueryCondition
//{
//    char                sRobotID[ROBOT_ID_LEN];     //传感器数的源ID
//    INT64                nBeginTime;                     //开始时间
//    INT64                nEndTime;                     //结束时间
//    unsigned short        nQueryPos;                     //查询下标
//} _PACKED_1_ TsLocationRecordQueryCondition;
//
///***** 机器人位置记录查询结果 *****/
//typedef struct TsLocationRecordQueryResult
//{
//    unsigned int           nBeginPos;            //开始位置
//    unsigned int           nTotalNum;            //总条数
//    unsigned short           nNum;                //当前结果中的记录数
//    TsCarStatus               arrLocationRecord[MAX_PAGE_NUM];
//} _PACKED_1_ TsLocationRecordQueryResult;


/***** 爬行器叠加字符类型 *****/
enum SrodFilterType
{
    Srod_Filter_UNKNOWN = 0,    //未定义
    Srod_Filter_HEADER,         //片头
    Srod_Filter_BODY,           //正文
    Srod_Filter_TAIL,           //片尾
};

/***** 爬行器叠加字体 *****/
typedef struct SrodFilterFont
{
    char    szFontFile[MAX_MARK_NAME_LEN];
    char    szFontColor[MAX_MARK_NAME_LEN];
    int     nFontSize;
} _PACKED_1_ SrodFilterFont;

#define SROD_MAX_FILTER_TEXT_LEN 300
/***** 爬行器叠加文本 *****/
typedef struct SrodFilterText
{
    int     nType;//0 time 1 text 2 image
    int     nX;
    int     nY;
    char    szText[SROD_MAX_FILTER_TEXT_LEN];
} _PACKED_1_ SrodFilterText;

//云台区域选择放大缩小(私有 快球专用)
typedef struct Ptz3DRect
{
    int xTop;     //方框起始点的x坐标
    int yTop;     //方框起始点的y坐标
    int xBottom;  //方框结束点的x坐标
    int yBottom;  //方框结束点的y坐标
    int bCounter; //保留
} _PACKED_1_ Ptz3DRect;

typedef struct Ptz3DPoint
{
    int x; //中心点坐标
    int y; //中心点坐标
    int zoom; //变倍
} _PACKED_1_ Ptz3DPoint;

typedef struct TsPtz3DParam
{
    char sRobotID[ROBOT_ID_LEN];
    Ptz3DPoint point;
    Ptz3DRect  rect;
} _PACKED_1_ TsPtz3DParam;


typedef struct
{
    char sRobotID[ROBOT_ID_LEN];  //机器人ID
    char sIP[IPV4_LEN];           //无线模块IP
    int  frequency;               //射频频率
    char  enable;                 //使能
    int  port;                    //无线模块端口号
    char  addr;                   //机器人无线模块通信地址
    char  status;                 //机器人状态 00前进 01停止 02后退
} _PACKED_1_  TsWirelessInfo;

/**********************************************************************/
//恢复默认对齐状态
#ifdef WIN32
    #pragma pack(pop)
#endif
/**********************************************************************/

#endif //_USR_DOMAIN_H_