#pragma once
#include "MyTree.h"
#include "StuManage.h"
#include "CourseManage.h"
#include "RecordInfo.h"

class CRecordManage
{
public:
    CRecordManage(void);
    ~CRecordManage(void);

    void Init();
    void ReadIndex();
    void ReadFile();
    void WriteFile();

    void ShowAll();

    void QueryByStuId(int id);
    void QueryByCourseId(int id);

    bool Add(int stuId, int courseId, int score);

    bool ModifyScore(int stuId, int courseId, int score);

    bool Delete(int stuId, int courseId);
private:
    int m_index[10];
    int m_nIndex;
    CMyTree<int, CRecordInfo> m_stuTree;
    CMyTree<int, CRecordInfo> m_courseTree;
};

