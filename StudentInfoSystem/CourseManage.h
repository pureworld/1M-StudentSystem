#pragma once
#include "CourseInfo.h"
#include "MyTree.h"
#include "MyMapTree.h"

#define COURSE_NUMBER 1000

class CCourseManage
{
public:
    CCourseManage(void);
    ~CCourseManage(void);

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
    CMyMapTree<int, CCourseInfo> m_IdTree;
    CMyMapTree<CMyString, CCourseInfo> m_NameTree;
};

