#pragma once
#include "StuInfo.h"
#include "MyTree.h"
#include "MyMapTree.h"

#define STU_NUMBER 100000

class CStuManage
{
public:
    CStuManage(void);
    ~CStuManage(void);

    void Init();
    void ReadFile();
    void WriteFile();

    void ShowAll();

    bool Has_It(int id) {
        if (m_IdTree.Find(id) == NULL) {
            return false;
        }
        return true;
    }
    void QueryById(int id);
    void QueryByName(CMyString name);

    bool Add(int id, CMyString name);

    bool ModifyId(int preId, int curId);
    bool ModifyName(int id, CMyString name);

    bool Delete(int id);
private:
    CMyMapTree<int, CStuInfo> m_IdTree;
    CMyTree<CMyString, CStuInfo> m_NameTree;
};

