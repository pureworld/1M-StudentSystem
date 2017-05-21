#include "StuManage.h"
#include <ctime>
#include <fstream>

CStuManage::CStuManage() {

}

CStuManage::~CStuManage() {

}

void CStuManage::Init() {
    CMyString table[26] = {"a", "b", "c", "d", "e", "f", "g", "h",
        "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
        "u", "v", "w", "x", "y", "z"};

    int id[STU_NUMBER];
    for (int i = 0; i < STU_NUMBER; i++) {
        id[i] = 10000000 + i;
    }
    srand(time(NULL));
    CMyString s1[100], s2[100], s3[10];
    for (int i = 0; i < 100; i++) {
        int n = rand() % 26;
        s1[i] += table[n];
        s1[i] += table[(n+8)%26];
        s1[i] += table[(n+16)%26];
    }
    for (int i = 0; i < 100; i++) {
        int n = rand() % 26;
        s2[i] += table[n];
        s2[i] += table[(n+8)%26];
        s2[i] += table[(n+16)%26];
    }
    for (int i = 0; i < 10; i++) {
        int n = rand() % 26;
        s3[i] += table[n];
        s3[i] += table[(n+13)%26];
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            for (int k = 0; k < 10; k++) {
                CMyString strTmp;
                strTmp += s1[i];
                strTmp += s2[j];
                strTmp += s3[k];
                CStuInfo tmp(id[i*1000+j*10+k], strTmp);
                m_IdTree.InsertNode(id[i*1000+j*10+k], tmp);
                m_NameTree.InsertNode(strTmp, tmp);
            }
        }
    }

    WriteFile();
}

void CStuManage::ReadFile() {
    m_IdTree.Clear();
    m_NameTree.Clear();
    ifstream in("stu.data", ios::in);
    if (in.is_open()) {
        while (!in.eof()) {
            int id;
            CMyString name;
	        in >> id >> name;
            if (name == "") {
                break;
            }
	        CStuInfo tmp(id, name);
	        m_IdTree.InsertNode(id, tmp);
	        m_NameTree.InsertNode(name, tmp);
        }
    }

}

void CStuManage::WriteFile() {
    m_IdTree.OutputFile("stu.data");
}

void CStuManage::ShowAll() {
    m_IdTree.InOrder();
}

void CStuManage::QueryById(int id) {
    MapTreeNode<int, CStuInfo>* pNode =  m_IdTree.Find(id);
    cout << pNode->m_Value << endl;
}

void CStuManage::QueryByName(CMyString name) {
    TreeNode<CMyString, CStuInfo>* pNode = m_NameTree.Find(name);
    int nCnt = 1;
    while (pNode != NULL) {
        cout << "第" << nCnt << "个：" << endl;
        cout << pNode->m_Value << endl;
        pNode = pNode->m_pNext;
        nCnt++;
    }
    cout << "共找到" << nCnt - 1 << "个学生" << endl;
}

bool CStuManage::Add(int id, CMyString name) {
    if (m_IdTree.Find(id) != NULL) {
        cout << "错误！已有该ID信息！" << endl;
        return false;
    }
    CStuInfo tmp(id, name);
    m_IdTree.InsertNode(id, tmp);
    m_NameTree.InsertNode(name, tmp);
    WriteFile();
    return true;
}

bool CStuManage::ModifyId(int preId, int curId) {
    if (m_IdTree.Find(curId) != NULL) {
        cout << "错误！已有该ID信息！" << endl;
        return false;
    }
    MapTreeNode<int, CStuInfo>* pNode =  m_IdTree.Find(preId);
    Delete(preId);
    Add(curId, pNode->m_Value.GetName());
    return true;
}

bool CStuManage::ModifyName(int id, CMyString name) {
    if (m_IdTree.Find(id) == NULL) {
        cout << "错误！无该ID信息！" << endl;
        return false;
    }

    Delete(id);
    Add(id, name);
    return true;
}

bool CStuManage::Delete(int id) {
    MapTreeNode<int, CStuInfo>* pNode =  m_IdTree.Find(id);
    if (pNode == NULL) {
        cout << "错误！无该ID信息！" << endl;
        return false;
    }

    m_IdTree.DeleteNode(id);
    m_NameTree.DeleteNode(pNode->m_Value.GetName(), pNode->m_Value);
    WriteFile();
    return true;
}