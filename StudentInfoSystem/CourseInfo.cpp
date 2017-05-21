#include "CourseInfo.h"


CCourseInfo::CCourseInfo(void)
{
}

CCourseInfo::CCourseInfo(int id, CMyString name) {
    m_nId = id;
    m_CourseName = name;
}

CCourseInfo::~CCourseInfo(void)
{
}

bool CCourseInfo::operator==(CCourseInfo obj) {
    return ((m_nId == obj.m_nId)&&(m_CourseName == obj.m_CourseName));
}

ostream& operator<<(ostream& out, CCourseInfo& obj) {
    out << obj.m_nId << endl;
    out << obj.m_CourseName;
    return out;
}