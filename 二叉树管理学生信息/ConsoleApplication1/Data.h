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
    //����
    bool AddStu(CMyTree& stuIDtoNmae, CMyTree& stuNametoID)//����ѧ����Ϣ
    {
        char szBuff[10] = "";
        int nTmp = 0;
        CStudent IDtoNmae;
        CStudent NametoID;

        cout << "������ѧ��Id, ����" << endl;
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

    bool AddCour(CMyTree& courIDtoName, CMyTree& courNametoID/*, CMyTree&RecCourIDTree*/)//���ӿγ���Ϣ
    {
        char szBuff[10] = "";
        int nTmp = 0;
        CCourseInformation IDtoNmae;
        CCourseInformation NametoID;

        cout << "������γ�Id, �γ�����" << endl;
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

    bool AddRec(CMyTree& stuIDRectree, CMyTree& courIDRectree, CMyTree& courIDtree, CMyTree& StuIDtree)//����ѡ�μ�¼
    {

        int nScore = 0;//����
        int nStuID = 0;//ѧ��id
        int nCourID = 0;//�γ�id

        CRecord stuID;
        CRecord courID;
        CCourseInformation courIDtoName;
        CStudent stuIDtoName;

        cout << "������ѧ��id,�γ�Id, ����" << endl;
        scanf("%d %d %d", &nStuID, &nCourID,&nScore);
        fflush(stdin);

        stuIDtoName.nID = nStuID;
        courIDtoName.nCourseID = nCourID;
        
        //���ѧ�źͿγ�id�����Ƿ���Ч
        if (nStuID<0||nCourID<0)
        {
            return false;
        }
        //��� ѧ����Ϣ.txt����ѧ��id��û�����޷�����
        if (StuIDtree.findStuID(stuIDtoName)==nullptr)
        {

            return false;
        }

        //��� �γ���Ϣ.txt���޿γ�id��û�����޷�����
        if (courIDtree.findCourID(courIDtoName) == nullptr)
        {
            return false;
        }

        //������  0--100��
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
        //����ѧ��id��ѧ���������γ�id���γ����֣�����
        char szBuf[100];
        sprintf(szBuf, "%d-%d-%d\n", nStuID, nCourID, nScore);
        ofstream file1;
        file1.open("xuanke.txt", ios::app);
        file1 << szBuf;
        file1.close();
        return true;

    }

    //����
    bool searchStuID(int n, char* szname,CMyTree& IDtoNmaeTree)//ID��ѧ������
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

    bool searchStuName(int* arrStuID,char*szBuff, CMyTree& NmaetoIDTree)//ѧ����������id
    {
        CStudent NametoID;
        strcpy(NametoID.szName, szBuff);
        int i = 0;
        CMyTreeNode* p = NmaetoIDTree.findStuName(NametoID);
        if (p != nullptr)
        {
            //����ͬ�� ������id,ֱ��û��Ϊֹ,������0����
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

    bool searchCourID(int n, char* szname, CMyTree& IDtoNmaeTree)//�γ�id�ҿγ���
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

    bool searchCourName(int* arrStuID, char*szBuff, CMyTree& NmaetoIDTree)//�γ����ҿγ�id
    {
        CCourseInformation NametoID;
        strcpy(NametoID.szCourseName, szBuff);
        int i = 0;
        CMyTreeNode* p = NmaetoIDTree.findCourName(NametoID);
        if (p != nullptr)
        {
            //����ͬ�� ������id,ֱ��û��Ϊֹ,������0����
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

    bool searchRecCourID(int n, CRecord*ArrStu , CMyTree& IDtoNmaeTree)//ѡ�μ�¼�ÿγ�id��ѯ
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
    bool searchRecStuID(int n, CRecord*ArrStu, CMyTree& IDtoNmaeTree)//ѡ�μ�¼��ѧ��id��ѯ
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

    //ɾ��
    bool deleteStu(int n, CMyTree& stuIDtoNmae, CMyTree& stuNmaetoID)
    {
        char szStuName[20] = "";//���ҵ�ѧ��������ʱ�洢
        int nStuIDlen = 0;//ѧ����Ϣ����
        
        CStudent IDtoName;
        CStudent NametoID;

        //ѧ��С�ڵ���0
        if (n<=0)
        {
            return false;
        }
        IDtoName.nID = n;
        CMyTreeNode* p = stuIDtoNmae.findStuID(IDtoName);//��������Ҵ������ѧ��id�ڵ�
        if (p != nullptr)
        {
            int k = 0;
            //���ѧ������
            strcpy(szStuName, p->data.szName);
            strcpy(IDtoName.szName, szStuName);
            strcpy(NametoID.szName, szStuName);
            //���ѧ��id���е�����
            nStuIDlen = p->data.nLine;//��ȡ����ѧ����Ϣ��ǰ�����ļ�������

            while (true)
            {
                cout << "��Ҫɾ����ѧ����Ϣ�ǣ�" << endl;
                cout << "ѧ��:" << IDtoName.nID << "ѧ������" << IDtoName.szName << endl;
                cout << "1.ȷ��ɾ��" << "2.�˳�" << endl;
                scanf("%1d", &k);
                fflush(stdin);
                if (1 == k)
                {
                    int ndID = 0;//ɾ����ѧ��Ϊ0
                    char szDTem[10]="";//ɾ����ѧ������Ϊ0
                    char szTem[100] = "";//��ȡ�ļ�ÿ�еĻ�����

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
                    ��������������seekg������tellg����
                    �������������seekp������tellp����
                    tellg������������Ҫ�������������ص�ǰ��λָ���λ�ã�Ҳ�������������Ĵ�С��
                    seekg�����Ƕ������ļ���λ������������������һ��������ƫ�������ڶ��������ǻ���ַ��
                    */////////////////////////////////////////////////////////////////////////
                    fileStu.seekg(nPos);
                    fileStu << "0-00000000000";
                    /*fileStu <<"0 - 0 \n";*/
                    fileStu.close();
                    //ɾ��ѧ��id������Ϣ
                    stuIDtoNmae.DeleteStuID(IDtoName);
                    stuNmaetoID.DeleteStuName(NametoID);
                    return true;
                }
                else if (2 == k)
                {
                    break;
                }
                else{
                    cout << "�����������������" << endl;
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
        char szCourName[20] = "";//���ҵĿγ�����ʱ�洢
        int nCourIDlen = 0;//�γ���Ϣ����

        CCourseInformation IDtoName;
        CCourseInformation NametoID;

        //ѧ��С�ڵ���0
        if (n <= 0)
        {
            return false;
        }
        IDtoName.nCourseID = n;
        CMyTreeNode* p = courIDtoNmae.findCourID(IDtoName);//��������Ҵ�������γ�id�ڵ�
        if (p != nullptr)
        {
            int k = 0;
            //��ÿγ�����
            strcpy(szCourName, p->Cdata.szCourseName);
            strcpy(IDtoName.szCourseName, szCourName);         
            strcpy(NametoID.szCourseName, szCourName);
            //��ÿγ�id���е�����
            nCourIDlen = p->Cdata.nLine;//��ȡ�����γ���Ϣ��ǰ�����ļ�������

            while (true)
            {
                cout << "��Ҫɾ���Ŀγ���Ϣ�ǣ�" << endl;
                cout << "�γ�id:" << IDtoName.nCourseID << "�γ�����" << IDtoName.szCourseName << endl;
                cout << "1.ȷ��ɾ��" << "2.�˳�" << endl;
                scanf("%1d", &k);
                fflush(stdin);
                if (1 == k)
                {
                    int ndID = 0;//ɾ����ѧ��Ϊ0
                    char szDTem[10] = "";//ɾ����ѧ������Ϊ0
                    char szTem[100] = "";//��ȡ�ļ�ÿ�еĻ�����

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
                    ��������������seekg������tellg����
                    �������������seekp������tellp����
                    tellg������������Ҫ�������������ص�ǰ��λָ���λ�ã�Ҳ�������������Ĵ�С��
                    seekg�����Ƕ������ļ���λ������������������һ��������ƫ�������ڶ��������ǻ���ַ��
                    */////////////////////////////////////////////////////////////////////////
                    fileStu.seekg(nPos);
                    fileStu << "0-00000000000";
                    fileStu.close();
                    //ɾ��ѧ��id������Ϣ
                    courIDtoNmae.DeleteCourID(IDtoName);
                    courNmaetoID.DeleteCourName(NametoID);
                    return true;
                }
                else if (2 == k)
                {
                    break;
                }
                else{
                    cout << "�����������������" << endl;
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
        char szRecName[20] = "";//���ҵĿγ�����ʱ�洢
        int nRecIDlen = 0;//�γ���Ϣ����

        CRecord IDtoName;
        CRecord NametoID;

        //ѧ��С�ڵ���0
        if (n <= 0)
        {
            return false;
        }
        IDtoName.nStuID = n;
        CMyTreeNode* p = RecIDtoNmae.findRecStuID(IDtoName);//��������Ҵ������ѧ��id�ڵ�
        if (p != nullptr)
        {
            int k = 0;
            //             //��ÿγ�����
            //             strcpy(szCourName, p->Rdata.nStuID);
            //             strcpy(IDtoName.szCourseName, szCourName);
            //���ѧ��id���е�����
            nRecIDlen = p->Rdata.nLine;//��ȡ����ѧ����Ϣ��ǰ�����ļ�������
            IDtoName.nCourseID = p->Rdata.nCourseID;
            NametoID.nCourseID = p->Rdata.nCourseID;
            IDtoName.nScore = p->Rdata.nScore;
            while (true)
            {
                cout << "��Ҫɾ����ѡ�μ�¼�ǣ�" << endl;
                cout << "ѧ��id:" << IDtoName.nStuID << "�γ�id:" << IDtoName.nCourseID << "�ɼ�" << IDtoName.nScore << endl;
                cout << "1.ȷ��ɾ��" << "2.�˳�" << endl;
                scanf("%1d", &k);
                fflush(stdin);
                if (1 == k)
                {
                    int nStuID = 0;//ɾ����ѧ��Ϊ0
                    int nCourID = 0;//ɾ���Ŀγ�idΪ0
                    int nScore = 0;//ɾ���ķ���
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
                    ��������������seekg������tellg����
                    �������������seekp������tellp����
                    tellg������������Ҫ�������������ص�ǰ��λָ���λ�ã�Ҳ�������������Ĵ�С��
                    seekg�����Ƕ������ļ���λ������������������һ��������ƫ�������ڶ��������ǻ���ַ��
                    */////////////////////////////////////////////////////////////////////////
                    fileStu.seekg(nPos);
                    fileStu << "0-00000000000";
                    fileStu.close();
                    //ɾ��ѧ��id������Ϣ
                    RecIDtoNmae.DeleteRecStuID(IDtoName);
                    RecNmaetoID.DeleteRecCourID(IDtoName);
                    return true;
                }
                else if (2 == k)
                {
                    break;
                }
                else{
                    cout << "�����������������" << endl;
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
        int nStuID = 0;//ѧ��
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
                printf("�ļ��޷�ʹ�ã�ϵͳ�����˳�\n");
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
            printf("�ļ��޷�ʹ�ã�ϵͳ�����˳�\n");
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




