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
    void ReadFile();
    void WriteFile();

    bool HasStu(int stuId) {
        if (m_stuTree.Find(stuId) == NULL) {
            return false;
        }
        return true;
    }
    bool HasCourse(int courseId) {
        if (m_courseTree.Find(courseId) == NULL) {
            return false;
        }
        return true;
    }

    void ShowAll();

    void QueryByStuId(int id);
    void QueryByCourseId(int id);

    bool Add(int stuId, int courseId, int score);

    bool ModifyScore(int stuId, int courseId, int score);

    bool Delete(int stuId, int courseId);
private:
    CMyTree<int, CRecordInfo> m_stuTree;
    CMyTree<int, CRecordInfo> m_courseTree;
};

