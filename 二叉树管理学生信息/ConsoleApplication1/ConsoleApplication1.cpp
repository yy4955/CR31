// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//1.选课信息的插入,2.查找函数遇到同名的怎么处理,3.左右都不为空,怎么插入

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "MyTree.h"
#include "Data.h"

using namespace std;
//读文件

int menu();

//写入文件
int _tmain(int argc, _TCHAR* argv[])
{
    /*
    1.先读文件,关闭文件
    2.数据在二叉树中操作,打开关闭
    3.
    */
    CData data;
    CStudent stuIDtoName;
    CStudent stuNametoID;

    CCourseInformation courIDtoName;
    CCourseInformation courNametoID;

    CRecord RecStuID;
    CRecord RecCourID;

    //6颗树
    CMyTree stuIDtoNameTree;
    CMyTree stuNametoIDTree;

    CMyTree courIDtoNameTree;
    CMyTree courNametoIDTree;

    CMyTree RecStuIDTree;
    CMyTree RecCourIDTree;

    char szBuff[100] = "";
    int nStuline = 0;//学生文本行数统计
    int nCourline = 0;//课程信息文本行数统计
    int nRecline = 0;//选课信息文本行数统计

    ifstream fileStu;
    //stu  学生信息

    //stringstream buffer;
    //string s;
    //fileStu.open("stu.txt", ios::in);//都文件打开
    fileStu.open("stu.txt",ios::in);//都文件打开
    while (!fileStu.eof())
    {
        if (fileStu.eof())//判断是否到结尾，此判断一定要放到push_back前边
        {
            break;
        }
        //cout << s << endl;
        fileStu.getline(szBuff, sizeof(szBuff));
        nStuline++;
        stuIDtoName.nLine = nStuline;
        stuNametoID.nLine = nStuline;

        sscanf(szBuff, "%d-%s", &(stuIDtoName.nID), stuIDtoName.szName);
            if (stuIDtoName.nID != 0)
            {
                stuIDtoNameTree.InsertStuID(stuIDtoName);
                //cout << stuIDtoName.nID << "-" << stuIDtoName.szName << endl;
            }
 
         sscanf(szBuff, "%d-%s", &(stuNametoID.nID), stuNametoID.szName);
             if (stuNametoID.nID != 0)
             {
                 stuNametoIDTree.InsertStuName(stuNametoID);
                // cout << stuNametoID.szName << "-" << stuNametoID.nID << endl;
             }

            memset(szBuff, 0, sizeof(szBuff));

        //memset(stuIDtoName, 0, sizeof(stuIDtoName));
    }
    fileStu.close();
    cout << "学生类读取完毕" << endl;

    //读取课程信息
    ifstream fileCour;
    //lesson  课程信息
    fileCour.open("lesson.txt", ios::in);//都文件打开
    while (!fileCour.eof())
    {
        if (fileCour.eof())//判断是否到结尾，此判断一定要放到push_back前边
        {
            break;
        }
        fileCour.getline(szBuff, sizeof(szBuff));
        nCourline++;
        courIDtoName.nLine = nCourline;
        courNametoID.nLine = nCourline;

        sscanf(szBuff, "%d-%s", &(courIDtoName.nCourseID), courIDtoName.szCourseName);
        if (courIDtoName.nCourseID != 0)
        {
            courIDtoNameTree.InsertCourID(courIDtoName);
        }

        sscanf(szBuff, "%d-%s", &(courNametoID.nCourseID), courNametoID.szCourseName);
        if (courNametoID.nCourseID != 0)
        {
            courNametoIDTree.InsertCourName(courNametoID);
        }

        memset(szBuff, 0, sizeof(szBuff));
    }
    fileCour.close();
    cout << "课程信息类读取完毕" << endl;

    //读取选课记录
    ifstream fileRec;
    //xuanke  选课记录
    fileRec.open("xuanke.txt", ios::in);//都文件打开
    while (!fileRec.eof())
    {
        if (fileRec.eof())
        {
            break;
        }

        fileRec.getline(szBuff, 90);
        nRecline++;
        if (nRecline==420)
        {
            system("pause");
        }
        RecCourID.nLine = nRecline;
        RecStuID.nLine = nRecline;

        sscanf(szBuff, "%d-%d-%d", &(RecStuID.nStuID), &(RecStuID.nCourseID),&(RecStuID.nScore));
        if (RecStuID.nStuID != 0)
        {
            RecStuIDTree.InsertRecStuId(RecStuID);
           // cout << RecStuID.nStuID <<"-" << RecStuID.nCourseID << "-" << RecStuID.nScore<<"-"<< RecStuID.nLine << endl;
        }

         sscanf(szBuff, "%d-%d-%d", &(RecCourID.nStuID), &(RecCourID.nCourseID), &(RecCourID.nScore));
          if (RecCourID.nCourseID != 0)
          {
              RecCourIDTree.InsertRecCourId(RecCourID);
            //  cout << RecCourID.nCourseID << "-" << RecCourID.nStuID << "-" << RecCourID.nScore << "-" << RecCourID.nLine << endl;
          }

        memset(szBuff, 0, 99);
    }
    fileStu.close();
    cout << "选课记录读取完毕" << endl;

    //进入菜单栏
     while (true)
     {
         int nSet = 0;//子选项
         int n = 0;//学号,课程id临时接受
         char szTemName[100] = "";//名字临时
         int arrTemStuID[1000] = {0};//学号临时
         CRecord RecId[1000] ;//选课记录信息
         memset(RecId, 0, sizeof(RecId));

         switch (menu())
         {
         case 0:
             cout << "1.遍历学生信息" << endl;
             cout << "2.遍历课程信息" << endl;
             cout << "3.遍历选课记录" << endl;
            // cout << "4.遍历层序" << endl;
             scanf("%d", &nSet);
             fflush(stdin);
             switch (nSet)
             {
             case 1:
                 stuIDtoNameTree.StuLDR_stc(stuNametoIDTree.GetRoot());
                 system("pause");
                 break;
             case 2:
                 courIDtoNameTree.CourLDR_stc(courNametoIDTree.GetRoot());
                 system("pause");
                 break;
             case 3:
                 RecStuIDTree.RecLDR_stc(RecCourIDTree.GetRoot());
                 system("pause");
                 break;
//              case 4:
//                  stuNametoIDTree.NameLayer();
//                  system("pause");
//                  break;
             default:
                 break;
             }
             break;
         case 1://插入
             cout << "1.新增学生(ID, 名字)"<< endl;
             cout << "2.新增课程(ID, 名字)" << endl;
             cout << "3.新增选课记录(学生ID, 课程ID, 分数)" << endl;
             scanf("%1d",&nSet);
             fflush(stdin);
             switch (nSet)
             {
             case 1:            
                 if (data.AddStu(stuIDtoNameTree, stuNametoIDTree)==true)
                 {
                     cout << "增加成功" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "增加失败" << endl;
                     system("pause");
                 }
                 break;
             case 2:
                 
                 if (data.AddCour(courIDtoNameTree, courNametoIDTree) == true)
                     {
                         cout << "增加成功" << endl;
                         system("pause");
                     }
                     else
                     {
                         cout << "增加失败" << endl;
                         system("pause");
                     }
                 break;
             case 3:
                 if (data.AddRec(RecStuIDTree, RecCourIDTree,courIDtoNameTree,stuIDtoNameTree)==true)
                 {
                     cout << "增加成功" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "增加失败" << endl;
                     system("pause");
                 }
                 break;
             default:
                 break;
             }
             break;
         case 2:
             cout << "1.删除学生(ID, 名字)" << endl;
             cout << "2.删除课程(ID, 名字)" << endl;
             cout << "3.删除选课记录(学生ID, 课程ID, 分数)" << endl;
             scanf("%1d", &nSet);
             fflush(stdin);
             switch (nSet)
             {
             case 1:           
                 cout << "输入删除课学生ID" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.deleteStu(n, stuIDtoNameTree,stuNametoIDTree)==true)
                 {
                     cout << "删除成功" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "删除失败" << endl;
                     system("pause");
                 }
                 break;
             case 2:
                 cout << "请输入删除课程(ID)" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.deleteCour(n, courIDtoNameTree,courNametoIDTree) == true)
                 {
                     cout << "删除成功" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "删除失败" << endl;
                     system("pause");
                 }               
                 break;
             case 3:
                 cout << "请输入删除选课记录的学生ID" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.deleteRec(n, RecStuIDTree,RecCourIDTree) == true)
                 {
                     cout << "删除成功" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "删除失败" << endl;
                     system("pause");
                 }
             default:
                 break;
             }
             break;
         case 3://统计
             cout << "1.统计选修 xx 课程的学生考试情况"<< endl;
             scanf("%1d", &nSet);
             fflush(stdin);
             switch (nSet)
             {
             case 1:
                 cout << "1.请输入你要统计的课程名" << endl;
                 //cout << ">>" << endl;
                 scanf("%10s", szTemName);
                 fflush(stdin);
                 data.searchCourName(arrTemStuID, szTemName, courNametoIDTree);
                 int n = *arrTemStuID;
                 if (data.searchRecCourID(n, RecId, RecCourIDTree) == true)
                 {
                     int i = 0;
                     while (true)
                     {
                         if (RecId[i].nStuID != 0)
                         {
                             char szTempStuName[100] = "";
                             data.searchStuID(RecId[i].nStuID, szTempStuName, stuIDtoNameTree);
                             char szTempCourName[100] = "";
                             data.searchCourID(RecId[i].nCourseID, szTempCourName, courIDtoNameTree);
                             cout << "学生id:" << RecId[i].nStuID << "学生名字" << szTempStuName << "课程id:" << RecId[i].nCourseID << "课程名字:" << szTempCourName << "成绩:" << RecId[i].nScore << endl;
                             i++;
                             //system("pause"); 
                         }
                         else
                         {
                             system("pause");
                             break;
                         }
                     }
                 }
                 break;
             }
             break;
             //                  int n = arrTemStuID[i];
             //                  
             //                  if (data.Statistics(arrTemStuID,szTemName, courNametoIDTree, RecCourIDTree, arrTemStuID) == true)
             //                  {
             //                      int i =0;
             //                      while (true)
             //                      {
             //                          if (RecId[i].nStuID!=0)
             //                          {
             //                              char szTemStuName[100] = " ";
             //                              data.searchStuID(RecId[i].nStuID, szTemStuName, stuIDtoNameTree);
             //                              cout << "学生ID:" << RecId[i].nStuID << "学生姓名" << szTemStuName << "成绩" << RecId[i].nScore << endl;
             //                          }                   
             //                      }                     
             //                  }
         case 4://查询
             cout << "1.通过学生ID查询学生姓名" << endl;
             cout << "2.通过学生姓名查询学生ID " << endl;
             cout << "3.通过课程ID查询课程名 " << endl;
             cout << "4.通过课程名查询课程ID" << endl;
             cout << "5.通过课程ID查询选修了该课程的学生以及成绩" << endl;
             cout << "6.通过学生ID查询该学生选修的课程信息 " << endl;
             scanf("%1d", &nSet);
             fflush(stdin);
             switch (nSet)
             {
             case 1:
                 cout << "请输入学生ID查询学生姓名" << endl;
                 scanf("%10d",&n);
                 fflush(stdin);
                 if (data.searchStuID(n, szTemName, stuIDtoNameTree)==true)
                 {
                     cout << "学生姓名:" << szTemName << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "没有找到学生姓名"  << endl;
                     system("pause");
                 }
                 
                 break;
             case 2:
                 cout << "请输入学生姓名查询学生ID" << endl;
                 scanf("%10s", szTemName);
                 fflush(stdin);
                 if (data.searchStuName(arrTemStuID, szTemName, stuNametoIDTree) == true)
                 {
                     int i = 0;
                     while (true)
                     {
                         if (arrTemStuID[i] != 0)
                         {
                             cout << "学号:" << arrTemStuID[i] << endl;
                             i++;
                             
                         }
                         else
                         {
                             system("pause");
                             break;
                         }
                     }
                     
                 }
                 else
                 {
                     cout << "没有找到对应名字的学号" << endl;
                     system("pause");
                 }
                 break;
             case 3:
                 
                 cout << "请输入课程ID查询课程名" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.searchCourID(n, szTemName, courIDtoNameTree) == true)
                 {
                     cout << "课程姓名:" << szTemName << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "没有找到课程姓名" << endl;
                     system("pause");
                 }
                 break;
             case 4:            
                 cout << "请输入课程名查询课程ID" << endl;
                 scanf("%10s", szTemName);
                 fflush(stdin);
                 if (data.searchCourName(arrTemStuID, szTemName, courNametoIDTree) == true)
                 {
                     int i = 0;
                     while (true)
                     {
                         if (arrTemStuID[i] != 0)
                         {
                             cout << "课程id:" << arrTemStuID[i] << endl;
                             i++;
                             system("pause");
                         }
                         else
                         {
                             break;
                         }
                     }

                 }
                 else
                 {
                     cout << "没有找到对应课程id" << endl;
                     system("pause");
                 }
                 break;
             case 5:              
                 cout << "请输入课程ID查询选修了该课程的学生以及成绩" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.searchRecCourID(n,RecId,RecCourIDTree)==true)
                 {
                     int i = 0;
                     while (true)
                     {
                         if (RecId[i].nStuID != 0)
                         {
                             char szTempStuName[100] = "";
                             data.searchStuID(RecId[i].nStuID, szTempStuName, stuIDtoNameTree);
                             char szTempCourName[100] = "";
                             data.searchCourID(RecId[i].nCourseID, szTempCourName, courIDtoNameTree);
                             cout << "学生id:\t" << RecId[i].nStuID << "\t" << "学生名字\t" << szTempStuName << "\t" << "课程id:\t" 
                                 << RecId[i].nCourseID << "\t" << "课程名字:\t" << szTempCourName << "\t" << "成绩:\t" << RecId[i].nScore << "\t" << endl;
                             i++;
                             
                         }
                         else
                         {
                             system("pause");
                             break;
                         }
                     }

                 }
                 else
                 {
                     cout << "没有选修该门课程的学生" << endl;
                     system("pause");
                 }
                 break;
             case 6:
                 cout << "请输入学生ID查询学生选修的课程信息" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.searchRecStuID(n, RecId, RecStuIDTree) == true)
                 {
                     int i = 0;
                     while (true)
                     {
                         if (RecId[i].nStuID != 0)
                         {
                             char szTempStuName[100] = "";
                             data.searchStuID(RecId[i].nStuID, szTempStuName, stuIDtoNameTree);
                             char szTempCourName[100] = "";
                             data.searchCourID(RecId[i].nCourseID, szTempCourName, courIDtoNameTree);
                             cout << "学生id:\t" << RecId[i].nStuID << "\t" << "学生名字\t" << szTempStuName << "\t" << "课程id:\t"
                                 << RecId[i].nCourseID << "\t" << "课程名字:\t" << szTempCourName << "\t" << "成绩:\t" << RecId[i].nScore << "\t" << endl;
                             i++;
                             
                         }
                         else
                         {
                             system("pause");
                             break;
                         }
                     }

                 }
                 else
                 {
                     cout << "没有这个学生" << endl;
                     system("pause");
                 }
                 break;
             default:
                 break;
             }
             break;
         case 5:
             exit(0);
             break;
         default:
             break;
         }
     }
	return 0;
}

int menu()
{
    int nChoice = 0;

    system("cls");
    printf("=====================================================\r\n");
    printf("=================       菜单选项      ================\r\n");
    printf("=                0.遍历检查                          =\r\n");
    printf("=                1.插入                             =\r\n");
    printf("=                2.删除                             =\r\n");
    printf("=                3.统计                             =\r\n");
    printf("=                4.查询                             =\r\n");
    printf("=                5.退出                             =\r\n");
    printf("=====================================================\r\n");
    printf("请输入功能选项:(0-8)\r\n");
    scanf("%1d", &nChoice);
    fflush(stdin);

    while (nChoice < -1 || nChoice > 10)
    {
        printf("输入范围为1~7:");
        scanf("%1d", &nChoice);
        fflush(stdin);

    }

    return nChoice;

}

// void ReadSTuFile()  //读学生文件到二叉树
// {
//     CStudent stu;
//     CMyTree Tree;
//     FILE *fp = fopen("students.txt", "r+");
//     if (fp == NULL)
//     {
//         //system("cls");
//         printf("文件无法使用，系统即将退出\n");
//         exit(-1);
//     }
//     rewind(fp);
//     while (fread(&stu, sizeof(stu), 1, fp) == 1)
//     {
// 
//         if (stu.nID != 0)
//         {
//             Tree.InsertStuID(stu);
//         }
//     }
//     fclose(fp);
//     fp = NULL;
//     if (fp != NULL)
//     {
//         fp = NULL;
//     }
// }
// 