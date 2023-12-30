#include "UnsSerializationTool.h"
#include "CommandConst.h"
#include "USRError.h"
#include "UsrDomain.h"

/***************************************************************************************************
以下由mock_robot_linux  createUnsSerializationTool()生成,
增加命令时需要从mock_robot_linux 生成的目录下UnsSerializationTool 更新
***************************************************************************************************/

const char* UnsStringCmd(unsigned int cmdID)
{
    switch (cmdID)
    {
    case CST_CMD_LOGIN:
        return "CMD_LOGIN";
    case CST_CMD_LOGOUT:
        return "CMD_LOGOUT";
    case CST_CMD_GET_ROBOT_INFO:
        return "CMD_GET_ROBOT_INFO";
    case CST_CMD_GET_RECORD_POLICY:
        return "CMD_GET_RECORD_POLICY";
    case CST_CMD_SET_RECORD_POLICY:
        return "CMD_SET_RECORD_POLICY";
    case CST_CMD_GET_RECORD_EXPIRE_TIME:
        return "CMD_GET_RECORD_EXPIRE_TIME";
    case CST_CMD_SET_RECORD_EXPIRE_TIME:
        return "CMD_SET_RECORD_EXPIRE_TIME";
    case CST_CMD_RECORD_QUERY:
        return "CMD_RECORD_QUERY";
    case CST_CMD_SNAPSHOT_QUERY:
        return "CMD_SNAPSHOT_QUERY";
    case CST_CMD_HEARTBEAT:
        return "CMD_HEARTBEAT";
    case CST_CMD_GET_ROBOT_STATUS:
        return "CMD_GET_ROBOT_STATUS";
    case CST_CMD_GET_MEDIA_SUMMARY_INFO:
        return "CMD_GET_MEDIA_SUMMARY_INFO";
    case CST_CMD_SET_ROBOT_NAME:
        return "CMD_SET_ROBOT_NAME";
    case CST_CMD_DEL_ROBOT:
        return "CMD_DEL_ROBOT";
    case CST_CMD_GET_UNS_DATE_TIME:
        return "CMD_GET_UNS_DATE_TIME";
    case CST_CMD_GET_VERSION:
        return "CMD_GET_VERSION";
    case CST_CMD_GET_RECORD_ROBOT_INFO:
        return "CMD_GET_RECORD_ROBOT_INFO";
    case CST_CMD_GET_RECORD_MEDIA_SUMMARY_INFO:
        return "CMD_GET_RECORD_MEDIA_SUMMARY_INFO";
    case CST_CMD_GET_RECORD_CALENDAR:
        return "CMD_GET_RECORD_CALENDAR";
    case CST_CMD_GET_LIVE_MEDIA_STATUS:
        return "CMD_GET_LIVE_MEDIA_STATUS";
    case CST_CMD_GET_RECORD_STATUS:
        return "CMD_GET_RECORD_STATUS";
    case CST_CMD_GET_ROBOT_NAME:
        return "CMD_GET_ROBOT_NAME";
    case CST_CMD_GET_ROBOT_ONLINE_COUNT:
        return "CMD_GET_ROBOT_ONLINE_COUNT";
    case CST_CMD_GET_ROBOT_LOCATION:
        return "CMD_GET_ROBOT_LOCATION";
    case CST_CMD_ADD_ROLE_INFO:
        return "CMD_ADD_ROLE_INFO";
    case CST_CMD_GET_ROLE_INFO:
        return "CMD_GET_ROLE_INFO";
    case CST_CMD_SET_ROLE_INFO:
        return "CMD_SET_ROLE_INFO";
    case CST_CMD_DELETE_ROLE_INFO:
        return "CMD_DELETE_ROLE_INFO";
    case CST_CMD_SET_ROLE_PRIVILEGE:
        return "CMD_SET_ROLE_PRIVILEGE";
    case CST_CMD_GET_ROLE_PRIVILEGE:
        return "CMD_GET_ROLE_PRIVILEGE";
    case CST_CMD_CHECK_USER_EXISTED:
        return "CMD_CHECK_USER_EXISTED";
    case CST_CMD_ADD_USER_INFO:
        return "CMD_ADD_USER_INFO";
    case CST_CMD_GET_USER_INFO:
        return "CMD_GET_USER_INFO";
    case CST_CMD_SET_USER_INFO:
        return "CMD_SET_USER_INFO";
    case CST_CMD_DELETE_USER_INFO:
        return "CMD_DELETE_USER_INFO";
    case CST_CMD_CREATE_DATA_CHANNEL:
        return "CMD_CREATE_DATA_CHANNEL";
    case CST_CMD_START_LIVE_PREVIEW:
        return "CMD_START_LIVE_PREVIEW";
    case CST_CMD_STOP_LIVE_PREVIEW:
        return "CMD_STOP_LIVE_PREVIEW";
    case CST_CMD_START_RETRIEVAL:
        return "CMD_START_RETRIEVAL";
    case CST_CMD_STOP_RETRIEVAL:
        return "CMD_STOP_RETRIEVAL";
    case CST_CMD_RETRIEVAL_CTRL:
        return "CMD_RETRIEVAL_CTRL";
    case CST_CMD_START_MSG_TRANSMIT:
        return "CMD_START_MSG_TRANSMIT";
    case CST_CMD_STOP_MSG_TRANSMIT:
        return "CMD_STOP_MSG_TRANSMIT";
    case CST_CMD_START_RETRIEVAL_V2:
        return "CMD_START_RETRIEVAL_V2";
    case CST_CMD_STOP_RETRIEVAL_V2:
        return "CMD_STOP_RETRIEVAL_V2";
    case CST_CMD_SET_RETRIEVAL_TIME:
        return "CMD_SET_RETRIEVAL_TIME";
    case CST_CMD_SET_SKIP_BLAND_SPACE:
        return "CMD_SET_SKIP_BLAND_SPACE";
    case CST_CMD_SET_RETRIEVAL_RATE:
        return "CMD_SET_RETRIEVAL_RATE";
    case CST_CMD_START_CHANNEL_MEDIA:
        return "CMD_START_CHANNEL_MEDIA";
    case CST_CMD_STOP_CHANNEL_MEDIA:
        return "CMD_STOP_CHANNEL_MEDIA";
    case CST_CMD_RETRIEVAL_LOCATE_TIME:
        return "CMD_RETRIEVAL_LOCATE_TIME";
    case CST_CMD_PAUSE:
        return "CMD_PAUSE";
    case CST_CMD_PLAY_NEXT_FRAME:
        return "CMD_PLAY_NEXT_FRAME";
    case CST_CMD_BEGIN_BROWSE:
        return "CMD_BEGIN_BROWSE";
    case CST_CMD_BROWSE:
        return "CMD_BROWSE";
    case CST_CMD_END_BROWSE:
        return "CMD_END_BROWSE";
    case CST_CMD_START_MEDIE_PROXY:
        return "CMD_START_MEDIE_PROXY";
    case CST_CMD_STOP_MEDIE_PROXY:
        return "CMD_STOP_MEDIE_PROXY";
    case CST_CMD_QUERY_ALARM_LOG:
        return "CMD_QUERY_ALARM_LOG";
    case CST_CMD_QUERY_ALARM_SUMMARY:
        return "CMD_QUERY_ALARM_SUMMARY";
    case CST_CMD_START_TALKBACK:
        return "CMD_START_TALKBACK";
    case CST_CMD_STOP_TALKBACK:
        return "CMD_STOP_TALKBACK";
    case CST_CMD_SNAPSHOT_CTRL:
        return "CMD_SNAPSHOT_CTRL";
    case CST_CMD_DVS_UPGRADE:
        return "CMD_DVS_UPGRADE";
    case CST_CMD_STOP_UPGRADE:
        return "CMD_STOP_UPGRADE";
    case CST_CMD_UPGRADE_STATUS:
        return "CMD_UPGRADE_STATUS";
    case CST_CMD_IVAS_GET_STATUS:
        return "CMD_IVAS_GET_STATUS";
    case CST_CMD_IVAS_ADD_SAMPLE:
        return "CMD_IVAS_ADD_SAMPLE";
    case CST_CMD_IVAS_CLEAR_SAMPLE:
        return "CMD_IVAS_CLEAR_SAMPLE";
    case CST_CMD_IVAS_RELEARN:
        return "CMD_IVAS_RELEARN";
    case CST_CMD_IVAS_IMAGE_ANALYZING:
        return "CMD_IVAS_IMAGE_ANALYZING";
    case CST_CMD_IVAS_UPLOAD_SAMPLE:
        return "CMD_IVAS_UPLOAD_SAMPLE";
    case CST_CMD_GET_OPERATOR_RIGHTS:
        return "CMD_GET_OPERATOR_RIGHTS";
    case CST_CMD_CTRL_ROBOT_MOTION:
        return "CMD_CTRL_ROBOT_MOTION";
    case CST_CMD_SET_ROBOT_PRESSURE:
        return "CMD_SET_ROBOT_PRESSURE";
    case CST_CMD_SET_ROBOT_LAMP:
        return "CMD_SET_ROBOT_LAMP";
    case CST_CMD_ROBOT_PARKING:
        return "CMD_ROBOT_PARKING";
    case CST_CMD_ROBOT_SCRAM:
        return "CMD_ROBOT_SCRAM";
    case CST_CMD_ROBOT_CLEAR:
        return "CMD_ROBOT_CLEAR";
    case CST_CMD_ROBOT_CHARGE:
        return "CMD_ROBOT_CHARGE";
    case CST_CMD_ROBOT_REVISE_LOCATION:
        return "CMD_ROBOT_REVISE_LOCATION";
    case CST_CMD_SET_ROBOT_TOUR:
        return "CMD_SET_ROBOT_TOUR";
    case CST_CMD_GET_ROBOT_TOUR:
        return "CMD_GET_ROBOT_TOUR";
    case CST_CMD_ROBOT_AUTO_TOUR:
        return "CMD_ROBOT_AUTO_TOUR";
    case CST_CMD_ROBOT_PTZ_CTRL:
        return "CMD_ROBOT_PTZ_CTRL";
    case CST_CMD_ROBOT_SHUTDOWN:
        return "CMD_ROBOT_SHUTDOWN";
    case CST_CMD_ROBOT_RESTART:
        return "CMD_ROBOT_RESTART";
    case CST_CMD_ROBOT_ARM_CTRL:
        return "CMD_ROBOT_ARM_CTRL";
    case CST_CMD_ROBOT_BACK_HOME:
        return "CMD_ROBOT_BACK_HOME";
    case CST_CMD_GET_ALARM_POLICY:
        return "CMD_GET_ALARM_POLICY";
    case CST_CMD_SET_ALARM_POLICY:
        return "CMD_SET_ALARM_POLICY";
    case CST_CMD_GET_ROBOT_LAMP:
        return "CMD_GET_ROBOT_LAMP";
    case CST_CMD_GET_AVOID_OBSTACLE:
        return "CMD_GET_AVOID_OBSTACLE";
    case CST_CMD_SET_AVOID_OBSTACLE:
        return "CMD_SET_AVOID_OBSTACLE";
    case CST_CMD_ROBOT_GOTO_LOCATION:
        return "CMD_ROBOT_GOTO_LOCATION";
    case CST_CMD_ROBOT_MANUAL_TOUR:
        return "CMD_ROBOT_MANUAL_TOUR";
    case CST_CMD_ROBOT_TOUR_CTRL:
        return "CMD_ROBOT_TOUR_CTRL";
    case CST_CMD_GET_MONITORED_DVS_ALARM_POLICY:
        return "CMD_GET_MONITORED_DVS_ALARM_POLICY";
    case CST_CMD_SET_MONITORED_DVS_ALARM_POLICY:
        return "CMD_SET_MONITORED_DVS_ALARM_POLICY";
    case CST_CMD_ROBOT_PTZ_3DPOSITION:
        return "CMD_ROBOT_PTZ_3DPOSITION";
    case CST_CMD_ROBOT_WIRELESS_ADDR:
        return "CMD_ROBOT_WIRELESS_ADDR";
    case CST_CMD_ROBOT_RTSP_MEDIA_ADDR:
        return "CMD_ROBOT_RTSP_MEDIA_ADDR";
    case CST_CMD_ROADBASE_CTRL:
        return "CMD_ROADBASE_CTRL";
    case CST_CMD_ADD_ROADBASE_S2E:
        return "CMD_ADD_ROADBASE_S2E";
    case CST_CMD_GET_ROADBASE_S2E:
        return "CMD_GET_ROADBASE_S2E";
    case CST_CMD_SET_ROADBASE_S2E:
        return "CMD_SET_ROADBASE_S2E";
    case CST_CMD_DEL_ROADBASE_S2E:
        return "CMD_DEL_ROADBASE_S2E";
    case CST_CMD_GET_ROADBASE:
        return "CMD_GET_ROADBASE";
    case CST_CMD_SET_ROADBASE:
        return "CMD_SET_ROADBASE";
    case CST_CMD_DEL_ROADBASE:
        return "CMD_DEL_ROADBASE";
    case CST_CMD_ACTIVATE_S2E:
        return "CMD_ACTIVATE_S2E";
    case CST_CMD_ADD_ROADBASE:
        return "CMD_ADD_ROADBASE";
    case CST_CMD_ADD_PIPE_GALLERY:
        return "CMD_ADD_PIPE_GALLERY";
    case CST_CMD_GET_PIPE_GALLERY:
        return "CMD_GET_PIPE_GALLERY";
    case CST_CMD_SET_PIPE_GALLERY:
        return "CMD_SET_PIPE_GALLERY";
    case CST_CMD_DEL_PIPE_GALLERY:
        return "CMD_DEL_PIPE_GALLERY";
    case CST_CMD_ADD_TOUR_STATION:
        return "CMD_ADD_TOUR_STATION";
    case CST_CMD_GET_TOUR_STATION:
        return "CMD_GET_TOUR_STATION";
    case CST_CMD_SET_TOUR_STATION:
        return "CMD_SET_TOUR_STATION";
    case CST_CMD_DEL_TOUR_STATION:
        return "CMD_DEL_TOUR_STATION";
    case CST_CMD_ADD_TOUR_LINE:
        return "CMD_ADD_TOUR_LINE";
    case CST_CMD_GET_TOUR_LINE:
        return "CMD_GET_TOUR_LINE";
    case CST_CMD_SET_TOUR_LINE:
        return "CMD_SET_TOUR_LINE";
    case CST_CMD_DEL_TOUR_LINE:
        return "CMD_DEL_TOUR_LINE";
    case CST_CMD_ADD_TOUR_TASK:
        return "CMD_ADD_TOUR_TASK";
    case CST_CMD_GET_TOUR_TASK:
        return "CMD_GET_TOUR_TASK";
    case CST_CMD_SET_TOUR_TASK:
        return "CMD_SET_TOUR_TASK";
    case CST_CMD_DEL_TOUR_TASK:
        return "CMD_DEL_TOUR_TASK";
    case CST_CMD_UPLOAD_DOWNLOAD_REPORT:
        return "CMD_UPLOAD_DOWNLOAD_REPORT";
    case CST_CMD_QUERY_TOUR_REPORT:
        return "CMD_QUERY_TOUR_REPORT";
    case CST_CMD_QUERY_TOUR_STATUS:
        return "CMD_QUERY_TOUR_STATUS";
    case CST_CMD_SUMMARY_QUERY_TOUR_REPORT:
        return "CMD_SUMMARY_QUERY_TOUR_REPORT";
    case CST_CMD_SUBSCRIBE_RT_TOUR_STATION:
        return "CMD_SUBSCRIBE_RT_TOUR_STATION";
    case CST_CMD_UNSUBSCRIBE_RT_TOUR_STATION:
        return "CMD_UNSUBSCRIBE_RT_TOUR_STATION";
    case CST_CMD_GET_OPERATION_RECOTD:
        return "CMD_GET_OPERATION_RECOTD";
    case CST_CMD_GET_SENSOR_RECOTD:
        return "CMD_GET_SENSOR_RECOTD";
    case CST_CMD_GET_MONITOREDDVS_RECOTD:
        return "CMD_GET_MONITOREDDVS_RECOTD";
    case CST_CMD_GET_TOUR_STATUS:
        return "CMD_GET_TOUR_STATUS";
    case CST_CMD_GET_SENSOR_RECOTD_SUMMARY:
        return "CMD_GET_SENSOR_RECOTD_SUMMARY";
    case CST_CMD_GET_MONITOREDDVS_RECOTD_SUMMARY:
        return "CMD_GET_MONITOREDDVS_RECOTD_SUMMARY";
    case CST_CMD_PERFORM_STATION_DETECTION:
        return "CMD_PERFORM_STATION_DETECTION";
    case CST_CMD_ROBOT_STATUS:
        return "CMD_ROBOT_STATUS";
    case CST_CMD_ROBOT_READY:
        return "CMD_ROBOT_READY";
    case CST_CMD_ROBOT_CAR_STATUS:
        return "CMD_ROBOT_CAR_STATUS";
    case CST_CMD_ROBOT_SENSOR_INFO:
        return "CMD_ROBOT_SENSOR_INFO";
    case CST_CMD_ROBOT_BATTERY_INFO:
        return "CMD_ROBOT_BATTERY_INFO";
    case CST_CMD_ROBOT_THERMAL:
        return "CMD_ROBOT_THERMAL";
    case CST_CMD_ROBOT_RUNNING_LOG:
        return "CMD_ROBOT_RUNNING_LOG";
    case CST_CMD_ROBOT_ARM_STATUS:
        return "CMD_ROBOT_ARM_STATUS";
    case CST_CMD_TOUR_STATUS:
        return "CMD_TOUR_STATUS";
    case CST_CMD_ROBOT_PTZ_STATUS:
        return "CMD_ROBOT_PTZ_STATUS";
    case CST_CMD_LIVE_MEDIA_STATUS:
        return "CMD_LIVE_MEDIA_STATUS";
    case CST_CMD_RECORD_STATUS:
        return "CMD_RECORD_STATUS";
    case CST_CMD_UPLOAD_TOUR_STATION:
        return "CMD_UPLOAD_TOUR_STATION";
    case CST_CMD_RETRIEVAL_STATUS:
        return "CMD_RETRIEVAL_STATUS";
    case CST_CMD_ROADBASE_STATUS:
        return "CMD_ROADBASE_STATUS";
    case CST_CMD_LEVEL_SENSOR_STATUS:
        return "CMD_LEVEL_SENSOR_STATUS";
    case CST_CMD_ALARM_INFO:
        return "CMD_ALARM_INFO";
    case CST_CMD_ROADBASE_BATTERY_STATUS:
        return "CMD_ROADBASE_BATTERY_STATUS";
    }
    return "Unknown";
}
const char* UnsStringError(int usrError)
{
    switch (usrError)
    {
    case USR_SUCCESS:
        return "SUCCESS";
    case USR_ERR_SYS_NULL_POINTER:
        return "SYS_NULL_POINTER";
    case USR_ERR_SYS_MODULE_EXIST:
        return "SYS_MODULE_EXIST";
    case USR_ERR_SYS_NOT_ENOUGH_MEMORY:
        return "SYS_NOT_ENOUGH_MEMORY";
    case USR_ERR_SYS_NOT_READY:
        return "SYS_NOT_READY";
    case USR_ERR_SYS_NOT_FOUND:
        return "SYS_NOT_FOUND";
    case USR_ERR_SYS_INVALID_HANDLE:
        return "SYS_INVALID_HANDLE";
    case USR_ERR_SYS_QUEUE_EMPTY:
        return "SYS_QUEUE_EMPTY";
    case USR_ERR_SYS_QUEUE_FULL:
        return "SYS_QUEUE_FULL";
    case USR_ERR_SYS_BAD_LENGTH:
        return "SYS_BAD_LENGTH";
    case USR_ERR_SYS_LOGIN_TYPE_UNKNOWN:
        return "SYS_LOGIN_TYPE_UNKNOWN";
    case USR_ERR_SYS_SERVER_BUSY:
        return "SYS_SERVER_BUSY";
    case USR_ERR_SYS_HANDLE_FAILED:
        return "SYS_HANDLE_FAILED";
    case USR_ERR_SYS_BAD_PARAM:
        return "SYS_BAD_PARAM";
    case USR_ERR_SYS_MAX_CONNECTION_NUM:
        return "SYS_MAX_CONNECTION_NUM";
    case USR_ERR_SYS_NOT_SUPPORT:
        return "SYS_NOT_SUPPORT";
    case USR_ERR_SYS_NOT_PRIVILEGE:
        return "SYS_NOT_PRIVILEGE";
    case USR_ERR_SYS_USER_NOT_EXISTED:
        return "SYS_USER_NOT_EXISTED";
    case USR_ERR_SYS_GROUP_NOT_EXISTED:
        return "SYS_GROUP_NOT_EXISTED";
    case USR_ERR_SYS_PWD_ERROR:
        return "SYS_PWD_ERROR";
    case USR_ERR_SYS_FINISH:
        return "SYS_FINISH";
    case USR_ERR_SYS_TERMINATION:
        return "SYS_TERMINATION";
    case USR_ERR_SYS_UNDEFINED:
        return "SYS_UNDEFINED";
    case USR_ERR_SYS_UPPER_LIMIT:
        return "SYS_UPPER_LIMIT";
    case USR_ERR_MEDIA_DISCONNECT:
        return "MEDIA_DISCONNECT";
    case USR_ERR_MEDIA_NO_DATA:
        return "MEDIA_NO_DATA";
    case USR_ERR_SYS_TIMEOUT:
        return "SYS_TIMEOUT";
    case USR_ERR_SYS_HANDLING:
        return "SYS_HANDLING";
    case USR_ERR_THREAD_BEGIN:
        return "THREAD_BEGIN";
    case USR_ERR_MUTEX_ALREADYINIT:
        return "MUTEX_ALREADYINIT";
    case USR_ERR_MUTEX_NOTINIT:
        return "MUTEX_NOTINIT";
    case USR_ERR_MUTEX_CANTCREATEMUTEX:
        return "MUTEX_CANTCREATEMUTEX";
    case USR_ERR_THREAD_CANT_INIT_MUTEX:
        return "THREAD_CANT_INIT_MUTEX";
    case USR_ERR_THREAD_START_FAILED:
        return "THREAD_START_FAILED";
    case USR_ERR_THREAD_THREAD_FUNC_NOT_SET:
        return "THREAD_THREAD_FUNC_NOT_SET";
    case USR_ERR_THREAD_NOT_RUNNING:
        return "THREAD_NOT_RUNNING";
    case USR_ERR_THREAD_ALREADY_RUNNING:
        return "THREAD_ALREADY_RUNNING";
    case USR_ERR_THREAD_STOP:
        return "THREAD_STOP";
    case USR_ERR_NETWORKIO_BEGIN:
        return "NETWORKIO_BEGIN";
    case USR_ERR_NETWORKIO_OPEN_FAILED:
        return "NETWORKIO_OPEN_FAILED";
    case USR_ERR_NETWORKIO_BIND_FAILED:
        return "NETWORKIO_BIND_FAILED";
    case USR_ERR_NETWORKIO_LISTEN_FAILED:
        return "NETWORKIO_LISTEN_FAILED";
    case USR_ERR_NETWORKIO_ACCEPT_FAILED:
        return "NETWORKIO_ACCEPT_FAILED";
    case USR_ERR_NETWORKIO_ACCEPT_TIMEOUT:
        return "NETWORKIO_ACCEPT_TIMEOUT";
    case USR_ERR_NETWORKIO_CONNECT_FAILED:
        return "NETWORKIO_CONNECT_FAILED";
    case USR_ERR_NETWORKIO_CONNECT_TIMEOUT:
        return "NETWORKIO_CONNECT_TIMEOUT";
    case USR_ERR_NETWORKIO_SEND_FAILED:
        return "NETWORKIO_SEND_FAILED";
    case USR_ERR_NETWORKIO_SEND_TIMEOUT:
        return "NETWORKIO_SEND_TIMEOUT";
    case USR_ERR_NETWORKIO_RECV_FAILED:
        return "NETWORKIO_RECV_FAILED";
    case USR_ERR_NETWORKIO_RECV_TIMEOUT:
        return "NETWORKIO_RECV_TIMEOUT";
    case USR_ERR_NETWORKIO_INIT_FAILED:
        return "NETWORKIO_INIT_FAILED";
    case USR_ERR_NETWORKIO_TCP_NODELAY_FAILED:
        return "NETWORKIO_TCP_NODELAY_FAILED";
    case USR_ERR_NETWORKIO_KEEPLIVE_FAILED:
        return "NETWORKIO_KEEPLIVE_FAILED";
    case USR_ERR_NETWORKIO_GET_ADDRINFO_FAILED:
        return "NETWORKIO_GET_ADDRINFO_FAILED";
    case USR_ERR_NETWORKIO_SET_REUSEADDR_FAILED:
        return "NETWORKIO_SET_REUSEADDR_FAILED";
    case USR_ERR_NETWORKIO_AGAIN:
        return "NETWORKIO_AGAIN";
    case USR_ERR_DVS_BEGIN:
        return "DVS_BEGIN";
    case USR_ERR_DVS_EXISTED:
        return "DVS_EXISTED";
    case USR_ERR_DVS_NOT_EXISTED:
        return "DVS_NOT_EXISTED";
    case USR_ERR_DVS_AUTH_FAILED:
        return "DVS_AUTH_FAILED";
    case USR_ERR_DVS_USED:
        return "DVS_USED";
    case USR_ERR_DVS_NOT_READY:
        return "DVS_NOT_READY";
    case USR_ERR_PLAYER_CLOSED:
        return "PLAYER_CLOSED";
    case USR_ERR_FILE_BEGIN:
        return "FILE_BEGIN";
    case USR_ERR_DATABASE_OPEN_FAILED:
        return "DATABASE_OPEN_FAILED";
    case USR_ERR_DATABASE_CREATE_TABLE_FAILED:
        return "DATABASE_CREATE_TABLE_FAILED";
    case USR_ERR_DATABASE_NOT_OPEN:
        return "DATABASE_NOT_OPEN";
    case USR_ERR_DATABASE_TABLE_NOT_EXIST:
        return "DATABASE_TABLE_NOT_EXIST";
    case USR_ERR_DATABASE_NO_RECORD:
        return "DATABASE_NO_RECORD";
    case USR_ERR_DB_OK:
        return "DB_OK";
    case USR_ERR_DB_ERROR:
        return "DB_ERROR";
    case USR_ERR_DB_INTERNAL:
        return "DB_INTERNAL";
    case USR_ERR_DB_PERM:
        return "DB_PERM";
    case USR_ERR_DB_ABORT:
        return "DB_ABORT";
    case USR_ERR_DB_BUSY:
        return "DB_BUSY";
    case USR_ERR_DB_LOCKED:
        return "DB_LOCKED";
    case USR_ERR_DB_NOMEM:
        return "DB_NOMEM";
    case USR_ERR_DB_READONLY:
        return "DB_READONLY";
    case USR_ERR_DB_INTERRUPT:
        return "DB_INTERRUPT";
    case USR_ERR_DB_IOERR:
        return "DB_IOERR";
    case USR_ERR_DB_CORRUPT:
        return "DB_CORRUPT";
    case USR_ERR_DB_NOTFOUND:
        return "DB_NOTFOUND";
    case USR_ERR_DB_FULL:
        return "DB_FULL";
    case USR_ERR_DB_CANTOPEN:
        return "DB_CANTOPEN";
    case USR_ERR_DB_PROTOCOL:
        return "DB_PROTOCOL";
    case USR_ERR_DB_EMPTY:
        return "DB_EMPTY";
    case USR_ERR_DB_SCHEMA:
        return "DB_SCHEMA";
    case USR_ERR_DB_TOOBIG:
        return "DB_TOOBIG";
    case USR_ERR_DB_CONSTRAINT:
        return "DB_CONSTRAINT";
    case USR_ERR_DB_MISMATCH:
        return "DB_MISMATCH";
    case USR_ERR_DB_MISUSE:
        return "DB_MISUSE";
    case USR_ERR_DB_NOLFS:
        return "DB_NOLFS";
    case USR_ERR_DB_AUTH:
        return "DB_AUTH";
    case USR_ERR_DB_FORMAT:
        return "DB_FORMAT";
    case USR_ERR_DB_RANGE:
        return "DB_RANGE";
    case USR_ERR_DB_NOTADB:
        return "DB_NOTADB";
    case USR_ERR_DB_NOTICE:
        return "DB_NOTICE";
    case USR_ERR_DB_WARNING:
        return "DB_WARNING";
    case USR_ERR_FILE_OPEN_FAILED:
        return "FILE_OPEN_FAILED";
    case USR_ERR_FILE_READ_FAILED:
        return "FILE_READ_FAILED";
    case USR_ERR_FILE_WRITE_FAILED:
        return "FILE_WRITE_FAILED";
    case USR_ERR_FILE_NOT_OPEN:
        return "FILE_NOT_OPEN";
    case USR_ERR_FILE_NOT_EXISTED:
        return "FILE_NOT_EXISTED";
    case USR_ERR_CREATE_DIR_FAILED:
        return "CREATE_DIR_FAILED";
    case USR_ERR_DISK_BEGIN:
        return "DISK_BEGIN";
    case USR_ERR_DISK_NO_EXIST:
        return "DISK_NO_EXIST";
    case USR_ERR_DISK_NOT_FORMAT:
        return "DISK_NOT_FORMAT";
    case USR_ERR_DISK_FORMAT_FAILED:
        return "DISK_FORMAT_FAILED";
    case USR_ERR_SDK_BEGIN:
        return "SDK_BEGIN";
    case USR_ERR_COMMAND_UNKNOWN:
        return "COMMAND_UNKNOWN";
    case USR_ERR_COMMAND_PARSE_FAILED:
        return "COMMAND_PARSE_FAILED";
    case USR_ERR_COMMAND_FORMAT_ERROR:
        return "COMMAND_FORMAT_ERROR";
    case USR_ERR_COMMAND_ASSEMBLY_FAILED:
        return "COMMAND_ASSEMBLY_FAILED";
    case USR_ERR_COMMAND_PAYLOAD_PARSE_ERROR:
        return "COMMAND_PAYLOAD_PARSE_ERROR";
    case USR_ERR_COMMAND_PAYLOAD_TYPE_ERROR:
        return "COMMAND_PAYLOAD_TYPE_ERROR";
    case USR_ERR_COMMAND_NOT_EXPECTED:
        return "COMMAND_NOT_EXPECTED";
    case USR_ERR_SDK_DISCONNECT:
        return "SDK_DISCONNECT";
    case USR_ERR_PACKET_HEAD_PARSE_ERROR:
        return "PACKET_HEAD_PARSE_ERROR";
    case USR_ERR_SDK_TYPE_ERROR:
        return "SDK_TYPE_ERROR";
    case USR_ERR_RECORD_BEGIN:
        return "RECORD_BEGIN";
    case USR_ERR_RECORD_NOT_EXIST:
        return "RECORD_NOT_EXIST";
    case USR_ERR_RECORD_AT_BEGIN_TIME:
        return "RECORD_AT_BEGIN_TIME";
    case USR_ERR_RECORD_AT_END_TIME:
        return "RECORD_AT_END_TIME";
    case USR_ERR_RECORD_AT_BLANK_SPACE:
        return "RECORD_AT_BLANK_SPACE";
    case USR_ERR_RECORD_STOP:
        return "RECORD_STOP";
    case USR_ERR_RECORD_FAILED:
        return "RECORD_FAILED";
    case USR_ERR_CAR_BUSY:
        return "CAR_BUSY";
    case USR_ERR_CAR_FAULT:
        return "CAR_FAULT";
    case USR_ERR_CAR_INVALID:
        return "CAR_INVALID";
    case USR_ERR_CAR_CHARGE_STATION_MANUAl:
        return "CAR_CHARGE_STATION_MANUAl";
    case USR_ERR_CAR_GET_STATION_FAILD:
        return "CAR_GET_STATION_FAILD";
    case USR_ERR_CAR_STATION_NOT_EXIST:
        return "CAR_STATION_NOT_EXIST";
    case USR_ERR_CAR_UNIMPLIMENT:
        return "CAR_UNIMPLIMENT";
    case USR_ERR_CAR_ROAD_MODULE_DISABLE:
        return "CAR_ROAD_MODULE_DISABLE";
    }
    return "Unknown";
}

const char* UnsStringRoadbaseType(unsigned short roadbaseType)
{
    switch (roadbaseType)
    {
    case ENM_ROADBASE_FIREDOOR:
        return "fire_door";
    case ENM_ROADBASE_PLATE_TRANSFER:
        return "plate_transfer";
    case ENM_ROADBASE_CHARGE_STATION:
        return "charge_station";
    case ENM_ROADBASE_FLOOD_VALVE:
        return "flood_valve";
    case ENM_ROADBASE_PLATE_TRANSFER_V1:
        return "plate_transfer_v1";
    case ENM_ROADBASE_BATTERY:
        return "battery";
    case ENM_ROADBASE_FIREDOOR_V1:
        return "fire_door_v1";
    case ENM_ROADBASE_LEVEL_SENSOR:
        return "level_sensor";
    }

    return "Unknown";
}

const char* UnsStringRoadbaseAction(unsigned short roadbaseAction, unsigned short roadbaseType)
{
    switch (roadbaseAction)
    {
    case ENM_ROADBASE_CLOSE:
        {
            if (ENM_ROADBASE_PLATE_TRANSFER == roadbaseType || ENM_ROADBASE_PLATE_TRANSFER_V1 == roadbaseType)
                return "curve";
            else if (ENM_ROADBASE_CHARGE_STATION == roadbaseType)
                return "stop_charge";
            else
                return "close";
        }
    case ENM_ROADBASE_OPEN:
        {
            if (ENM_ROADBASE_PLATE_TRANSFER == roadbaseType || ENM_ROADBASE_PLATE_TRANSFER_V1 == roadbaseType)
                return "straight";
            else if (ENM_ROADBASE_CHARGE_STATION == roadbaseType)
                return "start_charge";
            else
                return "open";
        }
    case ENM_ROADBASE_PREPARE_CHARGE:
        return "prepare_charge";
    case ENM_ROADBASE_RESET:
        return "reset";
    case ENM_ROADBASE_READ:
        return "read";
    }

    return "Unknown";
}

const char* UnsStringRoadbaseStatus(unsigned short status, unsigned short roadbaseType)
{
    switch (roadbaseType)
    {
    case ENM_ROADBASE_FIREDOOR:
    case ENM_ROADBASE_FIREDOOR_V1:
        {
            switch (status)
            {
            case ENM_FIRE_DOOR_STATUS_CLOSE:
                return "close";
            case ENM_FIRE_DOOR_STATUS_OPEN:
                return "open";
            case ENM_FIRE_DOOR_STATUS_CLOSE_OPEN:
                return "opening";
            case ENM_FIRE_DOOR_STATUS_OPEN_CLOSE:
                return "closeing";
            case ENM_FIRE_DOOR_STATUS_FAULT:
                return "fault";
            case ENM_FIRE_DOOR_STATUS_RUNNING:
                return "running";
            case ENM_FIRE_DOOR_STATUS_DISCONNECT:
                return "disconnect";
            }
            break;
        }
    case ENM_ROADBASE_PLATE_TRANSFER:
    case ENM_ROADBASE_PLATE_TRANSFER_V1:
        {
            switch (status)
            {
            case ENM_PLATE_TRANSFER_STATUS_STRAIGHT:
                return "straight";
            case ENM_PLATE_TRANSFER_STATUS_CURVE:
                return "curve";
            case ENM_PLATE_TRANSFER_STATUS_STRAIGHT_CHANGEING:
                return "straight_changeing";
            case ENM_PLATE_TRANSFER_STATUS_CURVE_CHANGEING:
                return "curve_changeing";
            case ENM_PLATE_TRANSFER_STATUS_FAULT:
                return "fault";
            case ENM_PLATE_TRANSFER_STATUS_RUNNING:
                return "running";
            case ENM_PLATE_TRANSFER_STATUS_DISCONNECT:
                return "disconnect";
            }
            break;
        }
    case ENM_ROADBASE_CHARGE_STATION:
        {
            switch (status)
            {
            case ENM_CHARGE_STATION_STATUS_FREE:
                return "free";
            case ENM_CHARGE_STATION_STATUS_TOUCH:
                return "touch";
            case ENM_CHARGE_STATION_STATUS_WAIT_RELAY_ON:
                return "wait_relay_on";
            case ENM_CHARGE_STATION_STATUS_CHARGING:
                return "charging";
            case ENM_CHARGE_STATION_STATUS_NEEDLE_OUT:
                return "needle_out";
            case ENM_CHARGE_STATION_STATUS_DISCONNECT:
                return "disconnect";
            }
            break;
        }
    case ENM_ROADBASE_FLOOD_VALVE:
        {
            switch (status)
            {
            case ENM_FLOOD_VALVE_STATUS_CLOSE:
                return "close";
            case ENM_FLOOD_VALVE_STATUS_OPEN:
                return "open";
            case ENM_FLOOD_VALVE_STATUS_FAULT:
                return "fault";
            case ENM_FLOOD_VALVE_STATUS_RUNNING:
                return "running";
            case ENM_FLOOD_VALVE_STATUS_DISCONNECT:
                return "disconnect";
            }
            break;
        }
    case ENM_ROADBASE_BATTERY:
        {
            switch (status)
            {
            case ENM_BATTERY_TRANSFER_STATUS_FAULT:
                return "fault";
            case ENM_BATTERY_TRANSFER_STATUS_ADDRESS:
                return "address_error";
            case ENM_BATTERY_TRANSFER_STATUS_OPERATION:
                return "operation";
            case ENM_BATTERY_TRANSFER_STATUS_DISCONNECT:
                return "disconnect";
            case ENM_BATTERY_TRANSFER_STATUS_NORMAL:
                return "normal";
            }
            break;
        }
    case ENM_ROADBASE_LEVEL_SENSOR:
        {
		switch (status)
		{
		case ENM_LEVEL_SENSOR_FAULT:
			return "fault";
		case ENM_LEVEL_SENSOR_ADDRESS:
			return "address_error";
		case ENM_LEVEL_SENSOR_OPERATION:
			return "operation";
		case ENM_LEVEL_SENSOR_DISCONNECT:
			return "disconnect";
		case ENM_LEVEL_SENSOR_USABLE:
			return "normal";
		}
		break;
        }
    }
	return "Unknown";
}

const char* UnsStringDvsType(char dvsType)
{
    switch (dvsType)
    {
    case ENM_DVS_ROBOT:
        return "robot";
    case ENM_DVS_CLIENT:
        return "client";
    case ENM_MEDIA_PRODUCER:
        return "media_producer";
    case ENM_MEDIA_CONSUMER:
        return "media_consumer";
    case ENM_S2E_PROXY:
        return "s2e_proxy";
    case ENM_DVS_IVAS:
        return "ivas";
    case ENM_DVS_SERVER:
        return "server";
    case ENM_DVS_SDK:
        return "sdk";
    }

    return "Unknown";
}
