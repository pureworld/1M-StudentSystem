#pragma once
#include "RecordManage.h"

class CStuSysView {
public:
    CStuSysView();
    ~CStuSysView();

    void MainLoop();
    void MainLoop2();

    void SecLoop1();
    void SecLoop2();
    void SecLoop3();
    void SecLoop4();
    void SecLoop5();

    void Init();
    void ReadFile();
private:
    CStuManage m_Stu;
    CCourseManage m_Course;
    CRecordManage m_Record;
};

