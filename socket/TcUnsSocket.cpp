#include "TcUnsSocket.h"
#include "USRError.h"
#include <stdio.h>

#if (defined(WIN32) || defined(_WIN32_WCE))
    #include <mstcpip.h>
    #include <WS2tcpip.h>
#else
    #include <netinet/tcp.h>
    #include <linux/sockios.h>
    #include <memory.h>
    #include <stdlib.h>
    #include <arpa/inet.h>
#endif
//#include "UnsOutputDebug.h"

TcUnsSocket::TcUnsSocket(const int p_nIPProtocol, const int p_nNetProtocol)
    : m_nSocket(-1)
    , m_nIPProtocol(p_nIPProtocol)
    , m_nNetProtocol(p_nNetProtocol)
    , m_nFamily(AF_INET)
    , m_nTimeOut(0)
    , m_nErrNo(0)
{
    memset(m_szErrMsg, 0, SOCKET_ERR_MSG_LEN);
    if (ENM_IP_V6 == p_nIPProtocol)
        m_nFamily = AF_INET6;
}
TcUnsSocket::~TcUnsSocket()
{
    //Close();
}

#if defined(__WIN32__) || defined(_WIN32)

#define WS_VERSION_CHOICE1 0x202/*MAKEWORD(2,2)*/
#define WS_VERSION_CHOICE2 0x101/*MAKEWORD(1,1)*/

static unsigned int g_nInitWinsock = 0;

int TcUnsSocket::InitWinsock()
{
    if (0 == g_nInitWinsock)
    {
        WSADATA	wsadata;
        if ((WSAStartup(WS_VERSION_CHOICE1, &wsadata) != 0) && ((WSAStartup(WS_VERSION_CHOICE2, &wsadata)) != 0))
            return USR_ERR_NETWORKIO_INIT_FAILED;
        if ((wsadata.wVersion != WS_VERSION_CHOICE1) && (wsadata.wVersion != WS_VERSION_CHOICE2))
        {
            WSACleanup();
            return USR_ERR_NETWORKIO_INIT_FAILED;
        }
    }
    g_nInitWinsock++;
    return USR_SUCCESS;
}

void TcUnsSocket::UninitWinsock()
{
    if (g_nInitWinsock > 0)
        g_nInitWinsock --;

    if (0 == g_nInitWinsock)
        WSACleanup();
}
#else
int TcUnsSocket::InitWinsock()
{
    return USR_SUCCESS;
}

void TcUnsSocket::UninitWinsock()
{
}
#endif

TcUnsSocket::TcUnsSocket(const TcUnsSocket& p_objSocket)
    : m_nSocket(p_objSocket.m_nSocket)
    , m_nIPProtocol(p_objSocket.m_nIPProtocol)
    , m_nNetProtocol(p_objSocket.m_nNetProtocol)
    , m_nFamily(p_objSocket.m_nFamily)
    , m_nTimeOut(0)
    , m_nErrNo(p_objSocket.m_nErrNo)
    , m_objTCPSocketDest(p_objSocket.m_objTCPSocketDest)
{
    memcpy(m_szErrMsg, p_objSocket.m_szErrMsg, SOCKET_ERR_MSG_LEN);
}
TcUnsSocket& TcUnsSocket::operator =(const TcUnsSocket& p_objSocket)
{
    if (this == &p_objSocket)
        return *this;

    m_nSocket			= p_objSocket.m_nSocket;
    m_nIPProtocol		= p_objSocket.m_nIPProtocol;
    m_nNetProtocol		= p_objSocket.m_nNetProtocol;
    m_nFamily			= p_objSocket.m_nFamily;
    m_nTimeOut			= p_objSocket.m_nTimeOut;
    m_nErrNo			= p_objSocket.m_nErrNo;
    m_objTCPSocketDest	= p_objSocket.m_objTCPSocketDest;
    memcpy(m_szErrMsg, p_objSocket.m_szErrMsg, SOCKET_ERR_MSG_LEN);

    return *this;
}

int TcUnsSocket::Open()
{
    m_nSocket = ::socket(m_nFamily, m_nNetProtocol, 0);
    if (-1 == m_nSocket)
    {
        HandErr("Open");
        return USR_ERR_NETWORKIO_OPEN_FAILED;
    }

    if (ENM_USE_TCP == m_nNetProtocol)
    {
        SetNoDelay();
        SetKeepAlive();
    }

    return USR_SUCCESS;
}
void TcUnsSocket::Close()
{
    if (-1 == m_nSocket)
        return ;
    //printf("%s line %d, %p socket=%d\n", __FUNCTION__, __LINE__, this, m_nSocket);
#if (defined(WIN32) || defined(_WIN32_WCE))
    ::closesocket(m_nSocket);
#else
    ::close(m_nSocket);
#endif
    //unsOutputDebug("TcUnsSocket Close:%d\n", m_nSocket);
    m_nSocket = -1;
    m_objTCPSocketDest.SetIP("");
    m_objTCPSocketDest.SetPORT(0);
}


int TcUnsSocket::Bind(const char* p_szIP, unsigned short p_nPort)
{
    if (NULL == p_szIP)
        return USR_ERR_SYS_NULL_POINTER;

    ADDRINFO hintsAddr, *destAddr;
    memset(&hintsAddr, 0, sizeof(hintsAddr));
    hintsAddr.ai_family = m_nFamily;
    hintsAddr.ai_socktype = m_nNetProtocol;
    hintsAddr.ai_flags = AI_PASSIVE;

    char szPort[16] = {0};
    sprintf(szPort, "%d", p_nPort);
    int nRet = ::getaddrinfo(p_szIP, szPort, &hintsAddr, &destAddr);
    if (nRet < 0)
    {
        HandErr("Bind getaddrinfo");
        return USR_ERR_NETWORKIO_GET_ADDRINFO_FAILED;
    }

    nRet = ::bind(m_nSocket, destAddr->ai_addr, destAddr->ai_addrlen);
    if (nRet < 0)
    {
        ::freeaddrinfo(destAddr);
        HandErr("Bind");
        return USR_ERR_NETWORKIO_BIND_FAILED;
    }
    ::freeaddrinfo(destAddr);

    return USR_SUCCESS;
}

int TcUnsSocket::Bind(const TcInetAddr& p_objTcInetAddr)
{
    return Bind(p_objTcInetAddr.GetIP(), p_objTcInetAddr.GetPORT());
}

int TcUnsSocket::Listen(int p_nBacklog)
{
    int nRet = ::listen(m_nSocket, p_nBacklog);
    if (nRet < 0)
    {
        HandErr("Listen");
        return USR_ERR_NETWORKIO_LISTEN_FAILED;
    }
    return USR_SUCCESS;
}

int TcUnsSocket::Accept(TcUnsSocket& p_objSocket, int p_nTimeOut)
{
    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(m_nSocket, &rset);

    struct timeval objTimeOut;
    struct timeval* pTimeOut = NULL;
    if (p_nTimeOut >= 0)
    {
        objTimeOut.tv_sec = p_nTimeOut / 1000;
        objTimeOut.tv_usec = (p_nTimeOut % 1000) * 1000;
        pTimeOut = &objTimeOut;
    }

    int nRet = ::select(m_nSocket + 1, &rset, NULL, NULL, pTimeOut);
    if (0 == nRet)
        return USR_ERR_NETWORKIO_ACCEPT_TIMEOUT;
    else if (0 > nRet)
    {
        HandErr("Accept select");
        return USR_ERR_NETWORKIO_ACCEPT_FAILED;
    }

    SOCKADDR_STORAGE objFrom;
    SOCKETLEN_T addrLen = sizeof(objFrom);
    int nRetSocket = ::accept(m_nSocket, (sockaddr*)&objFrom, &addrLen);
    if (nRetSocket < 0)
    {
        HandErr("Accept");
        return USR_ERR_NETWORKIO_ACCEPT_FAILED;
    }

    char szFromIP[64] = {0};
    char szFromPort[16] = {0};
    nRet = ::getnameinfo((sockaddr*)&objFrom, addrLen, szFromIP, sizeof(szFromIP), szFromPort, sizeof(szFromPort), NI_NUMERICHOST | NI_NUMERICSERV);
    if (nRet < 0)
    {
        HandErr("Accept getnameinfo");
        return USR_ERR_NETWORKIO_ACCEPT_FAILED;
    }

    p_objSocket.m_objTCPSocketDest.SetIP(szFromIP);
    p_objSocket.m_objTCPSocketDest.SetPORT(atoi(szFromPort));
    p_objSocket.m_objTCPSocketDest.SetIPProtoVer(m_nIPProtocol);
    p_objSocket.m_nSocket = nRetSocket;
    p_objSocket.m_nFamily = m_nFamily;

    return USR_SUCCESS;
}

int TcUnsSocket::Connect(const char* p_szDestIp, const int p_nPort)
{
    if (NULL == p_szDestIp)
        return USR_ERR_SYS_NULL_POINTER;

    ADDRINFO hintsAddr, *destAddr;
    memset(&hintsAddr, 0, sizeof(hintsAddr));
    hintsAddr.ai_family = m_nFamily;
    hintsAddr.ai_socktype = m_nNetProtocol;
    hintsAddr.ai_flags = AI_NUMERICHOST;

    char szPort[16] = {0};
    sprintf(szPort, "%d", p_nPort);
    int nRet = ::getaddrinfo(p_szDestIp, szPort, &hintsAddr, &destAddr);
    if (nRet < 0)
    {
        HandErr("Connect getaddrinfo");
        return USR_ERR_NETWORKIO_GET_ADDRINFO_FAILED;
    }

    m_objTCPSocketDest.SetIP(p_szDestIp);
    m_objTCPSocketDest.SetPORT(p_nPort);
    m_objTCPSocketDest.SetIPProtoVer(m_nIPProtocol);

    nRet = ::connect(m_nSocket, destAddr->ai_addr, destAddr->ai_addrlen);
    if (nRet < 0)
    {
        freeaddrinfo(destAddr);
        HandErr("Connect");
        return USR_ERR_NETWORKIO_CONNECT_FAILED;
    }

    freeaddrinfo(destAddr);
    return USR_SUCCESS;
}

int TcUnsSocket::Connect(const char* p_szDestIp, const int p_nPort, const int p_nTimeOut)
{
    if (NULL == p_szDestIp)
        return USR_ERR_SYS_NULL_POINTER;

    unsigned long argp = 1;
    int nRet = IOCTL_SOCKET(m_nSocket, FIONBIO, (unsigned long*)&argp);
    if (nRet < 0)
    {
        HandErr("Connect IOCTL_SOCKET");
        return USR_ERR_NETWORKIO_CONNECT_FAILED;
    }

    ADDRINFO hintsAddr, *destAddr;
    memset(&hintsAddr, 0, sizeof(hintsAddr));
    hintsAddr.ai_family = m_nFamily;
    hintsAddr.ai_socktype = m_nNetProtocol;
    hintsAddr.ai_flags = AI_NUMERICHOST;

    char szPort[16] = {0};
    sprintf(szPort, "%d", p_nPort);
    nRet = ::getaddrinfo(p_szDestIp, szPort, &hintsAddr, &destAddr);
    if (0 != nRet)
    {
        HandErr("Connect getaddrinfo");
        return USR_ERR_NETWORKIO_GET_ADDRINFO_FAILED;
    }

    m_objTCPSocketDest.SetIP(p_szDestIp);
    m_objTCPSocketDest.SetPORT(p_nPort);
    m_objTCPSocketDest.SetIPProtoVer(m_nIPProtocol);
    ::connect(m_nSocket, destAddr->ai_addr, destAddr->ai_addrlen);
    freeaddrinfo(destAddr);

    fd_set fds_read;
    FD_ZERO(&fds_read);
    FD_SET(m_nSocket, &fds_read);

    struct timeval stTimeout;
    struct timeval* pstTimeout = NULL;
    if (p_nTimeOut >= 0)
    {
        stTimeout.tv_sec = p_nTimeOut / 1000;
        stTimeout.tv_usec = (p_nTimeOut % 1000) * 1000;
        pstTimeout = &stTimeout;
    }

    /************************************************************************
    pstTimeout取值说明：
    NULL 等价于阻塞
    == 0 阻塞时间为0，select不做等待
    >  0 等待指定时间后返回
    ************************************************************************/
    /************************************************************************
    select返回值说明:
    <0，select错误
    =0，等待超时
    >0, 某些文件可读写
    ************************************************************************/
    /************************************************************************
    select参数：
    nfds: select监视的文件句柄数,视进程中打开的文件数而定，
    			一般设为要监视各文件中的最大文件号 +1
    ************************************************************************/
    nRet = ::select(m_nSocket + 1, NULL, &fds_read, NULL, pstTimeout);
    if (nRet == 0)
        return USR_ERR_NETWORKIO_CONNECT_TIMEOUT;
    else if (nRet < 0)
    {
        HandErr("Connect select");
        return USR_ERR_NETWORKIO_CONNECT_FAILED;
    }

    int error = 0;
    SOCKETLEN_T nLen = sizeof(error);
    nRet = getsockopt(m_nSocket, SOL_SOCKET, SO_ERROR, (char*)&error, &nLen);
    if (nRet < 0)
        return USR_ERR_NETWORKIO_CONNECT_FAILED;
    if (error != 0)
        return USR_ERR_NETWORKIO_CONNECT_FAILED;

    argp = 0;
    nRet = IOCTL_SOCKET(m_nSocket, FIONBIO, (unsigned long*)&argp);
    if (nRet < 0)
        return USR_ERR_NETWORKIO_CONNECT_FAILED;

    return USR_SUCCESS;
}

int TcUnsSocket::Connect(const TcInetAddr& p_objAddr)
{
    return Connect(p_objAddr.GetIP(), p_objAddr.GetPORT());
}
int TcUnsSocket::Connect(const TcInetAddr& p_objAddr, const int p_nTimeOut)
{
    return Connect(p_objAddr.GetIP(), p_objAddr.GetPORT(), p_nTimeOut);
}

int TcUnsSocket::SendTcp(const char* p_szData, const unsigned int p_nDataLen, int p_nTimeOut)
{
    if (p_nTimeOut < 0)
        p_nTimeOut = 0;

    //循环发送时，只需要设置一次
    if (p_nTimeOut != m_nTimeOut)
    {
        m_nTimeOut = p_nTimeOut;

        char* pszTimeOut = NULL;
        int nLen = 0;
#if (defined(WIN32) || defined(_WIN32_WCE))
        pszTimeOut = (char*)&m_nTimeOut;
        nLen = sizeof(m_nTimeOut);
#else
        struct timeval  objTimeval;
        objTimeval.tv_sec = m_nTimeOut / 1000;
        objTimeval.tv_usec = m_nTimeOut % 1000 * 1000;

        pszTimeOut = (char*)&objTimeval;
        nLen = sizeof(objTimeval);
#endif

        ::setsockopt(m_nSocket, SOL_SOCKET, SO_SNDTIMEO, pszTimeOut, nLen);
    }

    int nSendLen = ::send(m_nSocket, p_szData, p_nDataLen, SOCKET_FLAG);
    if (nSendLen <= 0)
    {
        HandErr("SendTcp");
        if (m_nErrNo == EAGAIN)
            return 0;

        return nSendLen;//USR_ERR_NETWORKIO_SEND_FAILED;
    }

    return nSendLen;
}
int TcUnsSocket::RecvTcp(char* p_szBuff, unsigned int p_nBuffLen, int p_nTimeOut, bool p_bUseEpoll)
{
    if (NULL == p_szBuff || 0 == p_nBuffLen)
        return USR_ERR_SYS_NULL_POINTER;

    if (!p_bUseEpoll)
    {
        fd_set rset;
        FD_ZERO(&rset);
        FD_SET(m_nSocket, &rset);

        struct timeval objTimeOut;
        struct timeval* pTimeOut = NULL;
        if (p_nTimeOut >= 0)
        {
            objTimeOut.tv_sec = p_nTimeOut / 1000;
            objTimeOut.tv_usec = (p_nTimeOut % 1000) * 1000;
            pTimeOut = &objTimeOut;
        }

        int nRet = ::select(m_nSocket + 1, &rset, NULL, NULL, pTimeOut);
        if (0 == nRet)
            return USR_ERR_NETWORKIO_RECV_TIMEOUT;
        else if (0 > nRet)
        {
            HandErr("RecvTcp select");
            return USR_ERR_NETWORKIO_RECV_FAILED;
        }
    }

    //::setsockopt(m_nSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&p_nTimeOut, sizeof(int));
    int nRecvLen = ::recv(m_nSocket, p_szBuff, p_nBuffLen, SOCKET_FLAG);
    if (nRecvLen <= 0)
    {
        HandErr("RecvTcp");
        return USR_ERR_NETWORKIO_RECV_FAILED;
    }

    return nRecvLen;
}

int TcUnsSocket::SendUdp(const char* p_pszData, unsigned int p_nDataLen, const TcInetAddr& p_objDestAddr)
{
    ADDRINFO hints, *destAddr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = m_nFamily;
    hints.ai_socktype = m_nNetProtocol;
    hints.ai_flags = AI_NUMERICHOST | AI_PASSIVE;

    char szPort[16] = {0};
    sprintf(szPort, "%d", p_objDestAddr.GetPORT());
    int nRet = ::getaddrinfo(p_objDestAddr.GetIP(), szPort, &hints, &destAddr);
    if (nRet < 0)
    {
        HandErr("SendUdp getaddrinfo");
        return USR_ERR_NETWORKIO_GET_ADDRINFO_FAILED;
    }

    int nSendLen = ::sendto(m_nSocket, p_pszData, p_nDataLen, SOCKET_FLAG, destAddr->ai_addr, destAddr->ai_addrlen);
    if (nSendLen <= 0)
    {
        freeaddrinfo(destAddr);
        HandErr("SendUdp");
        return USR_ERR_NETWORKIO_SEND_FAILED;
    }
    freeaddrinfo(destAddr);

    return nSendLen;
}

int TcUnsSocket::RecvUdp(char* p_pszBuf, unsigned int p_nBuflen, TcInetAddr &p_objFromTcInetAddr, int p_nTimeout)
{
    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(m_nSocket, &rset);

    struct timeval objTimeOut;
    struct timeval* pTimeOut = NULL;
    if (p_nTimeout >= 0)
    {
        objTimeOut.tv_sec = p_nTimeout / 1000;
        objTimeOut.tv_usec = (p_nTimeout % 1000) * 1000;
        pTimeOut = &objTimeOut;
    }

    int nRet = ::select(m_nSocket + 1, &rset, NULL, NULL, pTimeOut);
    if (0 == nRet)
        return USR_ERR_NETWORKIO_RECV_TIMEOUT;
    else if (nRet < 0)
    {
        HandErr("RecvUdp select");
        return USR_ERR_NETWORKIO_RECV_FAILED;
    }

    SOCKADDR_STORAGE fromAddr;
    SOCKETLEN_T addrLen = sizeof(fromAddr);

    int nRecvLen = ::recvfrom(m_nSocket, p_pszBuf, p_nBuflen, SOCKET_FLAG, (sockaddr*)&fromAddr, &addrLen);
    if (nRecvLen <= 0)
    {
        HandErr("RecvUdp recvfrom");
        return USR_ERR_NETWORKIO_RECV_FAILED;
    }

    char szFromIP[MAX_LENGTH_IP] = {0};
    char szPort[16] = {0};
    nRet = ::getnameinfo((sockaddr*)&fromAddr, addrLen, szFromIP, MAX_LENGTH_IP, szPort, 16, NI_NUMERICHOST | NI_NUMERICSERV);
    if (0 != nRet)
    {
        HandErr("RecvUdp getnameinfo");
        return USR_ERR_NETWORKIO_RECV_FAILED;
    }

    p_objFromTcInetAddr.SetIP(szFromIP);
    p_objFromTcInetAddr.SetPORT(atoi(szPort));
    p_objFromTcInetAddr.SetIPProtoVer(m_nIPProtocol);

    return nRecvLen;
}

int TcUnsSocket::SetNoDelay(int p_nFlag)
{
    if ( -1 == ::setsockopt(m_nSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&p_nFlag, sizeof(int)) )
    {
        HandErr("SetNoDelay");
        return USR_ERR_NETWORKIO_TCP_NODELAY_FAILED;
    }

    return USR_SUCCESS;
}

int TcUnsSocket::SetKeepAlive(int p_keepLive, int p_keepIdle, int p_keepIntvl, int p_keepCnt)
{
#if (defined(WIN32) || defined(_WIN32_WCE))
    if ( -1 == ::setsockopt(m_nSocket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&p_keepLive, sizeof(p_keepLive)))
    {
        HandErr("SetKeepAlive");
        return USR_ERR_NETWORKIO_KEEPLIVE_FAILED;
    }
    tcp_keepalive klive;
    klive.onoff = p_keepLive;
    klive.keepalivetime = p_keepIdle * 1000;		//毫秒
    klive.keepaliveinterval = p_keepIntvl * 1000;	//毫秒


    DWORD dwOpt = 1;
    if ( SOCKET_ERROR == ::WSAIoctl(m_nSocket, SIO_KEEPALIVE_VALS, &klive, sizeof(tcp_keepalive), NULL, 0, (LPDWORD)&dwOpt, NULL, NULL))
    {
        HandErr("SetKeepAlive WSAIoctl");
        return USR_ERR_NETWORKIO_KEEPLIVE_FAILED;
    }
#else
    if (   -1 == setsockopt(m_nSocket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&p_keepLive, sizeof(p_keepLive))
            || -1 == setsockopt(m_nSocket, SOL_TCP, TCP_KEEPIDLE, (const char*)&p_keepIdle, sizeof(p_keepIdle))
            || -1 == setsockopt(m_nSocket, SOL_TCP, TCP_KEEPINTVL, (const char*)&p_keepIntvl, sizeof(p_keepIntvl))
            || -1 == setsockopt(m_nSocket, SOL_TCP, TCP_KEEPCNT, (const char*)&p_keepCnt, sizeof(p_keepCnt)) )
    {
        HandErr("SetKeepAlive");
        return USR_ERR_NETWORKIO_KEEPLIVE_FAILED;
    }
#endif
    return USR_SUCCESS;
}

int TcUnsSocket::SetReuseAddr(bool p_bFlag)
{
    int nOptValue = p_bFlag ? 1 : 0;
    SOCKETLEN_T nLen = sizeof(nOptValue);
    int nRet = ::setsockopt( m_nSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nOptValue, nLen);
    if (nRet < 0)
        return USR_ERR_NETWORKIO_SET_REUSEADDR_FAILED;

    return USR_SUCCESS;
}

bool TcUnsSocket::SetNonBlocking(bool flag)
{
    unsigned long argp = 0;
    if (flag)
    {
        argp = 1; //设置为非阻塞模式
    }
    int nRet = IOCTL_SOCKET(m_nSocket, FIONBIO, (unsigned long*)&argp);
    if (nRet == -1)
        return false;

    return true;
}

bool TcUnsSocket::SetSendBuffSize(int sendBuffSize)
{
    int nRet = ::setsockopt(m_nSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&sendBuffSize, sizeof(int));
    if (nRet < 0)
    {
        HandErr("SetSendBuf");
        return false;
    }

    return true;
}

int TcUnsSocket::GetSendBuffSize()
{
    int nSendBuffSize = -1;
    SOCKETLEN_T len = sizeof(nSendBuffSize);
    int nRet = ::getsockopt(m_nSocket, SOL_SOCKET, SO_SNDBUF, (char*)&nSendBuffSize, &len);
    if (nRet < 0)
    {
        HandErr("SetSendBuf");
        return nRet;
    }
    return nSendBuffSize;
}

bool TcUnsSocket::SetRecvBuffSize(int recvBuffSize)
{
    int nRet = ::setsockopt(m_nSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&recvBuffSize, sizeof(int));
    if (nRet != 0)
    {
        HandErr("SetRecvBuff");
        return false;
    }

    return true;
}

int TcUnsSocket::GetRecvBuffSize()
{
    int nRecvBuffSize = -1;
    SOCKETLEN_T len = sizeof(int);
    int nRet = ::getsockopt(m_nSocket, SOL_SOCKET, SO_RCVBUF, (char*)&nRecvBuffSize, &len);
    if (nRet < 0)
    {
        HandErr("SetSendBuf");
        return nRet;
    }
    return nRecvBuffSize;
}

SOCKETHANDLE  TcUnsSocket::GetSocket()
{
    return m_nSocket;
}

TcInetAddr TcUnsSocket::GetSocketAddr()
{
    TcInetAddr localAddr;

    if (m_nFamily == AF_INET)
    {
        struct sockaddr_in addr;
        SOCKETLEN_T	namelen = sizeof(addr);

        int nRet = ::getsockname(m_nSocket, (struct sockaddr*)&addr, &namelen);
        if (nRet < 0)
        {
            HandErr("getsockname");
            return localAddr;
        }

        localAddr.SetIP(inet_ntoa(addr.sin_addr));
        localAddr.SetPORT(ntohs(addr.sin_port));
        localAddr.SetIPProtoVer(m_nIPProtocol);

        return localAddr;
    }
    else
    {
        struct sockaddr_in6 addr;
        SOCKETLEN_T namelen = sizeof(addr);

        int nRet = ::getsockname(m_nSocket, (struct sockaddr*)&addr, &namelen);
        if (nRet < 0)
        {
            HandErr("getsockname");
            return localAddr;
        }

        char szFromIP[128] = {0};
        char szFromPort[20] = {0};
        nRet = ::getnameinfo((sockaddr*)&addr, sizeof(sockaddr_in6), szFromIP, sizeof(szFromIP), szFromPort, sizeof(szFromPort), NI_NUMERICHOST | NI_NUMERICSERV);
        if (nRet != 0)
        {
            HandErr("getnameinfo");
            return localAddr;
        }

        localAddr.SetIP(szFromIP);
        localAddr.SetPORT(atoi(szFromPort));
        localAddr.SetIPProtoVer(m_nIPProtocol);
    }

    return localAddr;
}

const TcInetAddr& TcUnsSocket::GetTCPDestAddress()const
{
    return m_objTCPSocketDest;
}

void TcUnsSocket::HandErr(const char* description)
{
    m_nErrNo = getLastError();
    char* pszErrMsg = strerror(m_nErrNo);
    int nMsgLen = strlen(pszErrMsg);
    int nCpyLen = (nMsgLen > SOCKET_ERR_MSG_LEN - 1) ? (SOCKET_ERR_MSG_LEN - 1) : nMsgLen;
    strncpy(m_szErrMsg, pszErrMsg, nCpyLen);
    m_szErrMsg[nCpyLen] = '\0';
    //printf("TcUnsSocket=%d, %s: %s\n", m_nSocket, description, m_szErrMsg);
}

int TcUnsSocket::GetErrorNo()
{
    return m_nErrNo;
}
char* TcUnsSocket::GetStrError()
{
    return m_szErrMsg;
}

