#pragma once
#include "MyString.h"
class CRecordInfo
{
public:
    CRecordInfo(void);
    CRecordInfo(int stuId, int courseId, int score);
    ~CRecordInfo(void);

    bool operator==(CRecordInfo);

    int GetStuId() {
        return m_nStuId;
    }
    int GetCourseId() {
        return m_nCourseId;
    }
    int GetScore() {
        return m_nScore;
    }
    void Set(int a, int b, int c) {
        m_nStuId = a;
        m_nCourseId = b;
        m_nScore = c;
    }

    friend ostream& operator<<(ostream&, CRecordInfo&);
    friend istream& operator>>(istream&, CRecordInfo&);
private:
    int m_nStuId;
    int m_nCourseId;
    int m_nScore;
};

