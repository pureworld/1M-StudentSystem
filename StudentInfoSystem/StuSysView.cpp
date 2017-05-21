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
        cout << "1.随机初始化数据(耗时太久功能关闭)" << endl;
        cout << "2.从已有数据中读取" << endl;
        cout << "输入数字选择功能(“*”退出，“#”返回上一层)：";
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
            cout << "错误输入！" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::MainLoop2() {
    while (true) {
        system("cls");
        cout << "1.显示信息" << endl;
        cout << "2.查询信息"  << endl;
        cout << "3.增加信息" << endl;
        cout << "4.修改信息" << endl;
        cout << "5.删除信息" << endl;
        cout << "输入数字选择功能(“*”退出，“#”返回上一层)：";
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
            cout << "错误输入！" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop1() {
    while (true) {
        system("cls");
        cout << "1.显示所有学生(10万条慎选)" << endl;
        cout << "2.显示所有课程" << endl;
        cout << "3.显示所有选课记录(耗时太久功能关闭)" << endl;
        cout << "输入数字选择功能(“*”退出，“#”返回上一层)：";
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
            cout << "错误输入！" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop2() {
    while (true) {
        system("cls");
        cout << "1.通过学生ID查询姓名和所有选课记录" << endl;
        cout << "2.通过姓名查询所有同名学生的ID和姓名" << endl;
        cout << "3.通过课程ID查询所有选课学生和成绩：暂未实现" << endl;
        cout << "4.通过课程名查询所有选课学生和成绩：暂未实现" << endl;
        cout << "输入数字选择功能(“*”退出，“#”返回上一层)：";
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
            cout << "错误输入！" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop3() {
    while (true) {
        system("cls");
        cout << "1.增加学生信息" << endl;
        cout << "2.增加课程信息" << endl;
        cout << "3.增加选课记录" << endl;
        cout << "输入数字选择功能(“*”退出，“#”返回上一层)：";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            {
                int id;
                CMyString name;
                cin >> id >> name;
                if(m_Stu.Add(id, name)) {
                    cout << "增加（" << id << "," << name << "）成功！";
                }
                break;
            }
        case '2':
            {
                int id;
                CMyString name;
                cin >> id >> name;
                if(m_Course.Add(id, name)) {
                    cout << "增加（" << id << "," << name << "）成功！";
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
                    cout << "无该学生信息！" << endl;
                } else if (!m_Course.Has_It(courseId)) {
                    cout << "无该课程信息！" << endl;
                } else if (m_Record.Add(stuId, courseId, score)) {
                    cout << "增加（" << stuId << "，" << courseId
                        << "，" << score << "）成功！";
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
            cout << "错误输入！" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop4() {
    while (true) {
        system("cls");
        cout << "1.通过学生原ID和现ID修改ID" << endl;
        cout << "2.通过学生ID修改姓名" << endl;
        cout << "3.通过课程原ID和现ID修改ID" << endl;
        cout << "4.通过课程ID修改课程名" << endl;
        cout << "5.通过学生ID和课程ID修改成绩" << endl;
        cout << "输入数字选择功能(“*”退出，“#”返回上一层)：";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            {
	            int preId;
	            int curId;
	            cin >> preId >> curId;
	            if (m_Stu.ModifyId(preId, curId)) {
	                cout << "修改成功" << endl;
	            }
	            break;
            }
        case '2':
            {
                int id;
                CMyString curName;
                cin >> id >> curName;
                if (m_Stu.ModifyName(id, curName)) {
                    cout << "修改成功" << endl;
                }
            	break;
            }
        case '3':
            {
                int preId;
                int curId;
                cin >> preId >> curId;
                if (m_Course.ModifyId(preId, curId)) {
                    cout << "修改成功" << endl;
                }
                break;
            }
        case '4':
            {
                int id;
                CMyString curName;
                cin >> id >> curName;
                if (m_Course.ModifyName(id, curName)) {
                    cout << "修改成功" << endl;
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
            cout << "错误输入！" << endl;
            break;
        }
        system("pause");
    }
}

void CStuSysView::SecLoop5() {
    while (true) {
        system("cls");
        cout << "1.通过学生ID删除学生信息" << endl;
        cout << "2.通过课程ID删除课程信息" << endl;
        cout << "3.通过学生ID和课程ID删除选课记录" << endl;
        cout << "输入数字选择功能(“*”退出，“#”返回上一层)：";
        char c;
        cin >> c;
        switch (c) {
        case '1':
            {
	            int id;
	            cin >> id;
	            if (m_Stu.Delete(id)) {
	                cout << "删除成功！" << endl;
	            }
	            break;
            }
        case '2':
            {
                int id;
                cin >> id;
                if (m_Course.Delete(id)) {
                    cout << "删除成功！" << endl;
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
            cout << "错误输入！" << endl;
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