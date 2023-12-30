#ifndef _USR_ERROR_H_
#define _USR_ERROR_H_

//成功
#define USR_SUCCESS (0)

#define USR_ERR_BEGIN (0)

//{{系统错误
//空指针
#define USR_ERR_SYS_NULL_POINTER (USR_ERR_BEGIN - 1)
//模块不存在
#define USR_ERR_SYS_MODULE_EXIST (USR_ERR_BEGIN - 2)
//内存不足
#define USR_ERR_SYS_NOT_ENOUGH_MEMORY (USR_ERR_BEGIN - 3)
//未准备就绪
#define USR_ERR_SYS_NOT_READY (USR_ERR_BEGIN - 4)
//未找到
#define USR_ERR_SYS_NOT_FOUND (USR_ERR_BEGIN - 5)
//无效句柄
#define USR_ERR_SYS_INVALID_HANDLE (USR_ERR_BEGIN - 6)
//队列空
#define USR_ERR_SYS_QUEUE_EMPTY (USR_ERR_BEGIN - 7)
//队列满
#define USR_ERR_SYS_QUEUE_FULL (USR_ERR_BEGIN - 8)
//数据长度错误
#define USR_ERR_SYS_BAD_LENGTH (USR_ERR_BEGIN - 9)
//未知类型
#define USR_ERR_SYS_LOGIN_TYPE_UNKNOWN (USR_ERR_BEGIN - 10)
//服务器忙
#define USR_ERR_SYS_SERVER_BUSY (USR_ERR_BEGIN - 11)
//系统处理错误
#define USR_ERR_SYS_HANDLE_FAILED (USR_ERR_BEGIN - 12)
//参数错误
#define USR_ERR_SYS_BAD_PARAM (USR_ERR_BEGIN - 13)
//最大连接数
#define USR_ERR_SYS_MAX_CONNECTION_NUM (USR_ERR_BEGIN - 14)
//不支持
#define USR_ERR_SYS_NOT_SUPPORT (USR_ERR_BEGIN - 15)
//权限不足
#define USR_ERR_SYS_NOT_PRIVILEGE (USR_ERR_BEGIN - 16)
//用户不存在
#define USR_ERR_SYS_USER_NOT_EXISTED (USR_ERR_BEGIN - 17)
//用户组不存在
#define USR_ERR_SYS_GROUP_NOT_EXISTED (USR_ERR_BEGIN - 18)
//密码错误
#define USR_ERR_SYS_PWD_ERROR (USR_ERR_BEGIN - 19)
//操作结束
#define USR_ERR_SYS_FINISH (USR_ERR_BEGIN - 20)
//操作异常终止
#define USR_ERR_SYS_TERMINATION (USR_ERR_BEGIN - 21)
//未定义
#define USR_ERR_SYS_UNDEFINED (USR_ERR_BEGIN - 22)
//服务器上限
#define USR_ERR_SYS_UPPER_LIMIT (USR_ERR_BEGIN - 23)
//媒体源无数据
#define USR_ERR_MEDIA_DISCONNECT (USR_ERR_BEGIN - 24)
//媒体源无数据
#define USR_ERR_MEDIA_NO_DATA (USR_ERR_BEGIN - 25)
//处理超时
#define USR_ERR_SYS_TIMEOUT (USR_ERR_BEGIN - 26)
//处理中
#define USR_ERR_SYS_HANDLING (USR_ERR_BEGIN - 27)
//}}

//{{线程相关错误
#define USR_ERR_THREAD_BEGIN (USR_ERR_BEGIN - 100)  //线程错误 -100
//锁已初始化
#define USR_ERR_MUTEX_ALREADYINIT (USR_ERR_THREAD_BEGIN - 1)
//锁未初始化
#define USR_ERR_MUTEX_NOTINIT (USR_ERR_THREAD_BEGIN - 2)
//未创建锁
#define USR_ERR_MUTEX_CANTCREATEMUTEX (USR_ERR_THREAD_BEGIN - 3)
//线程错误
#define USR_ERR_THREAD_CANT_INIT_MUTEX (USR_ERR_THREAD_BEGIN - 11)
//线程启动失败
#define USR_ERR_THREAD_START_FAILED (USR_ERR_THREAD_BEGIN - 12)
//线程体未设置
#define USR_ERR_THREAD_THREAD_FUNC_NOT_SET (USR_ERR_THREAD_BEGIN - 13)
//线程未运行
#define USR_ERR_THREAD_NOT_RUNNING (USR_ERR_THREAD_BEGIN - 14)
//线程正在运行
#define USR_ERR_THREAD_ALREADY_RUNNING (USR_ERR_THREAD_BEGIN - 15)
//线程停止
#define USR_ERR_THREAD_STOP (USR_ERR_THREAD_BEGIN - 16)
//}}

//{{网络错误
#define USR_ERR_NETWORKIO_BEGIN (USR_ERR_THREAD_BEGIN - 100)  //网络错误 -200
// socket open 失败
#define USR_ERR_NETWORKIO_OPEN_FAILED (USR_ERR_NETWORKIO_BEGIN - 1)
// socket bind 失败
#define USR_ERR_NETWORKIO_BIND_FAILED (USR_ERR_NETWORKIO_BEGIN - 2)
// socket listen 失败
#define USR_ERR_NETWORKIO_LISTEN_FAILED (USR_ERR_NETWORKIO_BEGIN - 3)
// socket accept 失败
#define USR_ERR_NETWORKIO_ACCEPT_FAILED (USR_ERR_NETWORKIO_BEGIN - 4)
// socket accept 超时
#define USR_ERR_NETWORKIO_ACCEPT_TIMEOUT (USR_ERR_NETWORKIO_BEGIN - 5)
// socket connect 失败
#define USR_ERR_NETWORKIO_CONNECT_FAILED (USR_ERR_NETWORKIO_BEGIN - 6)
// socket connect 超时
#define USR_ERR_NETWORKIO_CONNECT_TIMEOUT (USR_ERR_NETWORKIO_BEGIN - 7)
// socket send 失败
#define USR_ERR_NETWORKIO_SEND_FAILED (USR_ERR_NETWORKIO_BEGIN - 8)
// socket send 超时
#define USR_ERR_NETWORKIO_SEND_TIMEOUT (USR_ERR_NETWORKIO_BEGIN - 9)
// socket recv 失败
#define USR_ERR_NETWORKIO_RECV_FAILED (USR_ERR_NETWORKIO_BEGIN - 10)
// socket recv 超时
#define USR_ERR_NETWORKIO_RECV_TIMEOUT (USR_ERR_NETWORKIO_BEGIN - 11)
// socket init 初始化失败
#define USR_ERR_NETWORKIO_INIT_FAILED (USR_ERR_NETWORKIO_BEGIN - 12)
// tcp设置nodelay失败
#define USR_ERR_NETWORKIO_TCP_NODELAY_FAILED (USR_ERR_NETWORKIO_BEGIN - 20)
// tcp设置keeplive失败
#define USR_ERR_NETWORKIO_KEEPLIVE_FAILED (USR_ERR_NETWORKIO_BEGIN - 21)
// get addrinfo 失败
#define USR_ERR_NETWORKIO_GET_ADDRINFO_FAILED (USR_ERR_NETWORKIO_BEGIN - 22)
// set reuseaddr 失败
#define USR_ERR_NETWORKIO_SET_REUSEADDR_FAILED (USR_ERR_NETWORKIO_BEGIN - 23)
// socket again
#define USR_ERR_NETWORKIO_AGAIN (USR_ERR_NETWORKIO_BEGIN - 24)
//}}

//{{设备错误
#define USR_ERR_DVS_BEGIN (USR_ERR_NETWORKIO_BEGIN - 100)  //设备错误 -300
//设备已存在
#define USR_ERR_DVS_EXISTED (USR_ERR_DVS_BEGIN - 1)
//设备不存在
#define USR_ERR_DVS_NOT_EXISTED (USR_ERR_DVS_BEGIN - 2)
//设备认证存在
#define USR_ERR_DVS_AUTH_FAILED (USR_ERR_DVS_BEGIN - 3)
//设备被占用
#define USR_ERR_DVS_USED (USR_ERR_DVS_BEGIN - 4)
//设备未准备就绪
#define USR_ERR_DVS_NOT_READY (USR_ERR_DVS_BEGIN - 5)

//播放器关闭
#define USR_ERR_PLAYER_CLOSED (USR_ERR_DVS_BEGIN - 50)
//}}

//{{文件错误
#define USR_ERR_FILE_BEGIN (USR_ERR_DVS_BEGIN - 100)  //文件错误 -400
//数据库失败
#define USR_ERR_DATABASE_OPEN_FAILED (USR_ERR_FILE_BEGIN - 1)
//创建数据库失败
#define USR_ERR_DATABASE_CREATE_TABLE_FAILED (USR_ERR_FILE_BEGIN - 2)
//数据库打开失败
#define USR_ERR_DATABASE_NOT_OPEN (USR_ERR_FILE_BEGIN - 3)
//数据库表不存在
#define USR_ERR_DATABASE_TABLE_NOT_EXIST (USR_ERR_FILE_BEGIN - 4)
//数据库无记录
#define USR_ERR_DATABASE_NO_RECORD (USR_ERR_FILE_BEGIN - 5)

#define USR_ERR_DB_OK          (USR_ERR_FILE_BEGIN -  20)   /* Successful result */
#define USR_ERR_DB_ERROR       (USR_ERR_DB_OK -  1)   /* SQL error or missing database */
#define USR_ERR_DB_INTERNAL    (USR_ERR_DB_OK -  2)   /* Internal logic error in SQLite */
#define USR_ERR_DB_PERM        (USR_ERR_DB_OK -  3)   /* Access permission denied */
#define USR_ERR_DB_ABORT       (USR_ERR_DB_OK -  4)   /* Callback routine requested an abort */
#define USR_ERR_DB_BUSY        (USR_ERR_DB_OK -  5)   /* The database file is locked */
#define USR_ERR_DB_LOCKED      (USR_ERR_DB_OK -  6)   /* A table in the database is locked */
#define USR_ERR_DB_NOMEM       (USR_ERR_DB_OK -  7)   /* A malloc() failed */
#define USR_ERR_DB_READONLY    (USR_ERR_DB_OK -  8)   /* Attempt to write a readonly database */
#define USR_ERR_DB_INTERRUPT   (USR_ERR_DB_OK -  9)   /* Operation terminated by sqlite3_interrupt()*/
#define USR_ERR_DB_IOERR       (USR_ERR_DB_OK - 10)   /* Some kind of disk I/O error occurred */
#define USR_ERR_DB_CORRUPT     (USR_ERR_DB_OK - 11)   /* The database disk image is malformed */
#define USR_ERR_DB_NOTFOUND    (USR_ERR_DB_OK - 12)   /* Unknown opcode in sqlite3_file_control() */
#define USR_ERR_DB_FULL        (USR_ERR_DB_OK - 13)   /* Insertion failed because database is full */
#define USR_ERR_DB_CANTOPEN    (USR_ERR_DB_OK - 14)   /* Unable to open the database file */
#define USR_ERR_DB_PROTOCOL    (USR_ERR_DB_OK - 15)   /* Database lock protocol error */
#define USR_ERR_DB_EMPTY       (USR_ERR_DB_OK - 16)   /* Database is empty */
#define USR_ERR_DB_SCHEMA      (USR_ERR_DB_OK - 17)   /* The database schema changed */
#define USR_ERR_DB_TOOBIG      (USR_ERR_DB_OK - 18)   /* String or BLOB exceeds size limit */
#define USR_ERR_DB_CONSTRAINT  (USR_ERR_DB_OK - 19)   /* Abort due to constraint violation */
#define USR_ERR_DB_MISMATCH    (USR_ERR_DB_OK - 20)   /* Data type mismatch */
#define USR_ERR_DB_MISUSE      (USR_ERR_DB_OK - 21)   /* Library used incorrectly */
#define USR_ERR_DB_NOLFS       (USR_ERR_DB_OK - 22)   /* Uses OS features not supported on host */
#define USR_ERR_DB_AUTH        (USR_ERR_DB_OK - 23)   /* Authorization denied */
#define USR_ERR_DB_FORMAT      (USR_ERR_DB_OK - 24)   /* Auxiliary database format error */
#define USR_ERR_DB_RANGE       (USR_ERR_DB_OK - 25)   /* 2nd parameter to sqlite3_bind out of range */
#define USR_ERR_DB_NOTADB      (USR_ERR_DB_OK - 26)   /* File opened that is not a database file */
#define USR_ERR_DB_NOTICE      (USR_ERR_DB_OK - 27)   /* Notifications from sqlite3_log() */
#define USR_ERR_DB_WARNING     (USR_ERR_DB_OK - 28)   /* Warnings from sqlite3_log() */

//文件打开失败
#define USR_ERR_FILE_OPEN_FAILED (USR_ERR_FILE_BEGIN - 60)
//读文件错误
#define USR_ERR_FILE_READ_FAILED (USR_ERR_FILE_BEGIN - 61)
//读文件错误
#define USR_ERR_FILE_WRITE_FAILED (USR_ERR_FILE_BEGIN - 62)
//读文件错误
#define USR_ERR_FILE_NOT_OPEN (USR_ERR_FILE_BEGIN - 63)
//文件不存在
#define USR_ERR_FILE_NOT_EXISTED (USR_ERR_FILE_BEGIN - 64)
//创建目录失败
#define USR_ERR_CREATE_DIR_FAILED (USR_ERR_FILE_BEGIN - 70)
//}}

//{{磁盘错误
#define USR_ERR_DISK_BEGIN (USR_ERR_FILE_BEGIN - 100)  //文件错误 -500
//磁盘不存在
#define USR_ERR_DISK_NO_EXIST (USR_ERR_DISK_BEGIN - 1)
//磁盘未格式化
#define USR_ERR_DISK_NOT_FORMAT (USR_ERR_DISK_BEGIN - 2)
//磁盘格式化失败
#define USR_ERR_DISK_FORMAT_FAILED (USR_ERR_DISK_BEGIN - 3)
//}}

//{{SDK错误
#define USR_ERR_SDK_BEGIN (USR_ERR_DISK_BEGIN - 100)  // SDK错误 -600
//未知命令
#define USR_ERR_COMMAND_UNKNOWN (USR_ERR_SDK_BEGIN - 1)
//命令解析失败
#define USR_ERR_COMMAND_PARSE_FAILED (USR_ERR_SDK_BEGIN - 2)
//命令格式错误
#define USR_ERR_COMMAND_FORMAT_ERROR (USR_ERR_SDK_BEGIN - 3)
//命令组装错误
#define USR_ERR_COMMAND_ASSEMBLY_FAILED (USR_ERR_SDK_BEGIN - 4)
//负载解析错误
#define USR_ERR_COMMAND_PAYLOAD_PARSE_ERROR (USR_ERR_SDK_BEGIN - 5)
//负载类型错误
#define USR_ERR_COMMAND_PAYLOAD_TYPE_ERROR (USR_ERR_SDK_BEGIN - 6)
//不是期望命令
#define USR_ERR_COMMAND_NOT_EXPECTED (USR_ERR_SDK_BEGIN - 7)
// SDK未连接
#define USR_ERR_SDK_DISCONNECT (USR_ERR_SDK_BEGIN - 20)
//包头解析错误
#define USR_ERR_PACKET_HEAD_PARSE_ERROR (USR_ERR_SDK_BEGIN - 50)
// SDK类型错误
#define USR_ERR_SDK_TYPE_ERROR (USR_ERR_SDK_BEGIN - 60)
//}}

//{{录像错误
#define USR_ERR_RECORD_BEGIN (USR_ERR_SDK_BEGIN - 100)  //录像错误 -700
//录像不存在
#define USR_ERR_RECORD_NOT_EXIST (USR_ERR_RECORD_BEGIN - 1)
//到达文件头
#define USR_ERR_RECORD_AT_BEGIN_TIME (USR_ERR_RECORD_BEGIN - 2)
//到达文件尾
#define USR_ERR_RECORD_AT_END_TIME (USR_ERR_RECORD_BEGIN - 3)
//录像空白
#define USR_ERR_RECORD_AT_BLANK_SPACE (USR_ERR_RECORD_BEGIN - 4)
//录像停止
#define USR_ERR_RECORD_STOP (USR_ERR_RECORD_BEGIN - 5)
//录像失败
#define USR_ERR_RECORD_FAILED (USR_ERR_RECORD_BEGIN - 6)
//}}

#define USR_ERR_CAR_BASE -1000
#define USR_ERR_CAR_BUSY USR_ERR_CAR_BASE
#define USR_ERR_CAR_FAULT (USR_ERR_CAR_BASE - 1)
#define USR_ERR_CAR_INVALID (USR_ERR_CAR_BASE - 2)
#define USR_ERR_CAR_CHARGE_STATION_MANUAl (USR_ERR_CAR_BASE - 3)
#define USR_ERR_CAR_GET_STATION_FAILD (USR_ERR_CAR_BASE - 4)
#define USR_ERR_CAR_STATION_NOT_EXIST (USR_ERR_CAR_BASE - 5)
#define USR_ERR_CAR_UNIMPLIMENT (USR_ERR_CAR_BASE - 6)
#define USR_ERR_CAR_ROAD_MODULE_DISABLE (USR_ERR_CAR_BASE - 7)

#endif  //_USR_ERROR_H_k