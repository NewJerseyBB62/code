#ifndef _TC_INET_ADDR_H_
#define _TC_INET_ADDR_H_

#include "SocketConst.h"

class TcInetAddr
{
public:
    TcInetAddr();
    ~TcInetAddr();

    TcInetAddr (const TcInetAddr& p_objTcInetAddr);
    TcInetAddr & operator =(const TcInetAddr& p_objTcInetAddr) ;

public:

    /************************************************************************
    **概述：
    *		设置IP地址
    **输入：
    *	   p_pszIP：IP地址,格式如：xxx.xxx.xxx.xxx。
    **返回值：
    *	  true： 成功
    *	  false：失败
    **功能：
    *	  若p_pszIP不合法的IP，返回false
    ************************************************************************/
    bool SetIP(const char* p_pszIP);

    /************************************************************************
    **概述：
    *		获取点分制表示的IP地址
    **返回值：
    *		格式如：xxx.xxx.xxx.xxx的点分十进制IP地址字符串
    ************************************************************************/
    const char* GetIP() const;

    void SetPORT(const unsigned short p_nPORT);
    const unsigned short GetPORT()  const;

    /************************************************************************
    ** 概述：
    *		设置IP协议类型
    **输入：
    *		p_nIPProtoVer：IP协议类型   IPV4或者IPV6
    ************************************************************************/
    void SetIPProtoVer(const int p_nIPProtoVer);
    const int GetIPProtoVer()  const;

    /************************************************************************
    **概述：
    *		比较两个地址对象是否相等
    **输入：
    *		TcInetAddr类对象
    ************************************************************************/
    bool operator ==(TcInetAddr &) ;

private:

    char			m_szHostIP[MAX_LENGTH_IP];		//IP地址（主机字节顺序）

    unsigned short	m_nPORT;							//端口号

    int				m_nIPProtocol;						//IP版本，IPv4或IPv6
};

#endif //_TC_INET_ADDR_H_
