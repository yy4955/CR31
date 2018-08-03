#pragma once
#include "stdafx.h"
#define TOTAL 10
class CStudent
{
public:
    CStudent(){}
    CStudent(int ID, char* name );
    ~CStudent();
    int  nID; //学号
    char szName[10]; //姓名
    int nLine ;//行数

    bool operator< (CStudent& stu)
    {
        if (nID < stu.nID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator>(CStudent& stu)
    {
        if (nID > stu.nID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator== (CStudent& stu)
    {
        if (nID == stu.nID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!= (CStudent& stu)
    {
        if (nID != stu.nID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator< (CStudent stu)
    {
        if (strcmp(szName, stu.szName) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator>(CStudent stu)
    {
        if (strcmp(szName, stu.szName) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator== (CStudent stu)
    {
        if (strcmp(szName, stu.szName) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!= (CStudent stu)
    {
        if (strcmp(szName, stu.szName) != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

//CStudent::CStudent(int ID, char* name, char*courseID[2]){
//    data = nID;
//    nHeight = 1;
//    memmove((void*)szName, (void*)name, sizeof(name));
//    memmove((void*)szCourseID, (void*)courseID[2], sizeof(courseID));
//    pParent = NULL;
//    pLeft = NULL;
//    pRight = NULL;
//    pList = NULL;
//}
//
//CStudent::~CStudent(){}