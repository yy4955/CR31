#pragma once
class CRecord
{
public:
    CRecord(int stuID, int CourseID, int Scorse);
    CRecord();
    ~CRecord();
//     CRecord operator=(CRecord& Record)
//     {
//         CRecord RecordtoReturn;
//         RecordtoReturn.nCourseID = Record.nCourseID;
//         RecordtoReturn.nScore = Record.nScore;
//         RecordtoReturn.nStuID = Record.nStuID;
//         return RecordtoReturn;
//     }
    int nStuID;//学生ID
    int nCourseID;//课程id
    int nScore;//分数
//     char szStuName[10];//学生姓名
//     char szCourName[10];//课程名
    int nLine = 0;//文件行计数

//     bool operator< (CRecord& stu)
//     {
//         if (nStuID < stu.nStuID)
//         {
//             return true;
//         }
//         else
//         {
//             return false;
//         }
//     }
// 
//     bool operator>(CRecord& stu)
//     {
//         if (nStuID > stu.nStuID)
//         {
//             return true;
//         }
//         else
//         {
//             return false;
//         }
//     }
// 
//     bool operator== (CRecord& stu)
//     {
//         if (nStuID == stu.nStuID)
//         {
//             return true;
//         }
//         else
//         {
//             return false;
//         }
//     }
// 
//     bool operator!= (CRecord& stu)
//     {
//         if (nStuID != stu.nStuID)
//         {
//             return true;
//         }
//         else
//         {
//             return false;
//         }
//     }

    bool operator< (CRecord& Course)
    {
        if (nCourseID < Course.nCourseID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator>(CRecord& Course)
    {
        if (nCourseID > Course.nCourseID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator== (CRecord& Course)
    {
        if (nCourseID == Course.nCourseID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!= (CRecord& Course)
    {
        if (nCourseID != Course.nCourseID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};

