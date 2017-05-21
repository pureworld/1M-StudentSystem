#include "MyString.h"
#include <cassert>
#include <cstdarg>

CMyString::CMyString() {
    InitString();
    SetStr("");
}

CMyString::CMyString(char* pStr) {
    InitString();
    SetStr(pStr);
}

CMyString::CMyString(const CMyString &objStr) {
    InitString();
    SetStr(objStr.GetStr());
}

CMyString::~CMyString() {
    ReleaseString();
}

void CMyString::InitString() {
    m_pStr = new char[0x20];
    m_nBuffLen = 0x20;
    m_nStrLen = 0;
}

void CMyString::ReleaseString() {
    if (m_pStr != NULL) {
        delete []m_pStr;
        m_pStr = NULL;
    }
    m_nBuffLen = 0;
    m_nStrLen = 0;
}

int CMyString::SetStr(const char* strSrc) {
    if (strSrc == NULL) {
        cout << "error : try to set to NULL!" << endl;
        return -1;
    }

    assert(strSrc != NULL);

    if (strlen(strSrc) + 1 > m_nBuffLen) {
        GetBuffer(strlen(strSrc) + 1);
    }

    strcpy(m_pStr, strSrc);
    return m_nStrLen = strlen(strSrc);
}

char* CMyString::GetBuffer(int nMinBuffLen) {
    if (nMinBuffLen <= m_nBuffLen) {
        return m_pStr;
    }
    char* newBuff = new char[nMinBuffLen];
    memset(newBuff, 0, nMinBuffLen);
    memcpy(newBuff, m_pStr, m_nBuffLen);
    delete []m_pStr;
    m_pStr = newBuff;
    m_nBuffLen = nMinBuffLen;
    return m_pStr;
}

char* CMyString::GetStr() const {
    return m_pStr;
}

void CMyString::Strip() {
    LeftStrip(" \r\n\t");
    RightStrip(" \r\n\t");
}

void CMyString::LeftStrip(char *strStrip/* ="20" */) {
    for (int i = 0; m_pStr[i] != '\0'; i++) {
        if (strchr(strStrip, m_pStr[i]) != NULL) {
            LeftMove();
            i--;
        } else {
            break;
        }
    }
}

void CMyString::RightStrip(char *strStrip/* ="20" */) {
    strrev(m_pStr);
    LeftStrip(strStrip);
    strrev(m_pStr);
}

void CMyString::CharLeftStrip(char *cStrip) {
    while (IsStartwith(cStrip)) {
        LeftMove();
    }
}

void CMyString::CharRightStrip(char *cStrip) {
    while (IsStartwith(cStrip)) {
        RightMove();
    }
}

void CMyString::LeftMove() {
    strrev(m_pStr);
    RightMove();
    strrev(m_pStr);
}

void CMyString::RightMove() {
    m_pStr[m_nStrLen-1] = '\0';
    m_nStrLen--;
}

bool CMyString::IsEndwith(const char* chSet /* = NULL */) const {
    char *strTmp = (char*)malloc(strlen(chSet) + 1);
    strcpy(strTmp, chSet);
    if (strncmp(strrev(m_pStr), strrev(strTmp), strlen(chSet)) == 0) {
        strrev(m_pStr);
        return true;
    } else {
        strrev(m_pStr);
        return false;
    }
}

bool CMyString::IsStartwith(const char* chSet /* = NULL */) const {
    return strncmp(m_pStr, chSet, strlen(chSet)) == 0;
}

int CMyString::FindSubStr(char* strSub) const {
    if (strstr(m_pStr, strSub) == NULL) {
        return 0;
    }
    return strstr(m_pStr, strSub) - m_pStr;
}

int CMyString::Cmp(const char* strSrc) const {
    return strcmp(m_pStr, strSrc);
}

int CMyString::Cmp(const CMyString &strCmp) const {
    return strcmp(m_pStr, strCmp.GetStr());
}

bool CMyString::Cat(const char* strCat) {
    if (strCat == NULL) {
        return false;
    }
    if (m_nStrLen + 1 + strlen(strCat) > m_nBuffLen) {
        GetBuffer(m_nStrLen + 1 + strlen(strCat));
    }
    strcat(m_pStr, strCat);
    return true;
}

bool CMyString::Cat(const CMyString &strCat) {
    if (m_nStrLen + 1 + strCat.GetStrLen() > m_nBuffLen) {
        GetBuffer(m_nStrLen + 1 + strCat.GetStrLen());
    }
    strcat(m_pStr, strCat.GetStr());
    return true;
}

void CMyString::ToUpper() {
    strupr(m_pStr);
}

void CMyString::ToLower() {
    strlwr(m_pStr);
}

CMyString& CMyString::operator=(char* pStr) {
    SetStr(pStr);
    return *this;
}
CMyString& CMyString::operator=(CMyString& myStr) {
    SetStr(myStr.GetStr());
    return *this;
}

CMyString CMyString::operator+(char* pStr) {
    CMyString tmp(*this);
    tmp.Cat(pStr);
    return tmp;
}
CMyString CMyString::operator+(CMyString& myStr) {
    CMyString tmp(*this);
    tmp.Cat(myStr);
    return tmp;
}

CMyString operator+(char* pStr, CMyString& myStr) {
    CMyString tmp(pStr);
    tmp.Cat(myStr);
    return tmp;
}

CMyString& CMyString::operator+=(char* pStr) {
    Cat(pStr);
    return *this;
}

CMyString& CMyString::operator+=(CMyString& myStr) {
    Cat(myStr);
    return *this;
}

bool CMyString::operator==(char* pStr) {
    if (pStr == NULL) {
        return false;
    }
    return strcmp(m_pStr, pStr) == 0;
}
bool CMyString::operator==(CMyString& myStr) {
    return strcmp(m_pStr, myStr.GetStr()) == 0;
}

bool CMyString::operator!=(char* pStr) {
    return !(*this == pStr);
}
bool CMyString::operator!=(CMyString& myStr) {
    return !(*this == myStr);
}

bool CMyString::operator<(char*pStr) {
    if (pStr == NULL) {
        return false;
    }
    return strcmp(m_pStr, pStr) < 0 ? true : false;
}
bool CMyString::operator<(CMyString&myStr) {
    return strcmp(m_pStr, myStr.GetStr()) < 0 ? true : false;
}

bool CMyString::operator>(char*pStr) {
    if (pStr == NULL) {
        return false;
    }
    return strcmp(m_pStr, pStr) > 0 ? true : false;
}
bool CMyString::operator>(CMyString&myStr) {
    return strcmp(m_pStr, myStr.GetStr()) > 0 ? true : false;
}

char& CMyString::operator[](int nIndex) {
    return m_pStr[nIndex];
}

ostream& operator<<(ostream&out, const CMyString &myStr) {
    out << myStr.GetStr();
    return out;
}

istream& operator>>(istream&in, CMyString &myStr) {
    char buf[100000];
    in >> buf;
    myStr.SetStr(buf);
    return in;
}
