#pragma once
class CCourseInformation
{
public:
    CCourseInformation();
    CCourseInformation(int ID,char*name);
    ~CCourseInformation();
    char szCourseName[10];//课程信息
    int nCourseID = 0;//课程id
    int nLine = 0;//文件行计数

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

