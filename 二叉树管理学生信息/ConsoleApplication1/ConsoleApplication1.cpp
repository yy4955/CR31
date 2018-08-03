// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//1.ѡ����Ϣ�Ĳ���,2.���Һ�������ͬ������ô����,3.���Ҷ���Ϊ��,��ô����

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "MyTree.h"
#include "Data.h"

using namespace std;
//���ļ�

int menu();

//д���ļ�
int _tmain(int argc, _TCHAR* argv[])
{
    /*
    1.�ȶ��ļ�,�ر��ļ�
    2.�����ڶ������в���,�򿪹ر�
    3.
    */
    CData data;
    CStudent stuIDtoName;
    CStudent stuNametoID;

    CCourseInformation courIDtoName;
    CCourseInformation courNametoID;

    CRecord RecStuID;
    CRecord RecCourID;

    //6����
    CMyTree stuIDtoNameTree;
    CMyTree stuNametoIDTree;

    CMyTree courIDtoNameTree;
    CMyTree courNametoIDTree;

    CMyTree RecStuIDTree;
    CMyTree RecCourIDTree;

    char szBuff[100] = "";
    int nStuline = 0;//ѧ���ı�����ͳ��
    int nCourline = 0;//�γ���Ϣ�ı�����ͳ��
    int nRecline = 0;//ѡ����Ϣ�ı�����ͳ��

    ifstream fileStu;
    //stu  ѧ����Ϣ

    //stringstream buffer;
    //string s;
    //fileStu.open("stu.txt", ios::in);//���ļ���
    fileStu.open("stu.txt",ios::in);//���ļ���
    while (!fileStu.eof())
    {
        if (fileStu.eof())//�ж��Ƿ񵽽�β�����ж�һ��Ҫ�ŵ�push_backǰ��
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
    cout << "ѧ�����ȡ���" << endl;

    //��ȡ�γ���Ϣ
    ifstream fileCour;
    //lesson  �γ���Ϣ
    fileCour.open("lesson.txt", ios::in);//���ļ���
    while (!fileCour.eof())
    {
        if (fileCour.eof())//�ж��Ƿ񵽽�β�����ж�һ��Ҫ�ŵ�push_backǰ��
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
    cout << "�γ���Ϣ���ȡ���" << endl;

    //��ȡѡ�μ�¼
    ifstream fileRec;
    //xuanke  ѡ�μ�¼
    fileRec.open("xuanke.txt", ios::in);//���ļ���
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
    cout << "ѡ�μ�¼��ȡ���" << endl;

    //����˵���
     while (true)
     {
         int nSet = 0;//��ѡ��
         int n = 0;//ѧ��,�γ�id��ʱ����
         char szTemName[100] = "";//������ʱ
         int arrTemStuID[1000] = {0};//ѧ����ʱ
         CRecord RecId[1000] ;//ѡ�μ�¼��Ϣ
         memset(RecId, 0, sizeof(RecId));

         switch (menu())
         {
         case 0:
             cout << "1.����ѧ����Ϣ" << endl;
             cout << "2.�����γ���Ϣ" << endl;
             cout << "3.����ѡ�μ�¼" << endl;
            // cout << "4.��������" << endl;
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
         case 1://����
             cout << "1.����ѧ��(ID, ����)"<< endl;
             cout << "2.�����γ�(ID, ����)" << endl;
             cout << "3.����ѡ�μ�¼(ѧ��ID, �γ�ID, ����)" << endl;
             scanf("%1d",&nSet);
             fflush(stdin);
             switch (nSet)
             {
             case 1:            
                 if (data.AddStu(stuIDtoNameTree, stuNametoIDTree)==true)
                 {
                     cout << "���ӳɹ�" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "����ʧ��" << endl;
                     system("pause");
                 }
                 break;
             case 2:
                 
                 if (data.AddCour(courIDtoNameTree, courNametoIDTree) == true)
                     {
                         cout << "���ӳɹ�" << endl;
                         system("pause");
                     }
                     else
                     {
                         cout << "����ʧ��" << endl;
                         system("pause");
                     }
                 break;
             case 3:
                 if (data.AddRec(RecStuIDTree, RecCourIDTree,courIDtoNameTree,stuIDtoNameTree)==true)
                 {
                     cout << "���ӳɹ�" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "����ʧ��" << endl;
                     system("pause");
                 }
                 break;
             default:
                 break;
             }
             break;
         case 2:
             cout << "1.ɾ��ѧ��(ID, ����)" << endl;
             cout << "2.ɾ���γ�(ID, ����)" << endl;
             cout << "3.ɾ��ѡ�μ�¼(ѧ��ID, �γ�ID, ����)" << endl;
             scanf("%1d", &nSet);
             fflush(stdin);
             switch (nSet)
             {
             case 1:           
                 cout << "����ɾ����ѧ��ID" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.deleteStu(n, stuIDtoNameTree,stuNametoIDTree)==true)
                 {
                     cout << "ɾ���ɹ�" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "ɾ��ʧ��" << endl;
                     system("pause");
                 }
                 break;
             case 2:
                 cout << "������ɾ���γ�(ID)" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.deleteCour(n, courIDtoNameTree,courNametoIDTree) == true)
                 {
                     cout << "ɾ���ɹ�" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "ɾ��ʧ��" << endl;
                     system("pause");
                 }               
                 break;
             case 3:
                 cout << "������ɾ��ѡ�μ�¼��ѧ��ID" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.deleteRec(n, RecStuIDTree,RecCourIDTree) == true)
                 {
                     cout << "ɾ���ɹ�" << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "ɾ��ʧ��" << endl;
                     system("pause");
                 }
             default:
                 break;
             }
             break;
         case 3://ͳ��
             cout << "1.ͳ��ѡ�� xx �γ̵�ѧ���������"<< endl;
             scanf("%1d", &nSet);
             fflush(stdin);
             switch (nSet)
             {
             case 1:
                 cout << "1.��������Ҫͳ�ƵĿγ���" << endl;
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
                             cout << "ѧ��id:" << RecId[i].nStuID << "ѧ������" << szTempStuName << "�γ�id:" << RecId[i].nCourseID << "�γ�����:" << szTempCourName << "�ɼ�:" << RecId[i].nScore << endl;
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
             //                              cout << "ѧ��ID:" << RecId[i].nStuID << "ѧ������" << szTemStuName << "�ɼ�" << RecId[i].nScore << endl;
             //                          }                   
             //                      }                     
             //                  }
         case 4://��ѯ
             cout << "1.ͨ��ѧ��ID��ѯѧ������" << endl;
             cout << "2.ͨ��ѧ��������ѯѧ��ID " << endl;
             cout << "3.ͨ���γ�ID��ѯ�γ��� " << endl;
             cout << "4.ͨ���γ�����ѯ�γ�ID" << endl;
             cout << "5.ͨ���γ�ID��ѯѡ���˸ÿγ̵�ѧ���Լ��ɼ�" << endl;
             cout << "6.ͨ��ѧ��ID��ѯ��ѧ��ѡ�޵Ŀγ���Ϣ " << endl;
             scanf("%1d", &nSet);
             fflush(stdin);
             switch (nSet)
             {
             case 1:
                 cout << "������ѧ��ID��ѯѧ������" << endl;
                 scanf("%10d",&n);
                 fflush(stdin);
                 if (data.searchStuID(n, szTemName, stuIDtoNameTree)==true)
                 {
                     cout << "ѧ������:" << szTemName << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "û���ҵ�ѧ������"  << endl;
                     system("pause");
                 }
                 
                 break;
             case 2:
                 cout << "������ѧ��������ѯѧ��ID" << endl;
                 scanf("%10s", szTemName);
                 fflush(stdin);
                 if (data.searchStuName(arrTemStuID, szTemName, stuNametoIDTree) == true)
                 {
                     int i = 0;
                     while (true)
                     {
                         if (arrTemStuID[i] != 0)
                         {
                             cout << "ѧ��:" << arrTemStuID[i] << endl;
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
                     cout << "û���ҵ���Ӧ���ֵ�ѧ��" << endl;
                     system("pause");
                 }
                 break;
             case 3:
                 
                 cout << "������γ�ID��ѯ�γ���" << endl;
                 scanf("%10d", &n);
                 fflush(stdin);
                 if (data.searchCourID(n, szTemName, courIDtoNameTree) == true)
                 {
                     cout << "�γ�����:" << szTemName << endl;
                     system("pause");
                 }
                 else
                 {
                     cout << "û���ҵ��γ�����" << endl;
                     system("pause");
                 }
                 break;
             case 4:            
                 cout << "������γ�����ѯ�γ�ID" << endl;
                 scanf("%10s", szTemName);
                 fflush(stdin);
                 if (data.searchCourName(arrTemStuID, szTemName, courNametoIDTree) == true)
                 {
                     int i = 0;
                     while (true)
                     {
                         if (arrTemStuID[i] != 0)
                         {
                             cout << "�γ�id:" << arrTemStuID[i] << endl;
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
                     cout << "û���ҵ���Ӧ�γ�id" << endl;
                     system("pause");
                 }
                 break;
             case 5:              
                 cout << "������γ�ID��ѯѡ���˸ÿγ̵�ѧ���Լ��ɼ�" << endl;
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
                             cout << "ѧ��id:\t" << RecId[i].nStuID << "\t" << "ѧ������\t" << szTempStuName << "\t" << "�γ�id:\t" 
                                 << RecId[i].nCourseID << "\t" << "�γ�����:\t" << szTempCourName << "\t" << "�ɼ�:\t" << RecId[i].nScore << "\t" << endl;
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
                     cout << "û��ѡ�޸��ſγ̵�ѧ��" << endl;
                     system("pause");
                 }
                 break;
             case 6:
                 cout << "������ѧ��ID��ѯѧ��ѡ�޵Ŀγ���Ϣ" << endl;
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
                             cout << "ѧ��id:\t" << RecId[i].nStuID << "\t" << "ѧ������\t" << szTempStuName << "\t" << "�γ�id:\t"
                                 << RecId[i].nCourseID << "\t" << "�γ�����:\t" << szTempCourName << "\t" << "�ɼ�:\t" << RecId[i].nScore << "\t" << endl;
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
                     cout << "û�����ѧ��" << endl;
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
    printf("=================       �˵�ѡ��      ================\r\n");
    printf("=                0.�������                          =\r\n");
    printf("=                1.����                             =\r\n");
    printf("=                2.ɾ��                             =\r\n");
    printf("=                3.ͳ��                             =\r\n");
    printf("=                4.��ѯ                             =\r\n");
    printf("=                5.�˳�                             =\r\n");
    printf("=====================================================\r\n");
    printf("�����빦��ѡ��:(0-8)\r\n");
    scanf("%1d", &nChoice);
    fflush(stdin);

    while (nChoice < -1 || nChoice > 10)
    {
        printf("���뷶ΧΪ1~7:");
        scanf("%1d", &nChoice);
        fflush(stdin);

    }

    return nChoice;

}

// void ReadSTuFile()  //��ѧ���ļ���������
// {
//     CStudent stu;
//     CMyTree Tree;
//     FILE *fp = fopen("students.txt", "r+");
//     if (fp == NULL)
//     {
//         //system("cls");
//         printf("�ļ��޷�ʹ�ã�ϵͳ�����˳�\n");
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