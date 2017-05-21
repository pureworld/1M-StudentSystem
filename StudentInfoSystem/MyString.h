#pragma once

#include <iostream>

using namespace std;

class CMyString {
public:
    CMyString();
    CMyString(char *);
    CMyString(const CMyString &);
    ~CMyString(void);

    //��ʼ��
    void InitString();
    //�ͷ�
    void ReleaseString();

    //�����ַ���
    int SetStr(const char* strSrc);

    //��ʽ���ַ���������printf�����������m_pStr
    //int Format(const char* strFormat, ...);

    //���ص�ǰ��������С
    inline int GetBufferSize() const { return m_nBuffLen; }

    //���ص�ǰ�ַ�������
    inline int GetStrLen() const { return m_nStrLen; }

    //���ػ���������С����ΪnMinBuffLen
    char* GetBuffer(int nMinBuffLen);

    //��ȡ��ǰm_pStr
    char* GetStr() const;

    //�Ƴ��ַ�����β�Ŀո񣨰���\r \n \t��
    void Strip();
    //�����ַ������ַ��������Ƴ��ַ�����ʼ���β�����ַ�
    void LeftStrip(char *strStrip = "\x20\n");
    void RightStrip(char *strStrip = "\x20");
    //�����ַ����ַ��������Ƴ��ַ�����ʼ���β�����ַ�����Ϊ�ַ�������ȫƥ�䣩
    void CharLeftStrip(char *cStrip);
    void CharRightStrip(char *cStrip);
    //����������ƶ�һλ����ɾ���ַ�����һ���ַ��������һ���ַ���������\0��
    void LeftMove();
    void RightMove();

    //�ж��ַ�����β�Ƿ����ַ����ַ�������ʼ���β����Ϊ�ַ�������ȫƥ�䣩
    bool IsEndwith(const char* chSet = NULL) const;
    bool IsStartwith(const char* chSet = NULL) const;

    //���ҵ�ǰCMyString���Ƿ����ָ�����ַ���
    //�����ڣ����ص�һ��ƫ��λ��
    //�������ڣ�����-1
    int FindSubStr(char* strSub) const;
    
    //�Ƚ��ַ���
    int Cmp(const char* strSrc) const;
    int Cmp(const CMyString& objSrc) const;

    //����strCat����ǰCMyString
    bool Cat(const char* strCat);
    bool Cat(const CMyString& objCat);

    //ת��Сд
    void ToUpper();
    void ToLower();


    //����һЩ������
    CMyString& operator=(char*);
    CMyString& operator=(CMyString&);

    CMyString operator+(char*);
    CMyString operator+(CMyString&);
    friend CMyString operator+(char*, CMyString&);

    CMyString& operator+=(char*);
    CMyString& operator+=(CMyString&);

    bool operator==(char*);
    bool operator==(CMyString&);

    bool operator!=(char*);
    bool operator!=(CMyString&);

    bool operator<(char*);
    bool operator<(CMyString&);

    bool operator>(char*);
    bool operator>(CMyString&);

    char& operator[](int nIndex);

    friend ostream& operator<<(ostream& out, const CMyString&);
    friend istream& operator>>(istream& in, CMyString&);
private:
    int m_nBuffLen;
    int m_nStrLen;
    char* m_pStr;
};
