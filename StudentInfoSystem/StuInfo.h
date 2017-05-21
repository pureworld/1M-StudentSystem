#pragma once
#include "MyString.h"
class CStuInfo
{
public:
    CStuInfo(void);
    CStuInfo(int id, CMyString name);
    ~CStuInfo(void);

    int GetId() {
        return m_nId;
    }
    CMyString GetName() {
        return m_Name;
    }

    bool operator==(CStuInfo);

    friend ostream& operator<<(ostream&, CStuInfo&);
private:
    int m_nId;
    CMyString m_Name;
};
