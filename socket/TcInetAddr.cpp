#include "TcInetAddr.h"
#include <string.h>

TcInetAddr::TcInetAddr()
{
    memset(m_szHostIP, 0, MAX_LENGTH_IP);
    m_nPORT = 0;
    m_nIPProtocol = ENM_IP_V4;
}

TcInetAddr::~TcInetAddr()
{
}

TcInetAddr::TcInetAddr (const TcInetAddr &p_objTcInetAddr)
{
    strcpy(m_szHostIP, p_objTcInetAddr.m_szHostIP);
    m_nPORT = p_objTcInetAddr.m_nPORT;
    m_nIPProtocol = p_objTcInetAddr.m_nIPProtocol;
}

TcInetAddr & TcInetAddr::operator =(const TcInetAddr & p_objTcInetAddr)
{
    if (this == &p_objTcInetAddr)
        return *this;

    strcpy(m_szHostIP, p_objTcInetAddr.m_szHostIP);
    m_nPORT = p_objTcInetAddr.m_nPORT;
    m_nIPProtocol = p_objTcInetAddr.m_nIPProtocol;

    return *this;
}

bool TcInetAddr::SetIP(const char* p_pszIP)
{
    if (p_pszIP == NULL)
        return false;
    int nLen = strlen(p_pszIP);
    if (nLen > MAX_LENGTH_IP)
        return false;

    strcpy(m_szHostIP, p_pszIP);
    return true;
}

const char* TcInetAddr::GetIP() const
{
    return m_szHostIP;
}

void TcInetAddr::SetPORT(unsigned short p_nPORT)
{
    m_nPORT = p_nPORT;
}

const unsigned short TcInetAddr::GetPORT() const
{
    return m_nPORT;
}

void TcInetAddr::SetIPProtoVer(const int p_nIPProtoVer)
{
    m_nIPProtocol = p_nIPProtoVer;
}

const int TcInetAddr::GetIPProtoVer()  const
{
    return m_nIPProtocol;
}

bool TcInetAddr::operator ==(TcInetAddr & p_objTcInetAddr)
{
    //IP比较忽略大小写
#if (defined(WIN32) || defined(_WIN32_WCE))
#ifdef _WIN32_WCE
    if (_stricmp(m_szHostIP, p_objTcInetAddr.GetIP()) == 0 &&
#else
    if (_stricmp(m_szHostIP, p_objTcInetAddr.GetIP()) == 0 &&
#endif
#else
    if (strcasecmp(m_szHostIP, p_objTcInetAddr.GetIP()) == 0 &&
#endif
            m_nPORT == p_objTcInetAddr.GetPORT() &&
            m_nIPProtocol == p_objTcInetAddr.GetIPProtoVer())
        return true;

    return false;
}
