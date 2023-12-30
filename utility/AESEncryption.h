#pragma once
class AESEncryption
{
public:
    AESEncryption(const char* key);
    virtual ~AESEncryption();

    /**
     * ����
     * @param in �����������
     * @param inlen ����������ݳ���
     * @param outlen ������ܺ����ݳ���
     * @param fill �������16�����������Ƿ���0ֵ��ȫ�� true:��0ֵ��ȫ, false:��xor���ܶ��������
     * @return ���ؼ��ܺ�����
     */
    void* Encrypt(void* in, int inlen, int& outlen, bool fill = false);

    /**
     * ����
     * @param in �����������
     * @param inlen ����������ݳ���
     * @param outlen ������ܺ����ݳ���
     * @return ���ؽ��ܺ�����
     */
    void* Decrypt(void* in, int inlen, int& outlen);

private:
    // S �б任
    unsigned char Sbox[256];
    // �� S �б任
    unsigned char InvSbox[256];
    // ��Կ
    unsigned char w[11][4][4];

private:
    /**
     * ��Կ��չ���� - ��128λ��Կ������չ�õ� w[11][4][4]
     * @param key 16λ��Կ
     */
    void KeyExpansion(const char* key);

    /**
     * ���ӽ���
     * @param in �ӽ�����������
     * @param len �ӽ����������ݳ���
     */
    void Xor(unsigned char* in, int len);

    /**
     * ���ܣ�����������С������16�ֽ�
     * @param data ��������
     */
    void Encrypt(unsigned char* data);

    /**
     * ���ܣ����������Ҳ������16�ֽ�
     * @param data ��������
     */
    void Decrypt(unsigned char* data);

    /**
     * S �б任
     * @param state �任����
     */
    void SubBytes(unsigned char state[][4]);

    /**
     * �б任
     * @param state �任����
     */
    void ShiftRows(unsigned char state[][4]);

    /**
     * �б任
     * @param state �任����
     */
    void MixColumns(unsigned char state[][4]);

    /**
     * ����չ��Կ�����
     * @param state �任����
     */
    void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);

    /**
     * �� S �б任
     * @param state �任����
     */
    void InvSubBytes(unsigned char state[][4]);

    /**
     * ���б任
     * @param state �任����
     */
    void InvShiftRows(unsigned char state[][4]);

    /**
     * ���б任
     * @param state �任����
     */
    void InvMixColumns(unsigned char state[][4]);
};

