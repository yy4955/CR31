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
    int nStuID;//ѧ��ID
    int nCourseID;//�γ�id
    int nScore;//����
//     char szStuName[10];//ѧ������
//     char szCourName[10];//�γ���
    int nLine = 0;//�ļ��м���

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

