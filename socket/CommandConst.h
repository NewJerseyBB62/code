#ifndef _COMMAND_CONST_H_
#define _COMMAND_CONST_H_

/************************************************************************
消息头的魔法码
************************************************************************/
const unsigned short CST_MAGIC_CODE = 0xAA55;

/************************************************************************
命令号：
预留			0x00 ~ 0xFF
USR系统命令		0x0100 ~ 0x0FFF
机器人控制命令	0x1000 ~ 0x11FF
机器人配置命令	0x1200 ~ 0x12FF
通知消息		0x8000

应答命令ID = 请求命令ID + 1
************************************************************************/
const unsigned int CST_CMD_LOGIN					        = 0x0100; //登录,TsLoginInfo
const unsigned int CST_CMD_LOGOUT					        = 0x0102; //登出
const unsigned int CST_CMD_GET_ROBOT_INFO			        = 0x0104; //获取机器人信息,TsRobotInfo
const unsigned int CST_CMD_GET_RECORD_POLICY		        = 0x0106; //查询录像策略,TsRecordPolicy
const unsigned int CST_CMD_SET_RECORD_POLICY		        = 0x0108; //设置录像策略,TsRecordPolicy
const unsigned int CST_CMD_GET_RECORD_EXPIRE_TIME	        = 0x010A; //查询录像保留期限
const unsigned int CST_CMD_SET_RECORD_EXPIRE_TIME	        = 0x010C; //设置录像保留期限
const unsigned int CST_CMD_RECORD_QUERY				        = 0x010E; //录像查询,TeStorageType、TsStorageQueryCondition、TsStorageQueryResult
const unsigned int CST_CMD_SNAPSHOT_QUERY			        = 0x0110; //抓拍查询,TeStorageType、TsStorageQueryCondition、TsStorageQueryResult
const unsigned int CST_CMD_HEARTBEAT				        = 0x0112; //心跳命令
const unsigned int CST_CMD_GET_ROBOT_STATUS			        = 0x0114; //获取机器人状态，TsRobotStatus
const unsigned int CST_CMD_GET_MEDIA_SUMMARY_INFO	        = 0x0116; //获取机器人媒体摘要信息
const unsigned int CST_CMD_SET_ROBOT_NAME       	        = 0x0118; //设置机器人名称
const unsigned int CST_CMD_DEL_ROBOT               	        = 0x011A; //删除机器人
const unsigned int CST_CMD_GET_UNS_DATE_TIME       	        = 0x011C; //查询服务器时间
const unsigned int CST_CMD_GET_VERSION             	        = 0x011E; //查询版本号
const unsigned int CST_CMD_GET_RECORD_ROBOT_INFO			= 0x0120; //获取录像机器人信息,TsRobotInfo
const unsigned int CST_CMD_GET_RECORD_MEDIA_SUMMARY_INFO	= 0x0122; //获取录像机器人媒体摘要信息
const unsigned int CST_CMD_GET_RECORD_CALENDAR         	    = 0x0124; //获取录像日历
const unsigned int CST_CMD_GET_LIVE_MEDIA_STATUS       	    = 0x0126; //获取实时媒体状态
const unsigned int CST_CMD_GET_RECORD_STATUS         	    = 0x0128; //获取录像状态
const unsigned int CST_CMD_GET_ROBOT_NAME       	        = 0x012A; //获取机器人名称
const unsigned int CST_CMD_GET_ROBOT_ONLINE_COUNT           = 0x012C; //机器人上下线统计
const unsigned int CST_CMD_GET_ROBOT_LOCATION               = 0x012E; //机器人位置记录

const unsigned int CST_CMD_ADD_ROLE_INFO                    = 0x0130; //新增角色
const unsigned int CST_CMD_GET_ROLE_INFO                    = 0x0132; //获取角色信息
const unsigned int CST_CMD_SET_ROLE_INFO                    = 0x0134; //设置角色信息
const unsigned int CST_CMD_DELETE_ROLE_INFO                 = 0x0136; //删除角色
const unsigned int CST_CMD_SET_ROLE_PRIVILEGE               = 0x0138; //设置角色权限
const unsigned int CST_CMD_GET_ROLE_PRIVILEGE               = 0x013A; //获取角色权限
const unsigned int CST_CMD_CHECK_USER_EXISTED               = 0x013C; //检测用户是否存在
const unsigned int CST_CMD_ADD_USER_INFO                    = 0x013E; //新增用户信息
const unsigned int CST_CMD_GET_USER_INFO                    = 0x0140; //获取用户信息
const unsigned int CST_CMD_SET_USER_INFO                    = 0x0142; //设置用户信息
const unsigned int CST_CMD_DELETE_USER_INFO                 = 0x0144; //删除用户

const unsigned int CST_CMD_CREATE_DATA_CHANNEL		= 0x0200; //创建数据通道
const unsigned int CST_CMD_START_LIVE_PREVIEW		= 0x0202; //请求视频
const unsigned int CST_CMD_STOP_LIVE_PREVIEW		= 0x0204; //停止视频
const unsigned int CST_CMD_START_RETRIEVAL			= 0x0206; //录像数据取回,TsRetrievalInfo
const unsigned int CST_CMD_STOP_RETRIEVAL			= 0x0208; //停止录像取回
const unsigned int CST_CMD_RETRIEVAL_CTRL			= 0x020A; //录像取回控制
const unsigned int CST_CMD_START_MSG_TRANSMIT		= 0x020C; //开始消息传输
const unsigned int CST_CMD_STOP_MSG_TRANSMIT		= 0x020E; //取消消息传输
const unsigned int CST_CMD_START_RETRIEVAL_V2       = 0x0210; //开始回放
const unsigned int CST_CMD_STOP_RETRIEVAL_V2        = 0x0212; //停止回放
const unsigned int CST_CMD_SET_RETRIEVAL_TIME       = 0x0214; //设置回放区间
const unsigned int CST_CMD_SET_SKIP_BLAND_SPACE     = 0x0216; //设置跳过空白标记
const unsigned int CST_CMD_SET_RETRIEVAL_RATE       = 0x0218; //设置速率
const unsigned int CST_CMD_START_CHANNEL_MEDIA      = 0x021A; //请求通道视频
const unsigned int CST_CMD_STOP_CHANNEL_MEDIA       = 0x021C; //停止通道视频
const unsigned int CST_CMD_RETRIEVAL_LOCATE_TIME    = 0x021E; //时间定位
const unsigned int CST_CMD_PAUSE                    = 0x0220; //暂停
const unsigned int CST_CMD_PLAY_NEXT_FRAME          = 0x0222; //播放下一帧
const unsigned int CST_CMD_BEGIN_BROWSE             = 0x0224; //开始拖动
const unsigned int CST_CMD_BROWSE                   = 0x0226; //拖动
const unsigned int CST_CMD_END_BROWSE               = 0x0228; //停止拖动
const unsigned int CST_CMD_START_MEDIE_PROXY		= 0x022A; //启动代理视频
const unsigned int CST_CMD_STOP_MEDIE_PROXY 		= 0x022C; //停止代理视频

const unsigned int CST_CMD_QUERY_ALARM_LOG			= 0x0230; //查询报警日志
const unsigned int CST_CMD_QUERY_ALARM_SUMMARY		= 0x0232; //查询报警日志统计信息
const unsigned int CST_CMD_START_TALKBACK		    = 0x0234; //开始对讲
const unsigned int CST_CMD_STOP_TALKBACK 		    = 0x0236; //停止对讲

const unsigned int CST_CMD_SNAPSHOT_CTRL			= 0x0240; //抓拍控制,TsSnapshotTask

const unsigned int CST_CMD_DVS_UPGRADE				= 0x0300; //设备升级
const unsigned int CST_CMD_STOP_UPGRADE				= 0x0302; //终止升级
const unsigned int CST_CMD_UPGRADE_STATUS			= 0x0304; //升级状态,TsDvsUpgradeStatus

const unsigned int CST_CMD_IVAS_GET_STATUS       = 0x0400; //获取分析软件状态
const unsigned int CST_CMD_IVAS_ADD_SAMPLE       = 0x0402; //添加分析样本
const unsigned int CST_CMD_IVAS_CLEAR_SAMPLE     = 0x0404; //清空分析样本
const unsigned int CST_CMD_IVAS_RELEARN          = 0x0406; //重新学习
const unsigned int CST_CMD_IVAS_IMAGE_ANALYZING  = 0x0408; //图片分析
const unsigned int CST_CMD_IVAS_UPLOAD_SAMPLE    = 0x040A; //上传样本


const unsigned int CST_CMD_GET_OPERATOR_RIGHTS		      = 0x1000; //获取操作权
const unsigned int CST_CMD_CTRL_ROBOT_MOTION		      = 0x1002; //控制机器人运动,TsRobotMotion
const unsigned int CST_CMD_SET_ROBOT_PRESSURE		      = 0x1004; //控制压紧轮,TsRobotPressure
const unsigned int CST_CMD_SET_ROBOT_LAMP			      = 0x1006; //灯光控制,TsRobotLamp
const unsigned int CST_CMD_ROBOT_PARKING			      = 0x1008; //驻车,TsRobotParking
const unsigned int CST_CMD_ROBOT_SCRAM				      = 0x100A; //急停
const unsigned int CST_CMD_ROBOT_CLEAR				      = 0x100C; //清错
const unsigned int CST_CMD_ROBOT_CHARGE				      = 0x100E; //充电控制,TsRobotChargeCtrl
const unsigned int CST_CMD_ROBOT_REVISE_LOCATION	      = 0x1010; //位置校正,TsRobotLocation
const unsigned int CST_CMD_SET_ROBOT_TOUR			      = 0x1012; //巡检策略配置,TsRobotTour
const unsigned int CST_CMD_GET_ROBOT_TOUR			      = 0x1014; //巡检策略查询,TsRobotTour
const unsigned int CST_CMD_ROBOT_AUTO_TOUR			      = 0x1016; //自动巡检,TsRobotAutoTour
const unsigned int CST_CMD_ROBOT_PTZ_CTRL			      = 0x1018; //机器人云台控制,TsRobotPtzCtrl
const unsigned int CST_CMD_ROBOT_SHUTDOWN			      = 0x101A; //机器人关机
const unsigned int CST_CMD_ROBOT_RESTART			      = 0x101C; //机器人重启
const unsigned int CST_CMD_ROBOT_ARM_CTRL			      = 0x101E; //机械臂控制
const unsigned int CST_CMD_ROBOT_BACK_HOME			      = 0x1020; //机器人返航
const unsigned int CST_CMD_GET_ALARM_POLICY			      = 0x1022; //获取报警参数,TsAlarmPolicy
const unsigned int CST_CMD_SET_ALARM_POLICY			      = 0x1024; //设置报警参数,TsAlarmPolicy
const unsigned int CST_CMD_GET_ROBOT_LAMP			      = 0x1026; //获取灯光状态,TsRobotLampStatus
const unsigned int CST_CMD_GET_AVOID_OBSTACLE		      = 0x1028; //获取避障状态,TsRobotAvoidObstacle
const unsigned int CST_CMD_SET_AVOID_OBSTACLE		      = 0x102A; //设置避障参数,TsRobotAvoidObstacle
const unsigned int CST_CMD_ROBOT_GOTO_LOCATION	          = 0x102C; //一键定位,TsRobotLocation
const unsigned int CST_CMD_ROBOT_MANUAL_TOUR	          = 0x102E; //手动巡检,TsManualTourParam
const unsigned int CST_CMD_ROBOT_TOUR_CTRL                = 0x1030; //暂停巡检驻车,TsRobotTourCtrl
const unsigned int CST_CMD_GET_MONITORED_DVS_ALARM_POLICY = 0x1032; //获取被监控设备报警参数,TsAlarmPolicy
const unsigned int CST_CMD_SET_MONITORED_DVS_ALARM_POLICY = 0x1034; //设置被监控报警参数,TsAlarmPolicy
const unsigned int CST_CMD_ROBOT_PTZ_3DPOSITION           = 0x1036; //机器人云台3D位置,tsPtz3DParam
const unsigned int CST_CMD_ROBOT_WIRELESS_ADDR            = 0x1038; //机器人无线模块通信频率及地址
const unsigned int CST_CMD_ROBOT_RTSP_MEDIA_ADDR          = 0x103A; //机器人摄像机信息

const unsigned int CST_CMD_ROADBASE_CTRL			= 0x2000; //路基控制,TsRoadbaseCtrl
const unsigned int CST_CMD_ADD_ROADBASE_S2E		    = 0x2002; //新增路基转换器,TsRoadbaseS2E
const unsigned int CST_CMD_GET_ROADBASE_S2E         = 0x2004; //查询路基组信息
const unsigned int CST_CMD_SET_ROADBASE_S2E         = 0x2006; //设置路基组信息,TsRoadbaseS2E
const unsigned int CST_CMD_DEL_ROADBASE_S2E         = 0x2008; //删除路基组信息
const unsigned int CST_CMD_GET_ROADBASE				= 0x200A; //查询路基设备,TsRoadbase
const unsigned int CST_CMD_SET_ROADBASE				= 0x200C; //设置路基设备,TsRoadbase
const unsigned int CST_CMD_DEL_ROADBASE				= 0x200E; //删除路基设备,TsRoadbase
const unsigned int CST_CMD_ACTIVATE_S2E             = 0x2010; //激活路基代理
const unsigned int CST_CMD_ADD_ROADBASE             = 0x2012; //新增路基设备,TsRoadbase

const unsigned int CST_CMD_ADD_PIPE_GALLERY			= 0x2100; //新增管廊,TsPipeGallery
const unsigned int CST_CMD_GET_PIPE_GALLERY			= 0x2102; //查询管廊,TsPipeGallery/TsPipeGalleryQueryResult
const unsigned int CST_CMD_SET_PIPE_GALLERY			= 0x2104; //设置管廊,TsPipeGallery
const unsigned int CST_CMD_DEL_PIPE_GALLERY			= 0x2106; //删除管廊

const unsigned int CST_CMD_ADD_TOUR_STATION			= 0x2108; //新增站点,TsTourStation
const unsigned int CST_CMD_GET_TOUR_STATION			= 0x210A; //查询站点,TsTourStation/TsTourStationQueryResult
const unsigned int CST_CMD_SET_TOUR_STATION			= 0x210C; //设置站点,TsTourStation
const unsigned int CST_CMD_DEL_TOUR_STATION			= 0x210E; //删除站点

const unsigned int CST_CMD_ADD_TOUR_LINE			= 0x2110; //新增线路,TsTourLine
const unsigned int CST_CMD_GET_TOUR_LINE			= 0x2112; //查询线路,TsTourLine/TsPipeGalleryQueryResult
const unsigned int CST_CMD_SET_TOUR_LINE			= 0x2114; //设置线路,TsTourLine
const unsigned int CST_CMD_DEL_TOUR_LINE			= 0x2116; //删除线路

const unsigned int CST_CMD_ADD_TOUR_TASK			       = 0x2118; //新增任务,TsTourTask
const unsigned int CST_CMD_GET_TOUR_TASK			       = 0x211A; //查询任务,TsTourTask/TsTourTaskQueryResult
const unsigned int CST_CMD_SET_TOUR_TASK			       = 0x211C; //设置任务,TsTourTask
const unsigned int CST_CMD_DEL_TOUR_TASK			       = 0x211E; //删除任务
const unsigned int CST_CMD_UPLOAD_DOWNLOAD_REPORT	       = 0x2120; //上传、下载巡检报告，TsUploadDownloadTourReport
const unsigned int CST_CMD_QUERY_TOUR_REPORT		       = 0x2122; //查询巡检报告，TsTourReportQueryCondition
const unsigned int CST_CMD_QUERY_TOUR_STATUS		       = 0x2124; //查询巡检历史状态，TsTourStatusQueryCondition
const unsigned int CST_CMD_SUMMARY_QUERY_TOUR_REPORT	   = 0x2126; //查询巡检报告摘要，TsTourReportQueryCondition
const unsigned int CST_CMD_SUBSCRIBE_RT_TOUR_STATION       = 0x2128; //订阅站点巡检结果实时上传
const unsigned int CST_CMD_UNSUBSCRIBE_RT_TOUR_STATION     = 0x212A; //取消订阅站点巡检结果实时上传
const unsigned int CST_CMD_GET_OPERATION_RECOTD            = 0x212c; //查询操作记录
const unsigned int CST_CMD_GET_SENSOR_RECOTD               = 0x212E; //查询传感器数据记录
const unsigned int CST_CMD_GET_MONITOREDDVS_RECOTD         = 0x2130; //查询路基设备传感器数据记录
const unsigned int CST_CMD_GET_TOUR_STATUS                 = 0x2132; //查询巡检状态
const unsigned int CST_CMD_GET_SENSOR_RECOTD_SUMMARY       = 0x2134; //查询传感器数据记录统计
const unsigned int CST_CMD_GET_MONITOREDDVS_RECOTD_SUMMARY = 0x2136; //查询传感器数据记录统计
const unsigned int CST_CMD_PERFORM_STATION_DETECTION       = 0x2138; //执行站点巡检

const unsigned int CST_CMD_ROBOT_STATUS			= 0x8000; //机器人在线状态通知,TsRobotStatus
const unsigned int CST_CMD_ROBOT_READY			= 0x8001; //机器人就绪通知,TsRobotInfo
const unsigned int CST_CMD_ROBOT_CAR_STATUS		= 0x8002; //机器人车体实时状态通知,TsCarStatus
const unsigned int CST_CMD_ROBOT_SENSOR_INFO	= 0x8003; //机器人传感器信息通知,TsSensorInfo
const unsigned int CST_CMD_ROBOT_BATTERY_INFO	= 0x8004; //机器人电池信息通知,TsBatteryInfo
const unsigned int CST_CMD_ROBOT_THERMAL		= 0x8005; //机器人热成像检测最高温,TsRobotThermal
const unsigned int CST_CMD_ROBOT_RUNNING_LOG	= 0x8006; //机器人运行状态,TsRobotRunningLog
const unsigned int CST_CMD_ROBOT_ARM_STATUS		= 0x8007; //机械臂状态,TsRobotArmStatus
const unsigned int CST_CMD_TOUR_STATUS			= 0x8008; //机器人巡游状态,TsTourStatus
const unsigned int CST_CMD_ROBOT_PTZ_STATUS		= 0x8009; //机器人云台状态,TsRobotPtzStatus
const unsigned int CST_CMD_LIVE_MEDIA_STATUS    = 0x800A; //机器人实时流状态,TsRobotMediaStatus
const unsigned int CST_CMD_RECORD_STATUS        = 0x800B; //机器人录像状态,TsRobotMediaStatus
const unsigned int CST_CMD_UPLOAD_TOUR_STATION  = 0x800C; //巡检站点报告,TsTourStatus


const unsigned int CST_CMD_RETRIEVAL_STATUS		= 0x8100; //机器人录像取回状态

const unsigned int CST_CMD_ROADBASE_STATUS		= 0x8200; //路基设备状态,TsRoadbase
const unsigned int CST_CMD_LEVEL_SENSOR_STATUS  = 0x8201; //液位传感器状态,TsLevelSensorStatus

const unsigned int CST_CMD_ALARM_INFO			= 0x8300; //报警状态

const unsigned int CST_CMD_ROADBASE_BATTERY_STATUS = 0x8400; //获取充电电池信息


//SubscribeType
const unsigned short CST_SUBSCRIBE_SYSTEM				= 0x01;	//订阅系统消息
const unsigned short CST_SUBSCRIBE_ROBOT_ONLINE_STATUS	= 0x02;	//订阅机器人在线状态
const unsigned short CST_SUBSCRIBE_ROBOT_RUNNING_STATUS	= 0x04;	//订阅机器人运行状态
const unsigned short CST_SUBSCRIBE_ROADBASE				= 0x08;	//订阅路基设备信息

#endif //_COMMAND_CONST_H_