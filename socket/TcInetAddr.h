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
    **������
    *		����IP��ַ
    **���룺
    *	   p_pszIP��IP��ַ,��ʽ�磺xxx.xxx.xxx.xxx��
    **����ֵ��
    *	  true�� �ɹ�
    *	  false��ʧ��
    **���ܣ�
    *	  ��p_pszIP���Ϸ���IP������false
    ************************************************************************/
    bool SetIP(const char* p_pszIP);

    /************************************************************************
    **������
    *		��ȡ����Ʊ�ʾ��IP��ַ
    **����ֵ��
    *		��ʽ�磺xxx.xxx.xxx.xxx�ĵ��ʮ����IP��ַ�ַ���
    ************************************************************************/
    const char* GetIP() const;

    void SetPORT(const unsigned short p_nPORT);
    const unsigned short GetPORT()  const;

    /************************************************************************
    ** ������
    *		����IPЭ������
    **���룺
    *		p_nIPProtoVer��IPЭ������   IPV4����IPV6
    ************************************************************************/
    void SetIPProtoVer(const int p_nIPProtoVer);
    const int GetIPProtoVer()  const;

    /************************************************************************
    **������
    *		�Ƚ�������ַ�����Ƿ����
    **���룺
    *		TcInetAddr�����
    ************************************************************************/
    bool operator ==(TcInetAddr &) ;

private:

    char			m_szHostIP[MAX_LENGTH_IP];		//IP��ַ�������ֽ�˳��

    unsigned short	m_nPORT;							//�˿ں�

    int				m_nIPProtocol;						//IP�汾��IPv4��IPv6
};

#endif //_TC_INET_ADDR_H_
