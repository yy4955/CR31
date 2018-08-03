#pragma once

#include <assert.h>
#include <iostream>
#include "common.h"
#include "Student.h"
#include "CourseInformation.h"
#include "Record.h"
//#include <algorithm>
//�쳣��
 class CMyException{
 public:
     CMyException(const char* pstr){
         m_ErrStr = pstr;
     }
 
     const char* what(){
         return m_ErrStr.c_str();
     }
 
 private:
     std::string m_ErrStr;
 };


struct CMyTreeNode
{
    CMyTreeNode(CStudent stu){
        data = stu;
        nHeight = 1;
        pParent = NULL;
        pLeft = NULL;
        pRight = NULL;
        pList = NULL;

    }
    CMyTreeNode(CCourseInformation stu)
    {
        Cdata = stu;
        nHeight = 1;
        pParent = NULL;
        pLeft = NULL;
        pRight = NULL;
        pList = NULL;
    }
    CMyTreeNode(CRecord Rec){
        Rdata = Rec;
        nHeight = 1;
        pParent = NULL;
        pLeft = NULL;
        pRight = NULL;
        pList = NULL;
    }
 
    //�߶�
    int nHeight;
    //����
    CStudent data;
    CCourseInformation Cdata;
    CRecord Rdata;
    //���ڵ�
    CMyTreeNode*pParent;
    //�󺢽ڵ�
    CMyTreeNode*pLeft;
    //�ҽڵ�
    CMyTreeNode*pRight;
    CMyTreeNode*pList;

};

class CMyTree  
{
public:
    CMyTree();
    ~CMyTree();

    //����
    bool InsertStuName(CStudent stu);//��ѧ�����ֲ���
    bool InsertStuID(CStudent stu);//��ѧ�Ų���

    bool InsertCourName(CCourseInformation data);//���γ����ֲ���
    bool InsertCourID(CCourseInformation data);//���γ�id����

    bool InsertRecStuId(CRecord Rec);//��ѡ�μ�¼ѧ��id����
    bool InsertRecCourId(CRecord Rec);//��ѡ�μ�¼�γ�id����

    //ɾ��
    bool DeleteStuID(CStudent data);//��ѧ��ɾ��
    bool DeleteStuName(CStudent data);//��ѧ������ɾ��

    bool DeleteCourID(CCourseInformation data);//���γ�idɾ��
    bool DeleteCourName(CCourseInformation data);//���γ�����ɾ��

    bool DeleteRecCourID(CRecord data);//��ѡ�μ�¼�γ�idɾ��
    bool DeleteRecStuID(CRecord data);//��ѡ�μ�¼ѧ��idɾ��
    //��

    CMyTreeNode* findStuName(CStudent stu);//��ѧ����������
    CMyTreeNode* findStuID(CStudent stu);//��ѧ�Ų���

    CMyTreeNode* findCourName(CCourseInformation Courdata);//���γ����ֲ���
    CMyTreeNode* findCourID(CCourseInformation data);//���γ�id����

    CMyTreeNode* findRecCourID(CRecord data);//��ѡ�μ�¼�γ���ID����
    CMyTreeNode* findRecStuID(CRecord data);//��ѡ�μ�¼ѧ��id����
    //4�ֱ���
    //1.�������, ����ʵ��
    void Layer();
    void NameLayer();
    //2.ǰ�����(�ǵݹ�ʵ��)
    void DLR_stc(CMyTreeNode*pNode);
    //3.�������(�ǵݹ�ʵ��)
    void StuLDR_stc(CMyTreeNode*pNode);
    void CourLDR_stc(CMyTreeNode*pNode);
    void RecLDR_stc(CMyTreeNode*pNode);
    void LDR_stc(CMyTreeNode*pNode);
    //4.���������(�ǵݹ�ʵ��)
    void LRD_stc(CMyTreeNode*pNode);


    //������ת
    //1.����
    void LeftRotate(CMyTreeNode*pK1, CMyTreeNode*pK2);
    //2.����
    void RightRotate(CMyTreeNode*pK1, CMyTreeNode*pK2);
    bool StrAdjustHeight(CMyTreeNode* pNode);
    int  GetHeight(CMyTreeNode* pNode)
    {
        return pNode==nullptr?0:pNode->nHeight;
    }//GetRoot���ø���



    CMyTreeNode* GetRoot()
    {
        return m_root;
    }//GetRoot���ø���
  
//     const int& (max)(const int& _Left, const int& _Right)
//     {	// return larger of _Left and _Right
//         return _Left< _Right ? _Right : _Left;
//     }
    //�����߶Ȳ�
    bool AdjustHeight(CMyTreeNode* pNode);

private:
    //��������find ,delate

    bool DeleteStuID(CMyTreeNode* pNode);//��ѧ��ɾ���ڵ�
    bool DeleteStuName(CMyTreeNode* pNode);//��ѧ������ɾ���ڵ�

    bool DeleteCourID(CMyTreeNode* pNode);//
    bool DeleteCourName(CMyTreeNode* pNode);//

    bool DeleteRecStuID(CMyTreeNode* pNode);//
    bool DeleteRecCourID(CMyTreeNode* pNode);//
    CMyTreeNode* m_root;//���ڵ�
    int m_nSize;//�ڵ��С
};

