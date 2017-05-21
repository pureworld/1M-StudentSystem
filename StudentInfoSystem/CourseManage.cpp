#include "CourseManage.h"
#include <ctime>
#include <fstream>

CCourseManage::CCourseManage() {

}

CCourseManage::~CCourseManage() {

}

void CCourseManage::Init() {
    CMyString table[26] = {"a", "b", "c", "d", "e", "f", "g", "h",
        "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
        "u", "v", "w", "x", "y", "z"};

    int id[COURSE_NUMBER];
    for (int i = 0; i < COURSE_NUMBER; i++) {
        id[i] = 58000000 + i;
    }
    srand(time(NULL));
    CMyString s1[10], s2[10], s3[10];
    int sign1[26] = {0}, sign2[26] = {0}, sign3[26] = {0};
    for (int i = 0; i < 10; i++) {
        int n = rand() % 26;
        while (true) {
            if (sign1[n] == 0) {
                sign1[n] = 1;
                break;
            } else {
                n = (n+1) % 26;
            }
        }
        s1[i] += table[n];
        s1[i] += table[(n*2)%26];
        s1[i] += table[(n*3)%26];
    }
    for (int i = 0; i < 10; i++) {
        int n = rand() % 26;
        while (true) {
            if (sign2[n] == 0) {
                sign2[n] = 1;
                break;
            } else {
                n = (n+1) % 26;
            }
        }
        s2[i] += table[n];
        s2[i] += table[(n*2)%26];
        s2[i] += table[(n*3)%26];
    }
    for (int i = 0; i < 10; i++) {
        int n = rand() % 26;
        while (true) {
            if (sign3[n] == 0) {
                sign3[n] = 1;
                break;
            } else {
                n = (n+1) % 26;
            }
        }
        s3[i] += table[n];
        s3[i] += table[(n*2)%26];
        s3[i] += table[(n*3)%26];
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                CMyString strTmp;
                strTmp += s1[i];
                strTmp += s2[j];
                strTmp += s3[k];
                CCourseInfo tmp(id[i*100+j*10+k], strTmp);
                m_IdTree.InsertNode(id[i*100+j*10+k], tmp);
                m_NameTree.InsertNode(strTmp, tmp);
            }
        }
    }
    WriteFile();
}

void CCourseManage::ReadFile() {
    m_IdTree.Clear();
    m_NameTree.Clear();
    ifstream in("course.data", ios::in);
    if (in.is_open()) {
        while (!in.eof()) {
            int id;
            CMyString name;
            in >> id >> name;
            if (name == "") {
                break;
            }
            CCourseInfo tmp(id, name);
            m_IdTree.InsertNode(id, tmp);
            m_NameTree.InsertNode(name, tmp);
        }
    }

}

void CCourseManage::WriteFile() {
    m_IdTree.OutputFile("course.data");
}

void CCourseManage::ShowAll() {
    m_IdTree.InOrder();
}

void CCourseManage::QueryById(int id) {
    MapTreeNode<int, CCourseInfo>* pNode =  m_IdTree.Find(id);
    cout << pNode->m_Value << endl;
}

void CCourseManage::QueryByName(CMyString name) {
    MapTreeNode<CMyString, CCourseInfo>* pNode = m_NameTree.Find(name);
    cout << pNode->m_Value << endl;
}

bool CCourseManage::Add(int id, CMyString name) {
    if (m_IdTree.Find(id) != NULL) {
        cout << "错误！已有该ID信息！" << endl;
        return false;
    }
    if (m_NameTree.Find(name) != NULL) {
        cout << "错误！已有该课程名信息！" << endl;
        return false;
    }
    CCourseInfo tmp(id, name);
    m_IdTree.InsertNode(id, tmp);
    m_NameTree.InsertNode(name, tmp);
    WriteFile();
    return true;
}

bool CCourseManage::ModifyId(int preId, int curId) {
    if (m_IdTree.Find(curId) != NULL) {
        cout << "错误！已有该ID信息！" << endl;
        return false;
    }
    MapTreeNode<int, CCourseInfo>* pNode =  m_IdTree.Find(preId);
    Delete(preId);
    Add(curId, pNode->m_Value.GetName());
    return true;
}

bool CCourseManage::ModifyName(int id, CMyString name) {
    if (m_IdTree.Find(id) == NULL) {
        cout << "错误！无该ID信息！" << endl;
        return false;
    }

    Delete(id);
    Add(id, name);
    return true;
}

bool CCourseManage::Delete(int id) {
    MapTreeNode<int, CCourseInfo>* pNode =  m_IdTree.Find(id);
    if (pNode == NULL) {
        cout << "错误！无该ID信息！" << endl;
        return false;
    }

    m_IdTree.DeleteNode(id);
    m_NameTree.DeleteNode(pNode->m_Value.GetName());
    WriteFile();
    return true;
}