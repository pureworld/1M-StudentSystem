#pragma once
#include "MyString.h"
class CCourseInfo
{
public:
    CCourseInfo(void);
    CCourseInfo(int, CMyString);
    ~CCourseInfo(void);

    int GetId() {
        return m_nId;
    }
    CMyString GetName() {
        return m_CourseName;
    }

    bool operator==(CCourseInfo);

    friend ostream& operator<<(ostream&, CCourseInfo&);
private:
    int m_nId;
    CMyString m_CourseName;
};

