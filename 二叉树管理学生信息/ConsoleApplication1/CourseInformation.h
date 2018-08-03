#pragma once
class CCourseInformation
{
public:
    CCourseInformation();
    CCourseInformation(int ID,char*name);
    ~CCourseInformation();
    char szCourseName[10];//�γ���Ϣ
    int nCourseID = 0;//�γ�id
    int nLine = 0;//�ļ��м���

    bool operator< (CCourseInformation& stu)
    {
        if (nCourseID < stu.nCourseID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator>(CCourseInformation& stu)
    {
        if (nCourseID > stu.nCourseID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator== (CCourseInformation& stu)
    {
        if (nCourseID == stu.nCourseID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!= (CCourseInformation& stu)
    {
        if (nCourseID != stu.nCourseID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator< (CCourseInformation stu)
    {
        if (strcmp(szCourseName, stu.szCourseName) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator>(CCourseInformation stu)
    {
        if (strcmp(szCourseName, stu.szCourseName) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator== (CCourseInformation stu)
    {
        if (strcmp(szCourseName, stu.szCourseName) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!= (CCourseInformation stu)
    {
        if (strcmp(szCourseName, stu.szCourseName) != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

