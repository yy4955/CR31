#pragma once

#include <assert.h>
#include <iostream>
#include "common.h"
#include "Student.h"
#include "CourseInformation.h"
#include "Record.h"
//#include <algorithm>
//异常类
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
 
    //高度
    int nHeight;
    //数据
    CStudent data;
    CCourseInformation Cdata;
    CRecord Rdata;
    //父节点
    CMyTreeNode*pParent;
    //左孩节点
    CMyTreeNode*pLeft;
    //右节点
    CMyTreeNode*pRight;
    CMyTreeNode*pList;

};

class CMyTree  
{
public:
    CMyTree();
    ~CMyTree();

    //增加
    bool InsertStuName(CStudent stu);//按学生名字插入
    bool InsertStuID(CStudent stu);//按学号插入

    bool InsertCourName(CCourseInformation data);//按课程名字插入
    bool InsertCourID(CCourseInformation data);//按课程id插入

    bool InsertRecStuId(CRecord Rec);//按选课记录学生id插入
    bool InsertRecCourId(CRecord Rec);//按选课记录课程id插入

    //删除
    bool DeleteStuID(CStudent data);//按学号删除
    bool DeleteStuName(CStudent data);//按学生姓名删除

    bool DeleteCourID(CCourseInformation data);//按课程id删除
    bool DeleteCourName(CCourseInformation data);//按课程名字删除

    bool DeleteRecCourID(CRecord data);//按选课记录课程id删除
    bool DeleteRecStuID(CRecord data);//按选课记录学生id删除
    //查

    CMyTreeNode* findStuName(CStudent stu);//按学生姓名查找
    CMyTreeNode* findStuID(CStudent stu);//按学号查找

    CMyTreeNode* findCourName(CCourseInformation Courdata);//按课程名字查找
    CMyTreeNode* findCourID(CCourseInformation data);//按课程id查找

    CMyTreeNode* findRecCourID(CRecord data);//按选课记录课程名ID查找
    CMyTreeNode* findRecStuID(CRecord data);//按选课记录学生id查找
    //4种遍历
    //1.层序遍历, 队列实现
    void Layer();
    void NameLayer();
    //2.前序遍历(非递归实现)
    void DLR_stc(CMyTreeNode*pNode);
    //3.中序遍历(非递归实现)
    void StuLDR_stc(CMyTreeNode*pNode);
    void CourLDR_stc(CMyTreeNode*pNode);
    void RecLDR_stc(CMyTreeNode*pNode);
    void LDR_stc(CMyTreeNode*pNode);
    //4.后续序遍历(非递归实现)
    void LRD_stc(CMyTreeNode*pNode);


    //树的旋转
    //1.左旋
    void LeftRotate(CMyTreeNode*pK1, CMyTreeNode*pK2);
    //2.右旋
    void RightRotate(CMyTreeNode*pK1, CMyTreeNode*pK2);
    bool StrAdjustHeight(CMyTreeNode* pNode);
    int  GetHeight(CMyTreeNode* pNode)
    {
        return pNode==nullptr?0:pNode->nHeight;
    }//GetRoot调用根。



    CMyTreeNode* GetRoot()
    {
        return m_root;
    }//GetRoot调用根。
  
//     const int& (max)(const int& _Left, const int& _Right)
//     {	// return larger of _Left and _Right
//         return _Left< _Right ? _Right : _Left;
//     }
    //调整高度差
    bool AdjustHeight(CMyTreeNode* pNode);

private:
    //内联函数find ,delate

    bool DeleteStuID(CMyTreeNode* pNode);//按学号删除节点
    bool DeleteStuName(CMyTreeNode* pNode);//按学生名字删除节点

    bool DeleteCourID(CMyTreeNode* pNode);//
    bool DeleteCourName(CMyTreeNode* pNode);//

    bool DeleteRecStuID(CMyTreeNode* pNode);//
    bool DeleteRecCourID(CMyTreeNode* pNode);//
    CMyTreeNode* m_root;//根节点
    int m_nSize;//节点大小
};

