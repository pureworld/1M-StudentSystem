#include "StuInfo.h"


CStuInfo::CStuInfo(void)
{
}

CStuInfo::CStuInfo(int id, CMyString name) {
    m_nId = id;
    m_Name = name;
}

CStuInfo::~CStuInfo(void)
{
}

bool CStuInfo::operator==(CStuInfo obj) {
    return ((m_nId == obj.m_nId)&&(m_Name == obj.m_Name));
}

ostream& operator<<(ostream& out, CStuInfo& obj) {
    out << obj.m_nId << endl;
    out << obj.m_Name;
    return out;
}