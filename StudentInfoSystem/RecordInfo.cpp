#include "RecordInfo.h"


CRecordInfo::CRecordInfo(void)
{
}

CRecordInfo::CRecordInfo(int stuId, int courseId, int score) {
    m_nStuId = stuId;
    m_nCourseId = courseId;
    m_nScore = score;
}

CRecordInfo::~CRecordInfo(void)
{
}

bool CRecordInfo::operator==(CRecordInfo obj) {
    return ((m_nStuId == obj.m_nStuId)
        && (m_nCourseId == obj.m_nCourseId)
        && (m_nScore == obj.m_nScore));
}

ostream& operator<<(ostream& out, CRecordInfo& obj) {
    out << obj.m_nStuId << endl;
    out << obj.m_nCourseId << endl;
    out << obj.m_nScore;
    return out;
}

istream& operator>>(istream& in, CRecordInfo& obj) {
    in >> obj.m_nStuId >> obj.m_nCourseId >> obj.m_nScore;
    return in;
}