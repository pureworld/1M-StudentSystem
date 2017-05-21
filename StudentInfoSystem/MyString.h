#pragma once

#include <iostream>

using namespace std;

class CMyString {
public:
    CMyString();
    CMyString(char *);
    CMyString(const CMyString &);
    ~CMyString(void);

    //初始化
    void InitString();
    //释放
    void ReleaseString();

    //设置字符串
    int SetStr(const char* strSrc);

    //格式化字符串，类似printf，结果保存在m_pStr
    //int Format(const char* strFormat, ...);

    //返回当前缓冲区大小
    inline int GetBufferSize() const { return m_nBuffLen; }

    //返回当前字符串长度
    inline int GetStrLen() const { return m_nStrLen; }

    //返回缓冲区，大小最少为nMinBuffLen
    char* GetBuffer(int nMinBuffLen);

    //获取当前m_pStr
    char* GetStr() const;

    //移除字符串首尾的空格（包括\r \n \t）
    void Strip();
    //根据字符集（字符串），移除字符串开始或结尾处的字符
    void LeftStrip(char *strStrip = "\x20\n");
    void RightStrip(char *strStrip = "\x20");
    //根据字符（字符串），移除字符串开始或结尾处的字符（若为字符串需完全匹配）
    void CharLeftStrip(char *cStrip);
    void CharRightStrip(char *cStrip);
    //向左或向右移动一位，即删除字符串第一个字符，或最后一个字符（不包括\0）
    void LeftMove();
    void RightMove();

    //判断字符串首尾是否是字符（字符串）开始或结尾（若为字符串需完全匹配）
    bool IsEndwith(const char* chSet = NULL) const;
    bool IsStartwith(const char* chSet = NULL) const;

    //查找当前CMyString中是否存在指定子字符串
    //若存在，返回第一个偏移位置
    //若不存在，返回-1
    int FindSubStr(char* strSub) const;
    
    //比较字符串
    int Cmp(const char* strSrc) const;
    int Cmp(const CMyString& objSrc) const;

    //连接strCat到当前CMyString
    bool Cat(const char* strCat);
    bool Cat(const CMyString& objCat);

    //转大小写
    void ToUpper();
    void ToLower();


    //重载一些操作符
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
