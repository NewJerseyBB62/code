#ifndef _USR_SOCKET_CONST_H_
#define _USR_SOCKET_CONST_H_

#if (defined(_WIN32) || defined(_WIN32_WCE))
    #include <WinSock2.h>

    #define SOCKETHANDLE							SOCKET
    #define getLastError()							GetLastError()
    #define IOCTL_SOCKET							ioctlsocket
    #define SOCKET_FLAG								0
    typedef	int										SOCKETLEN_T;

#else
    #include <sys/socket.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <errno.h>

    #define SOCKETHANDLE							int
    #define getLastError()							errno
    #define IOCTL_SOCKET							ioctl
    #define SOCKET_FLAG								MSG_NOSIGNAL

    typedef struct addrinfo							ADDRINFO;
    typedef struct sockaddr_storage					SOCKADDR_STORAGE;
    typedef socklen_t								SOCKETLEN_T;
    typedef struct sockaddr_in						SOCKADDR_IN;
#endif //end WIN32

#include "UsrCommonConst.h"

enum IP_PROTOCOL
{
    ENM_IP_V4	= 1,
    ENM_IP_V6	= 2
};

enum NET_PROTOCOL
{
    ENM_USE_TCP	= SOCK_STREAM,
    ENM_USE_UDP = SOCK_DGRAM
};

#define SOCKET_ERR_MSG_LEN			128

#endif //_USR_SOCKET_CONST_H_