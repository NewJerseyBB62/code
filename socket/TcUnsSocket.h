#ifndef _TC_UNS_SOCKET_H_
#define _TC_UNS_SOCKET_H_

#include "TcInetAddr.h"
#include <memory>

class TcUnsSocket
{
public:
    TcUnsSocket(const int p_nIPProtocol = ENM_IP_V4, const int p_nNetProtocol = ENM_USE_TCP);
    virtual ~TcUnsSocket();

    static int InitWinsock();
    static void UninitWinsock();

    TcUnsSocket(const TcUnsSocket& p_objSocket);
    TcUnsSocket& operator =(const TcUnsSocket& p_objSocket);

    int Open();
    void Close();

    int Bind(const char* p_szIP, unsigned short p_nPort);
    int Bind(const TcInetAddr& p_objTcInetAddr);

    /************************************************************************
    说明：处于监听状态的套接字sockfd将维护一个客户连接请求队列，该队列最多容纳backlog个用户请求
    ************************************************************************/
    int Listen(int p_nBacklog = 10);

    /************************************************************************
    说明：p_nTimeOut，超时时间，单位毫秒，取值小于等于0时，阻塞
    ************************************************************************/
    int Accept(TcUnsSocket& p_objSocket, int p_nTimeOut);

    /************************************************************************
    概  述：
    		设置NoDelay模式
    输  入：
    		p_nFlag，控制标记，值为1时，表示禁用，值为0时，表示不禁用。默认禁用
    返回值：
    		成功返回USR_SUCCESS, 失败返回错误码
    说  明：
    		禁用TCP协议中的组装大包再发送，仅在TCP模式下才生效
    ************************************************************************/
    int SetNoDelay(int p_nFlag = 1);

    /************************************************************************
    概  述：
    		设置TCP自动保活模式
    输  入：
    		p_keepLive，控制标记. 值为1时，表示开启，值为0时，表示关闭。默认开启
    		p_keepIdle，开始首次KeepAlive探测前的TCP空闭时间,单位秒
    		p_keepIntvl，两次KeepAlive探测间的时间间隔，单位秒
    		p_keepCnt，判定断开前的KeepAlive探测次数
    返回值：
    		成功返回USR_SUCCESS, 失败返回错误码
    说  明：
    		仅在TCP模式下才生效
    ************************************************************************/
    int SetKeepAlive(int p_keepLive = 1, int p_keepIdle = 5, int p_keepIntvl = 2, int p_keepCnt = 2);

    /************************************************************************
    概述：
    	设置地址重用
    输入：
    	p_bFlag,重用标记
    说明：
    	在bind之前设置重用
    ************************************************************************/
    int SetReuseAddr(bool p_bFlag);

    SOCKETHANDLE  GetSocket();

    TcInetAddr GetSocketAddr();
    const TcInetAddr& GetTCPDestAddress()const;

    /************************************************************************
    说明：p_nTimeOut，超时时间，单位毫秒，取值小于等于0时，阻塞
    ************************************************************************/
    int Connect(const char* p_szDestIp, const int p_nPort);
    int Connect(const char* p_szDestIp, const int p_nPort, const int p_nTimeOut);
    int Connect(const TcInetAddr& p_objAddr);
    int Connect(const TcInetAddr& p_objAddr, const int p_nTimeOut);

    /************************************************************************
    返回值：成功返回发送长度，失败返回错误码
    说  明：p_nTimeOut，超时时间，单位毫秒，取值小于等于0时，阻塞
    ************************************************************************/
    int SendTcp(const char* p_szData, const unsigned int p_nDataLen, int p_nTimeOut);

    /************************************************************************
    返回值：成功返回接收长度，失败返回错误码
    说  明：p_nTimeOut，超时时间，单位毫秒，取值小于等于0时，阻塞
    ************************************************************************/
    int RecvTcp(char* p_szBuff, unsigned int p_nBuffLen, int p_nTimeOut = 0, bool p_bUseEpoll = false);

    int SendUdp(const char* p_pszData, unsigned int p_nDataLen, const TcInetAddr& p_objDestAddr);

    int RecvUdp(char* p_pszBuf, unsigned int p_nBuflen, TcInetAddr &p_objFromTcInetAddr, int p_nTimeout = 0);

    bool SetNonBlocking(bool flag);

    bool SetSendBuffSize(int p_nSize);
    int GetSendBuffSize();

    bool SetRecvBuffSize(int recvBuffSize);
    int GetRecvBuffSize();

    int GetErrorNo();
    char* GetStrError();
private:
    void HandErr(const char* description);

private:
    SOCKETHANDLE		m_nSocket;				//socket句柄
    int					m_nIPProtocol;			//IP版本，IPv4或IPv6
    int					m_nNetProtocol;			//TCP 或 UDP
    int					m_nFamily;				//协议族

    int					m_nTimeOut;				//超时时间
    int					m_nErrNo;				//socket错误码
    char				m_szErrMsg[SOCKET_ERR_MSG_LEN];	//socket错误描述

    TcInetAddr			m_objTCPSocketDest;
};

#endif //_TC_UNS_SOCKET_H_