#include "StuSysView.h"
#include <iostream>
#include <ctime>
using namespace std;

CStuSysView::CStuSysView() {
    MainLoop();
}

CStuSysView::~CStuSysView() {
}

void CStuSysView::MainLoop() {
    while (true) {
        system("cls");
        cout << "1.�����ʼ������(��ʱ̫�ù��ܹر�)" << endl;
        cout << "2.�����������ж�ȡ" << endl;
        cout << "��������ѡ����(��*���˳�����#��������һ��)��";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            //Init();
            //MainLoop2();
            break;
        case '2':
            ReadFile();
            MainLoop2();
            break;
        case '*':
        case 'q':
            exit(0);
            break;
        case '#':
            exit(0);
            break;
        default:
            cout << "�������룡" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::MainLoop2() {
    while (true) {
        system("cls");
        cout << "1.��ʾ��Ϣ" << endl;
        cout << "2.��ѯ��Ϣ"  << endl;
        cout << "3.������Ϣ" << endl;
        cout << "4.�޸���Ϣ" << endl;
        cout << "5.ɾ����Ϣ" << endl;
        cout << "��������ѡ����(��*���˳�����#��������һ��)��";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            SecLoop1();
            break;
        case '2':
            SecLoop2();
            break;
        case '3':
            SecLoop3();
            break;
        case '4':
            SecLoop4();
            break;
        case '5':
            SecLoop5();
            break;
        case '*':
            exit(0);
            break;
        case '#':
            exit(0);
            break;
        default:
            cout << "�������룡" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop1() {
    while (true) {
        system("cls");
        cout << "1.��ʾ����ѧ��(10������ѡ)" << endl;
        cout << "2.��ʾ���пγ�" << endl;
        cout << "3.��ʾ����ѡ�μ�¼(��ʱ̫�ù��ܹر�)" << endl;
        cout << "��������ѡ����(��*���˳�����#��������һ��)��";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            m_Stu.ShowAll();
            break;
        case '2':
            m_Course.ShowAll();
            break;
        case '3':
            cout << "m_Record.ShowAll()" << endl;
            break;
        case '*':
            exit(0);
            break;
        case '#':
            return;
            break;
        default:
            cout << "�������룡" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop2() {
    while (true) {
        system("cls");
        cout << "1.ͨ��ѧ��ID��ѯ����������ѡ�μ�¼" << endl;
        cout << "2.ͨ��������ѯ����ͬ��ѧ����ID������" << endl;
        cout << "3.ͨ���γ�ID��ѯ����ѡ��ѧ���ͳɼ�����δʵ��" << endl;
        cout << "4.ͨ���γ�����ѯ����ѡ��ѧ���ͳɼ�����δʵ��" << endl;
        cout << "��������ѡ����(��*���˳�����#��������һ��)��";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            int stuId;
            cin >> stuId;
            m_Stu.QueryById(stuId);
            m_Record.QueryByStuId(stuId);
            break;
        case '2':
            {
                CMyString stuName;
                cin >> stuName;
                m_Stu.QueryByName(stuName);
                break;
            }
        case '3':
            int id;
            cin >> id;
            m_Course.QueryById(id);
            break;
        case '4':
            {
                CMyString name;
                cin >> name;
                m_Course.QueryByName(name);
                break;
            }
        case '*':
            exit(0);
            break;
        case '#':
            return;
            break;
        default:
            cout << "�������룡" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop3() {
    while (true) {
        system("cls");
        cout << "1.����ѧ����Ϣ" << endl;
        cout << "2.���ӿγ���Ϣ" << endl;
        cout << "3.����ѡ�μ�¼" << endl;
        cout << "��������ѡ����(��*���˳�����#��������һ��)��";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            {
                int id;
                CMyString name;
                cin >> id >> name;
                if(m_Stu.Add(id, name)) {
                    cout << "���ӣ�" << id << "," << name << "���ɹ���";
                }
                break;
            }
        case '2':
            {
                int id;
                CMyString name;
                cin >> id >> name;
                if(m_Course.Add(id, name)) {
                    cout << "���ӣ�" << id << "," << name << "���ɹ���";
                }
                break;
            }
        case '3':
            {
                int stuId;
                int courseId;
                int score;
                cin >> stuId >> courseId >> score;
                if (!m_Stu.Has_It(stuId)) {
                    cout << "�޸�ѧ����Ϣ��" << endl;
                } else if (!m_Course.Has_It(courseId)) {
                    cout << "�޸ÿγ���Ϣ��" << endl;
                } else if (m_Record.Add(stuId, courseId, score)) {
                    cout << "���ӣ�" << stuId << "��" << courseId
                        << "��" << score << "���ɹ���";
                }
                break;
            }
        case '*':
            exit(0);
            break;
        case '#':
            return;
            break;
        default:
            cout << "�������룡" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop4() {
    while (true) {
        system("cls");
        cout << "1.ͨ��ѧ��ԭID����ID�޸�ID" << endl;
        cout << "2.ͨ��ѧ��ID�޸�����" << endl;
        cout << "3.ͨ���γ�ԭID����ID�޸�ID" << endl;
        cout << "4.ͨ���γ�ID�޸Ŀγ���" << endl;
        cout << "5.ͨ��ѧ��ID�Ϳγ�ID�޸ĳɼ�" << endl;
        cout << "��������ѡ����(��*���˳�����#��������һ��)��";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            {
	            int preId;
	            int curId;
	            cin >> preId >> curId;
	            if (m_Stu.ModifyId(preId, curId)) {
	                cout << "�޸ĳɹ�" << endl;
	            }
	            break;
            }
        case '2':
            {
                int id;
                CMyString curName;
                cin >> id >> curName;
                if (m_Stu.ModifyName(id, curName)) {
                    cout << "�޸ĳɹ�" << endl;
                }
            	break;
            }
        case '3':
            {
                int preId;
                int curId;
                cin >> preId >> curId;
                if (m_Course.ModifyId(preId, curId)) {
                    cout << "�޸ĳɹ�" << endl;
                }
                break;
            }
        case '4':
            {
                int id;
                CMyString curName;
                cin >> id >> curName;
                if (m_Course.ModifyName(id, curName)) {
                    cout << "�޸ĳɹ�" << endl;
                }
                break;
            }
        case '5':
            break;
        case '*':
            exit(0);
            break;
        case '#':
            return;
            break;
        default:
            cout << "�������룡" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop5() {
    while (true) {
        system("cls");
        cout << "1.ͨ��ѧ��IDɾ��ѧ����Ϣ" << endl;
        cout << "2.ͨ���γ�IDɾ���γ���Ϣ" << endl;
        cout << "3.ͨ��ѧ��ID�Ϳγ�IDɾ��ѡ�μ�¼" << endl;
        cout << "��������ѡ����(��*���˳�����#��������һ��)��";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            {
	            int id;
	            cin >> id;
	            if (m_Stu.Delete(id)) {
	                cout << "ɾ���ɹ���" << endl;
	            }
	            break;
            }
        case '2':
            {
                int id;
                cin >> id;
                if (m_Course.Delete(id)) {
                    cout << "ɾ���ɹ���" << endl;
                }
                break;
            }
        case '3':
            break;
        case '*':
            exit(0);
            break;
        case '#':
            return;
            break;
        default:
            cout << "�������룡" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::Init() {
    m_Stu.Init();
    m_Course.Init();
    m_Record.Init();
}

void CStuSysView::ReadFile() {
    m_Stu.ReadFile();
    m_Course.ReadFile();
    m_Record.ReadIndex();
}