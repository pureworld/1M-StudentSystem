#include "RecordManage.h"
#include <fstream>
#include <ctime>
#include <sstream>

CRecordManage::CRecordManage(void)
{
    m_nIndex = -1;
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

    for (int i = 0; i < 100000; i++) {
        for (int j = 0; j < 10; j++) {
            int score = rand() % 101;
            CRecordInfo tmp(stuId[i], courseId[j], score);
            m_stuTree.InsertNode(stuId[i], tmp);
            m_courseTree.InsertNode(courseId[j], tmp);   
        }
    }

    WriteFile();
}

void CRecordManage::ReadIndex() {
    ifstream in("record.data", ios::in);
    for (int i = 0; i < 10; i++) {
        in >> m_index[i];
    }
}

void CRecordManage::ReadFile() {
    char* file[10] = {
        "record1.data",
        "record2.data",
        "record3.data",
        "record4.data",
        "record5.data",
        "record6.data",
        "record7.data",
        "record8.data",
        "record9.data",
        "record10.data",
    };
    m_stuTree.Clear();
    m_courseTree.Clear();
    ifstream in(file[m_nIndex], ios::in);
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
    char* file[10] = {
        "record1.data",
        "record2.data",
        "record3.data",
        "record4.data",
        "record5.data",
        "record6.data",
        "record7.data",
        "record8.data",
        "record9.data",
        "record10.data",
    };
    m_stuTree.OutputFile(file[m_nIndex]);
}

void CRecordManage::ShowAll() {
    cout << "100W 不显示" << endl;
}

void CRecordManage::QueryByStuId(int id) {
    for (int i = 9; i >= 0; i--) {
        if (id > m_index[i]) {
            m_nIndex = i;
            break;
        }
    }
    ReadFile();
    TreeNode<int, CRecordInfo>* pNode = m_stuTree.Find(id);
    cout << "选课记录如下" << endl;
    while (pNode != NULL) {
        cout << pNode->m_Value << endl;
        pNode = pNode->m_pNext;
    }
}
void CRecordManage::QueryByCourseId(int id) {

}

bool CRecordManage::Add(int stuId, int courseId, int score) {
    for (int i = 9; i >= 0; i--) {
        if (stuId > m_index[i]) {
            m_nIndex = i;
            break;
        }
    }
    ReadFile();
    CRecordInfo tmp(stuId, courseId, score);
    m_stuTree.InsertNode(stuId, tmp);
    m_courseTree.InsertNode(courseId, tmp);
    WriteFile();
    return true;
}

bool CRecordManage::ModifyScore(int stuId, int courseId, int score) {
    return false;

}

bool CRecordManage::Delete(int stuId, int courseId) {
    return false;

}