#pragma once

#include <iostream>
#include <fstream>
#include "MyTree.h"

#define  T 100000
using namespace std;
class CData
{
public:
    CData(){};
    ~CData(){};
    //增加
    bool AddStu(CMyTree& stuIDtoNmae, CMyTree& stuNametoID)//增加学生信息
    {
        char szBuff[10] = "";
        int nTmp = 0;
        CStudent IDtoNmae;
        CStudent NametoID;

        cout << "请输入学生Id, 姓名" << endl;
        scanf("%d %10s", &nTmp, szBuff);
        fflush(stdin);

        IDtoNmae.nID = nTmp;
        strcpy(IDtoNmae.szName, szBuff);
        NametoID.nID = nTmp;
        strcpy(NametoID.szName, szBuff);

        if (stuIDtoNmae.findStuID(IDtoNmae) != nullptr)
        {
            return false;
        }
        else
        {
            stuIDtoNmae.InsertStuID(IDtoNmae);
            stuNametoID.InsertStuName(NametoID);
        }
        char szBuf[100];
        sprintf(szBuf, "%d-%s\n", nTmp, szBuff);
        ofstream file1;
        file1.open("stu.txt", ios::app);
        file1 << szBuf;
        file1.close();
        return true;
    }

    bool AddCour(CMyTree& courIDtoName, CMyTree& courNametoID/*, CMyTree&RecCourIDTree*/)//增加课程信息
    {
        char szBuff[10] = "";
        int nTmp = 0;
        CCourseInformation IDtoNmae;
        CCourseInformation NametoID;

        cout << "请输入课程Id, 课程名字" << endl;
        scanf("%d %10s", &nTmp, szBuff);
        fflush(stdin);

        IDtoNmae.nCourseID = nTmp;
        strcpy(IDtoNmae.szCourseName, szBuff);
        NametoID.nCourseID = nTmp;
        strcpy(NametoID.szCourseName, szBuff);

        if (courIDtoName.findCourID(IDtoNmae) != nullptr)
        {
            return false;
        }
        else
        {
            courIDtoName.InsertCourID(IDtoNmae);
            courNametoID.InsertCourName(NametoID);
            //RecCourIDTree.InsertRecCourId(IDtoNmae);
        }
        char szBuf[100];
        sprintf(szBuf, "%d-%s\n", nTmp, szBuff);
        ofstream file1;
        file1.open("lesson.txt", ios::app);
        file1 << szBuf;
        file1.close();
        return true;
    }

    bool AddRec(CMyTree& stuIDRectree, CMyTree& courIDRectree, CMyTree& courIDtree, CMyTree& StuIDtree)//增加选课记录
    {

        int nScore = 0;//分数
        int nStuID = 0;//学生id
        int nCourID = 0;//课程id

        CRecord stuID;
        CRecord courID;
        CCourseInformation courIDtoName;
        CStudent stuIDtoName;

        cout << "请输入学生id,课程Id, 分数" << endl;
        scanf("%d %d %d", &nStuID, &nCourID,&nScore);
        fflush(stdin);

        stuIDtoName.nID = nStuID;
        courIDtoName.nCourseID = nCourID;
        
        //检测学号和课程id输入是否有效
        if (nStuID<0||nCourID<0)
        {
            return false;
        }
        //检测 学生信息.txt有无学生id，没有则无法生成
        if (StuIDtree.findStuID(stuIDtoName)==nullptr)
        {

            return false;
        }

        //检测 课程信息.txt有无课程id，没有则无法生成
        if (courIDtree.findCourID(courIDtoName) == nullptr)
        {
            return false;
        }

        //检测分数  0--100；
        if (nScore<0 || nScore>100)
        {
            return false;
        }

        
        courID.nCourseID = nCourID;
        courID.nStuID = nStuID;
        courID.nScore = nScore;

        stuID.nStuID = nStuID;
        stuID.nCourseID = nCourID;
        stuID.nScore = nScore;

        if ((stuIDRectree.findRecStuID(stuID) == nullptr) && (courIDRectree.findRecCourID(courID) == nullptr))
        {
            stuIDRectree.InsertRecStuId(stuID);
            courIDRectree.InsertRecCourId(courID);
        }
        else 
        {
            return false;
        }
        //插入学生id，学生姓名，课程id，课程名字，分数
        char szBuf[100];
        sprintf(szBuf, "%d-%d-%d\n", nStuID, nCourID, nScore);
        ofstream file1;
        file1.open("xuanke.txt", ios::app);
        file1 << szBuf;
        file1.close();
        return true;

    }

    //查找
    bool searchStuID(int n, char* szname,CMyTree& IDtoNmaeTree)//ID查学生姓名
    {
        CStudent IDtoNmae;
        IDtoNmae.nID = n;
        CMyTreeNode* p=IDtoNmaeTree.findStuID(IDtoNmae);
        if (p!=nullptr)
        {
            strcpy(szname, p->data.szName);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool searchStuName(int* arrStuID,char*szBuff, CMyTree& NmaetoIDTree)//学生姓名查找id
    {
        CStudent NametoID;
        strcpy(NametoID.szName, szBuff);
        int i = 0;
        CMyTreeNode* p = NmaetoIDTree.findStuName(NametoID);
        if (p != nullptr)
        {
            //查找同名 的所有id,直到没有为止,数组以0结束
            while (p!=nullptr)
            { 
                arrStuID[i] = p->data.nID;
                i++;
                p = p->pList;
            }
            arrStuID[i] = 0;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool searchCourID(int n, char* szname, CMyTree& IDtoNmaeTree)//课程id找课程名
    {
        CCourseInformation IDtoNmae;
        IDtoNmae.nCourseID = n;
        CMyTreeNode* p = IDtoNmaeTree.findCourID(IDtoNmae);
        if (p != nullptr)
        {
            strcpy(szname, p->Cdata.szCourseName);
            return true;
        }
        else
        {
            return false;
        }
    
    }

    bool searchCourName(int* arrStuID, char*szBuff, CMyTree& NmaetoIDTree)//课程名找课程id
    {
        CCourseInformation NametoID;
        strcpy(NametoID.szCourseName, szBuff);
        int i = 0;
        CMyTreeNode* p = NmaetoIDTree.findCourName(NametoID);
        if (p != nullptr)
        {
            //查找同名 的所有id,直到没有为止,数组以0结束
            while (p != nullptr)
            {
                arrStuID[i] = p->Cdata.nCourseID;
                i++;
                p = p->pList;
            }
            arrStuID[i] = 0;
            return true;
        }
        else
        {
            return false;
        }
    
    }

    bool searchRecCourID(int n, CRecord*ArrStu , CMyTree& IDtoNmaeTree)//选课记录用课程id查询
    {
        CRecord IDtoNmae;
        IDtoNmae.nCourseID = n;
        int i = 0;
        CMyTreeNode* p = IDtoNmaeTree.findRecCourID(IDtoNmae);
        if (p != nullptr)
        {
            while (p != nullptr)
            {
                ArrStu[i].nStuID = p->Rdata.nStuID;
                ArrStu[i].nCourseID = p->Rdata.nCourseID;
                ArrStu[i].nScore = p->Rdata.nScore;
                i++;
                p = p->pList;
            }
          
            ArrStu[i].nStuID = 0;
            ArrStu[i].nScore = 0;
            ArrStu[i].nCourseID = 0;
            return true;
        }
        else
        {
            return false;
        }

    }
    bool searchRecStuID(int n, CRecord*ArrStu, CMyTree& IDtoNmaeTree)//选课记录用学生id查询
    {
        CRecord IDtoNmae;
        IDtoNmae.nStuID = n;
        int i = 0;
        CMyTreeNode* p = IDtoNmaeTree.findRecStuID(IDtoNmae);
        if (p != nullptr)
        {
            while (p != nullptr)
            {
                ArrStu[i].nStuID = p->Rdata.nStuID;
                ArrStu[i].nCourseID = p->Rdata.nCourseID;
                ArrStu[i].nScore = p->Rdata.nScore;
                i++;
                p = p->pList;
            }
            ArrStu[i].nStuID = 0;
            ArrStu[i].nScore = 0;
            ArrStu[i].nCourseID = 0;
            return true;
        }
        else
        {
            return false;
        }
    }

    //删除
    bool deleteStu(int n, CMyTree& stuIDtoNmae, CMyTree& stuNmaetoID)
    {
        char szStuName[20] = "";//查找的学生姓名零时存储
        int nStuIDlen = 0;//学生信息行数
        
        CStudent IDtoName;
        CStudent NametoID;

        //学号小于等于0
        if (n<=0)
        {
            return false;
        }
        IDtoName.nID = n;
        CMyTreeNode* p = stuIDtoNmae.findStuID(IDtoName);//在树里查找带有这个学生id节点
        if (p != nullptr)
        {
            int k = 0;
            //获得学生名字
            strcpy(szStuName, p->data.szName);
            strcpy(IDtoName.szName, szStuName);
            strcpy(NametoID.szName, szStuName);
            //获得学生id树中的行数
            nStuIDlen = p->data.nLine;//获取这条学生信息当前所在文件的行数

            while (true)
            {
                cout << "你要删除的学生信息是：" << endl;
                cout << "学号:" << IDtoName.nID << "学生姓名" << IDtoName.szName << endl;
                cout << "1.确认删除" << "2.退出" << endl;
                scanf("%1d", &k);
                fflush(stdin);
                if (1 == k)
                {
                    int ndID = 0;//删除的学号为0
                    char szDTem[10]="";//删除的学生名字为0
                    char szTem[100] = "";//读取文件每行的缓冲区

                    memset(szDTem,' ',sizeof(IDtoName.szName));
                    
                    fstream fileStu;
                    fileStu.open("stu.txt", ios::in | ios::out);
                    char szBuf[100];
                    sprintf(szBuf, "%d-%s", ndID, ndID);

                    std::streampos nPos = 0;
                    for (int i = 1; i < nStuIDlen;i++)
                    {
                        fileStu.getline(szTem, sizeof(szTem),'\n');
                        nPos = fileStu.tellg();
                    }
                    /*////////////////////////////////////////////////////////////////////////
                    对输入流操作：seekg（）与tellg（）
                    对输出流操作：seekp（）与tellp（）
                    tellg（）函数不需要带参数，它返回当前定位指针的位置，也代表着输入流的大小。
                    seekg（）是对输入文件定位，它有两个参数：第一个参数是偏移量，第二个参数是基地址。
                    */////////////////////////////////////////////////////////////////////////
                    fileStu.seekg(nPos);
                    fileStu << "0-00000000000";
                    /*fileStu <<"0 - 0 \n";*/
                    fileStu.close();
                    //删除学生id树的信息
                    stuIDtoNmae.DeleteStuID(IDtoName);
                    stuNmaetoID.DeleteStuName(NametoID);
                    return true;
                }
                else if (2 == k)
                {
                    break;
                }
                else{
                    cout << "输入错误，请重新输入" << endl;
                    break;
                }
            }
        }
        else
        {
            return false;
        }
}

    bool deleteCour(int n, CMyTree& courIDtoNmae, CMyTree& courNmaetoID)
    {
        char szCourName[20] = "";//查找的课程名零时存储
        int nCourIDlen = 0;//课程信息行数

        CCourseInformation IDtoName;
        CCourseInformation NametoID;

        //学号小于等于0
        if (n <= 0)
        {
            return false;
        }
        IDtoName.nCourseID = n;
        CMyTreeNode* p = courIDtoNmae.findCourID(IDtoName);//在树里查找带有这个课程id节点
        if (p != nullptr)
        {
            int k = 0;
            //获得课程名字
            strcpy(szCourName, p->Cdata.szCourseName);
            strcpy(IDtoName.szCourseName, szCourName);         
            strcpy(NametoID.szCourseName, szCourName);
            //获得课程id树中的行数
            nCourIDlen = p->Cdata.nLine;//获取这条课程信息当前所在文件的行数

            while (true)
            {
                cout << "你要删除的课程信息是：" << endl;
                cout << "课程id:" << IDtoName.nCourseID << "课程名字" << IDtoName.szCourseName << endl;
                cout << "1.确认删除" << "2.退出" << endl;
                scanf("%1d", &k);
                fflush(stdin);
                if (1 == k)
                {
                    int ndID = 0;//删除的学号为0
                    char szDTem[10] = "";//删除的学生名字为0
                    char szTem[100] = "";//读取文件每行的缓冲区

                    fstream fileStu;
                    fileStu.open("lesson.txt", ios::in | ios::out);
                    char szBuf[100];
                    sprintf(szBuf, "%d-%s\n", ndID, szDTem);

                    std::streampos nPos = 0;
                    for (int i = 1; i < nCourIDlen; i++)
                    {
                        fileStu.getline(szTem, sizeof(szTem));
                        nPos = fileStu.tellg();
                    }
                    /*////////////////////////////////////////////////////////////////////////
                    对输入流操作：seekg（）与tellg（）
                    对输出流操作：seekp（）与tellp（）
                    tellg（）函数不需要带参数，它返回当前定位指针的位置，也代表着输入流的大小。
                    seekg（）是对输入文件定位，它有两个参数：第一个参数是偏移量，第二个参数是基地址。
                    */////////////////////////////////////////////////////////////////////////
                    fileStu.seekg(nPos);
                    fileStu << "0-00000000000";
                    fileStu.close();
                    //删除学生id树的信息
                    courIDtoNmae.DeleteCourID(IDtoName);
                    courNmaetoID.DeleteCourName(NametoID);
                    return true;
                }
                else if (2 == k)
                {
                    break;
                }
                else{
                    cout << "输入错误，请重新输入" << endl;
                    break;
                }
            }
        }
        else
        {
            return false;
        }
    }

    bool deleteRec(int n, CMyTree& RecIDtoNmae, CMyTree& RecNmaetoID)
    {
        char szRecName[20] = "";//查找的课程名零时存储
        int nRecIDlen = 0;//课程信息行数

        CRecord IDtoName;
        CRecord NametoID;

        //学号小于等于0
        if (n <= 0)
        {
            return false;
        }
        IDtoName.nStuID = n;
        CMyTreeNode* p = RecIDtoNmae.findRecStuID(IDtoName);//在树里查找带有这个学生id节点
        if (p != nullptr)
        {
            int k = 0;
            //             //获得课程名字
            //             strcpy(szCourName, p->Rdata.nStuID);
            //             strcpy(IDtoName.szCourseName, szCourName);
            //获得学生id树中的行数
            nRecIDlen = p->Rdata.nLine;//获取这条学生信息当前所在文件的行数
            IDtoName.nCourseID = p->Rdata.nCourseID;
            NametoID.nCourseID = p->Rdata.nCourseID;
            IDtoName.nScore = p->Rdata.nScore;
            while (true)
            {
                cout << "你要删除的选课记录是：" << endl;
                cout << "学生id:" << IDtoName.nStuID << "课程id:" << IDtoName.nCourseID << "成绩" << IDtoName.nScore << endl;
                cout << "1.确认删除" << "2.退出" << endl;
                scanf("%1d", &k);
                fflush(stdin);
                if (1 == k)
                {
                    int nStuID = 0;//删除的学号为0
                    int nCourID = 0;//删除的课程id为0
                    int nScore = 0;//删除的分数
                    char szTem[100] = "";
                    fstream fileStu;
                    fileStu.open("xuanke.txt", ios::in | ios::out);
                    char szBuf[100];
                    sprintf(szBuf, "%d-%d-%d\n", nStuID, nCourID, nScore);

                    std::streampos nPos = 0;
                    for (int i = 1; i < nRecIDlen; i++)
                    {
                        fileStu.getline(szTem, sizeof(szTem));
                        nPos = fileStu.tellg();
                    }
                    /*////////////////////////////////////////////////////////////////////////
                    对输入流操作：seekg（）与tellg（）
                    对输出流操作：seekp（）与tellp（）
                    tellg（）函数不需要带参数，它返回当前定位指针的位置，也代表着输入流的大小。
                    seekg（）是对输入文件定位，它有两个参数：第一个参数是偏移量，第二个参数是基地址。
                    */////////////////////////////////////////////////////////////////////////
                    fileStu.seekg(nPos);
                    fileStu << "0-00000000000";
                    fileStu.close();
                    //删除学生id树的信息
                    RecIDtoNmae.DeleteRecStuID(IDtoName);
                    RecNmaetoID.DeleteRecCourID(IDtoName);
                    return true;
                }
                else if (2 == k)
                {
                    break;
                }
                else{
                    cout << "输入错误，请重新输入" << endl;
                    break;
                }
            }
        }
        else
        {
            return false;
        }
    }

   

    void Studata(){
        int nStuID = 0;//学号
        char szName[10];

        for (int i = 0; i < 10; i++)
        {
            nStuID = i;
            int k = rand() % 3 + 2;

            for (int j = 0; j < k; j++){
                szName[j] = rand() % 24 + 97;

            }
            szName[k] = '\0';
            CStudent*p = new CStudent;
            p->nID = nStuID;
            memmove((void*)p->szName, (void*)szName, sizeof(szName));
            FILE*fp = fopen("Studata.bin", "a+b");
            if (fp = NULL){
                system("cls");
                printf("文件无法使用，系统即将退出\n");
                exit(-1);
            };

            fwrite(p, sizeof(CStudent), 1, fp);
            fclose(fp);
            fp = NULL;
        }

    }

    void ReadStuData(){
        FILE*fp = fopen("Studata.bin", "rb");
        if (fp == NULL){
            system("cls");
            printf("文件无法使用，系统即将退出\n");
            exit(-1);
        }
        rewind(fp);
        while (true)
        {
            CStudent*p = (CStudent*)malloc(sizeof(CStudent));
            fread(p, sizeof(CStudent), 1, fp);
        }
        //printf("%d--%s\n", p->nID, p->szName);
        //CStudent*p1 = p + 1;
        //printf("%d--%s\n", p1->nID, p1->szName);
        fclose(fp);
        fp = NULL;
    }
};




