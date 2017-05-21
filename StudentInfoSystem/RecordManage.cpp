#include "RecordManage.h"
#include <fstream>
#include <ctime>
#include <sstream>

CRecordManage::CRecordManage(void)
{
}


CRecordManage::~CRecordManage(void)
{
}

void CRecordManage::Init() {
    srand(time(NULL));
    int stuId[STU_NUMBER];
    for (int i = 0; i < STU_NUMBER; i++) {
        stuId[i] = 10000000 + i;
    }
    int courseId[COURSE_NUMBER];
    for (int i = 0; i < COURSE_NUMBER; i++) {
        courseId[i] = 58000000 + i;
    }

    for (int iii = 0; iii < 100000; iii++) {
        int sign[COURSE_NUMBER] = {0};
        for (int j = 0; j < 10; j++) {
            int courseIndex = rand() % COURSE_NUMBER;
            while (sign[courseIndex] == 1) {
                courseIndex++;
            }
            sign[courseIndex] = 1;
            int score = rand() % 101;
            CRecordInfo tmp(stuId[iii], courseId[courseIndex], score);
            m_stuTree.InsertNode(stuId[iii], tmp);
            m_courseTree.InsertNode(courseId[courseIndex], tmp);  
        }
        cout << iii << endl;
    }

    WriteFile();
}

void CRecordManage::ReadFile() {
    m_stuTree.Clear();
    m_courseTree.Clear();
    ifstream in("record.data", ios::in);
    CRecordInfo tmp;
    while (!in.eof()) {
        int stuId, courseId, score = -1;
        in >> stuId >> courseId >> score;
        if (score == -1) {
            break;
        }
        tmp.Set(stuId, courseId, score);
        m_stuTree.InsertNode(stuId, tmp);
        m_courseTree.InsertNode(courseId, tmp);
    }
}

void CRecordManage::WriteFile() {
    m_stuTree.OutputFile("record.data");
}

void CRecordManage::ShowAll() {
    cout << "100W 不显示" << endl;
}

void CRecordManage::QueryByStuId(int id) {
    TreeNode<int, CRecordInfo>* pNode = m_stuTree.Find(id);
    cout << "选课记录如下：" << endl;
    while (pNode != NULL) {
        cout << pNode->m_Value << endl;
        pNode = pNode->m_pNext;
    }
}
void CRecordManage::QueryByCourseId(int id) {
    TreeNode<int, CRecordInfo>* pNode = m_courseTree.Find(id);
    cout << "选则该课学生如下：" << endl;
    while (pNode != NULL) {
        cout << pNode->m_Value << endl;
        pNode = pNode->m_pNext;
    }
}

bool CRecordManage::Add(int stuId, int courseId, int score) {
    CRecordInfo tmp(stuId, courseId, score);
    m_stuTree.InsertNode(stuId, tmp);
    m_courseTree.InsertNode(courseId, tmp);
    WriteFile();
    return true;
}

bool CRecordManage::ModifyScore(int stuId, int courseId, int score) {
    bool bRet = false;
    if (Delete(stuId, courseId)) {
        bRet = Add(stuId, courseId, score);
    }
    return bRet;
}

bool CRecordManage::Delete(int stuId, int courseId) {
    int find = 0;
    TreeNode<int, CRecordInfo>* pNode = m_stuTree.Find(stuId);
    while (pNode != NULL) {
        if (pNode->m_Value.GetCourseId() == courseId) {
            find = 1;
            break;
        }
        pNode = pNode->m_pNext;
    }
    if (find == 0) {
        cout << "该学生未选该课！" << endl;
    }
    m_stuTree.DeleteNode(stuId, pNode->m_Value);
    m_courseTree.DeleteNode(courseId, pNode->m_Value);
    WriteFile();
    return true;
}