#include "stdafx.h"
#include "MyTree.h"
#include "MyQueue.h"
#include "MyStack.h"
#include "Mystring.h"
#include "Student.h"
#include "CourseInformation.h"
#include "Record.h"
#include <string.h>
#include <assert.h>
#include <algorithm>

CMystring MyStr;
//#include "MyQueue.h"
using namespace std;
CMyTree::CMyTree()
{
    m_root = nullptr;
    m_nSize = 0;
}


CMyTree::~CMyTree()
{

}

//增加的逻辑
/*
左孩<根<右孩


*/

bool CMyTree::InsertStuID(CStudent stu)//根据学号插入
{
    CMyTreeNode* pNew = new CMyTreeNode(stu);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //有根节点,找到合适的位置插入
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    while (true)
    {
        if (stu.nID < pInsert->data.nID)//插入数据小于根节点数据
        {
            if (pInsert->pLeft == nullptr)//如果左值为空,插入数据就是左值
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//左孩值变成子节点
            continue;
        }
        else if (stu.nID > pInsert->data.nID)
        {
            if (pInsert->pRight == nullptr)//如果右值为空,插入数据就是左值
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//右孩值变成子节点
            continue;
        }
        else
        {
            CMyTreeNode* pFind = findStuID(stu);
            if (pFind != nullptr)
            {
                //printf("%d,%d,%s,学号相同,不可插入\r\n",pFind->data.nLine,pFind->data.nID,pFind->data.szName);
                return false;
            }
            return false;
        }
    }
    AdjustHeight(pInsert);
    m_nSize++;
    return true;
}

bool CMyTree::InsertStuName(CStudent stu)//根据学生姓名插入
{
    CMyTreeNode* pNew = new CMyTreeNode(stu);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //有根节点,找到合适的位置插入
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    string str1(stu.szName);
    string str2(pInsert->data.szName);
    while (true)
    {

        if (MyStr.Cmp(stu.szName, pInsert->data.szName)<0)//插入数据小于根节点数据
        //if (str1<str2)
        //if (stu < pInsert->data)
        {
            if (pInsert->pLeft == nullptr)//如果左值为空,插入数据就是左值
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//左孩值变成子节点
            continue;
        }
        else if (MyStr.Cmp(stu.szName, pInsert->data.szName)>0)
        //else if (str1>str2)
        //else if(stu> pInsert->data)
        {
            if (pInsert->pRight == nullptr)//如果右值为空,插入数据就是左值
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//右孩值变成子节点
            continue;
        }
        else if(MyStr.Cmp(stu.szName, pInsert->data.szName)==0)
        {
            CMyTreeNode* pFind = findStuName(stu);
            while (pFind->pList != nullptr)
            {
                pFind = pFind->pList;
            }
            pFind->pList = pNew;
            break;
        }
    }
    AdjustHeight(pInsert);
    m_nSize++;
    return true;
}

//课程信息插入
bool CMyTree::InsertCourName(CCourseInformation data)//按课程名字插入
{
    CMyTreeNode* pNew = new CMyTreeNode(data);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //有根节点,找到合适的位置插入
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    string str1(data.szCourseName);
    string str2(pInsert->Cdata.szCourseName);
    while (true)
    {

        if (MyStr.Cmp(data.szCourseName, pInsert->Cdata.szCourseName) < 0)//插入数据小于根节点数据
        //if (str1<str2)
        //if (data < pInsert->Cdata)
        {
            if (pInsert->pLeft == nullptr)//如果左值为空,插入数据就是左值
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//左孩值变成子节点
        }
        else if (MyStr.Cmp(data.szCourseName, pInsert->Cdata.szCourseName) > 0)
        //else if (str1>str2)
        //else if (data > pInsert->Cdata)
        {
            if (pInsert->pRight == nullptr)//如果右值为空,插入数据就是左值
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//右孩值变成子节点
        }
        else if(MyStr.Cmp(data.szCourseName, pInsert->Cdata.szCourseName) == 0)
        {
            CMyTreeNode* pFind = findCourName(data);
            if(pFind != nullptr)
            {
                //printf("%d,%d,%s,课程名相同,不可插入\r\n", pFind->Cdata.nLine, pFind->Cdata.nCourseID, pFind->Cdata.szCourseName);
                return false;
            }
            return false;
        }
    }
    AdjustHeight(pInsert);
    m_nSize++;
    return true;
}

bool CMyTree::InsertCourID(CCourseInformation data)//按课程id插入
{
    CMyTreeNode* pNew = new CMyTreeNode(data);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //有根节点,找到合适的位置插入
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    while (true)
    {
        if (data.nCourseID < pInsert->Cdata.nCourseID)//插入数据小于根节点数据
        {
            if (pInsert->pLeft == nullptr)//如果左值为空,插入数据就是左值
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//左孩值变成子节点
        }
        else if (data.nCourseID > pInsert->Cdata.nCourseID)
        {
            if (pInsert->pRight == nullptr)//如果右值为空,插入数据就是左值
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//右孩值变成子节点
        }
        else
        {
            CMyTreeNode* pFind = findCourID(data);
            if(pFind != nullptr)
            {
                //printf("%d,%d,%s,课程id,不可插入\r\n",pFind->Cdata.nLine,pFind->Cdata.nCourseID,pFind->Cdata.szCourseName);
                return false;
            }
            return false;
        }
    }
    AdjustHeight(pInsert);
    m_nSize++;
    return true;
}

//选课记录插入
bool CMyTree::InsertRecStuId(CRecord Rec)//按课程名id插入
{
    CMyTreeNode* pNew = new CMyTreeNode(Rec);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //有根节点,找到合适的位置插入
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    while (true)
    {
        if (Rec.nStuID< pInsert->Rdata.nStuID)//插入数据小于根节点数据
        {
            if (pInsert->pLeft == nullptr)//如果左值为空,插入数据就是左值
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//左孩值变成子节点
            continue;
        }
        else if (Rec.nStuID > pInsert->Rdata.nStuID)
        {
            if (pInsert->pRight == nullptr)//如果右值为空,插入数据就是左值
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//右孩值变成子节点
            continue;
        }
        else if (Rec.nStuID == pInsert->Rdata.nStuID)
        {
            CMyTreeNode* pFind = findRecStuID(Rec);
            while (pFind->pList != nullptr)
            {
                pFind = pFind->pList;
            }
            pFind->pList = pNew;
            break;
        }
    }
    AdjustHeight(pInsert);
    m_nSize++;
    return true;
}

bool CMyTree::InsertRecCourId(CRecord Rec)//按课程名id插入
{
    CMyTreeNode* pNew = new CMyTreeNode(Rec);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //有根节点,找到合适的位置插入
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    while (true)
    {
        if (Rec.nCourseID< pInsert->Rdata.nCourseID)//插入数据小于根节点数据
        {
            if (pInsert->pLeft == nullptr)//如果左值为空,插入数据就是左值
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//左孩值变成子节点
            //printf("node ptr: %p, Height:%d\r\n", pInsert, pInsert->nHeight);
            continue;
        }
        else if (Rec.nCourseID > pInsert->Rdata.nCourseID)
        {
            if (pInsert->pRight == nullptr)//如果右值为空,插入数据就是左值
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//右孩值变成子节点
            continue;
        }
        else if (Rec.nCourseID == pInsert->Rdata.nCourseID)
        {
            CMyTreeNode* pFind = findRecCourID(Rec);
            while (pFind->pList != nullptr)
            {
                pFind = pFind->pList;
            }
            pFind->pList = pNew;
            break;
        }
    }
    AdjustHeight(pInsert);
    m_nSize++;
    return true;
}
//节点删除
bool CMyTree::DeleteStuName(CMyTreeNode* pFind)//删除名字
{
    assert(pFind != nullptr);
    /*
    删除右3种情况;
    1.删除节点是树叶，则直接删除
    2.被删除的节点只有一个子节点，
    此时只需要将删除节点的上一个节点的指向该节点的指针指向该节点唯一的子节点
    3.被删除的节点有两个子节点
    */

    //删除同名
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //没有叶子节点,左右孩都是空
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = nullptr;//删除
        }
        else if (pFind->pParent->pLeft == pFind)
        {
            pFind->pParent->pLeft = nullptr;
        }
        else if (pFind->pParent->pRight == pFind)
        {
            pFind->pParent->pRight = nullptr;
        }
        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    //左右孩都有节点,取左子树的右子节点和删除的父节点做替换,为根节点
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//进左子树
        while (Max->pRight != nullptr)//查找左子树的最右子节点
        {
            Max = Max->pRight;
        }
        //找到后和父节点交换
        CStudent Tmp = pFind->data;
        pFind->data = Max->data;
        Max->data = Tmp;

        //删除节点
        DeleteStuName(Max);
        // m_nSize--;
    }
    //只有一个子节点
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//申请一个交换变量
        //要么左边有值,要么右边有值
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //重新定义父子节点关系,抛弃原来的父子关系
        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = pSon;
        }
        else//有根节点
        {
            
            if (MyStr.Cmp(pSon->data.szName, pFind->pParent->data.szName)>0)
            {
                pFind->pParent->pRight = pSon;
            }
            else
            {
                pFind->pParent->pLeft = pSon;
            }

        }
        pSon->pParent = pFind->pParent;//更改父子关系

        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    return true;
}
bool CMyTree::DeleteStuID(CMyTreeNode* pFind)//删除id
{
    assert(pFind != nullptr);
    /*
    删除右3种情况;
    1.删除节点是树叶，则直接删除
    2.被删除的节点只有一个子节点，
    此时只需要将删除节点的上一个节点的指向该节点的指针指向该节点唯一的子节点
    3.被删除的节点有两个子节点
    */

    //删除同名
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp!=nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //没有叶子节点,左右孩都是空
    if (pFind->pLeft==nullptr && pFind->pRight==nullptr)
    {
        
        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = nullptr;//删除
        }
        else if (pFind->pParent->pLeft==pFind)
        {
            pFind->pParent->pLeft = nullptr;
        }
        else if (pFind->pParent->pRight == pFind)
        {
            pFind->pParent->pRight = nullptr;
        }
        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    //左右孩都有节点,取左子树的右子节点和删除的父节点做替换,为根节点
    else if (pFind->pLeft!=nullptr && pFind->pRight!=nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//进左子树
        while (Max->pRight != nullptr)//查找左子树的最右子节点
        {
            Max = Max->pRight;
        }
        //找到后和父节点交换
        CStudent Tmp = pFind->data;
        pFind->data = Max->data;
        Max->data = Tmp;

        //删除节点
        DeleteStuID(Max);
       // m_nSize--;
    }
    //只有一个子节点
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//申请一个交换变量
        //要么左边有值,要么右边有值
        if (pFind->pLeft!=nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //重新定义父子节点关系,抛弃原来的父子关系
        if (pFind->pParent==nullptr)//没有根节点
        {
            m_root = pSon;
        }
        else//有根节点
        {
            
            if (pSon->data.nID > pFind->pParent->data.nID)
            {
                pFind->pParent->pRight=pSon;
            }
            else
            {
                pFind->pParent->pLeft = pSon;
            }
           
        }
        pSon->pParent = pFind->pParent;//更改父子关系

        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    return true;
}

bool CMyTree::DeleteCourID(CMyTreeNode* pFind)
{
    assert(pFind != nullptr);
    /*
    删除右3种情况;
    1.删除节点是树叶，则直接删除
    2.被删除的节点只有一个子节点，
    此时只需要将删除节点的上一个节点的指向该节点的指针指向该节点唯一的子节点
    3.被删除的节点有两个子节点
    */

    //删除同名
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //没有叶子节点,左右孩都是空
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = nullptr;//删除
        }
        else if (pFind->pParent->pLeft == pFind)
        {
            pFind->pParent->pLeft = nullptr;
        }
        else if (pFind->pParent->pRight == pFind)
        {
            pFind->pParent->pRight = nullptr;
        }
        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    //左右孩都有节点,取左子树的右子节点和删除的父节点做替换,为根节点
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//进左子树
        while (Max->pRight != nullptr)//查找左子树的最右子节点
        {
            Max = Max->pRight;
        }
        //找到后和父节点交换
        CCourseInformation Tmp = pFind->Cdata;
        pFind->Cdata = Max->Cdata;
        Max->Cdata = Tmp;

        //删除节点
        DeleteCourID(Max);
        // m_nSize--;
    }
    //只有一个子节点
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//申请一个交换变量
        //要么左边有值,要么右边有值
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //重新定义父子节点关系,抛弃原来的父子关系
        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = pSon;
        }
        else//有根节点
        {

            if (pSon->data.nID > pFind->pParent->data.nID)
            {
                pFind->pParent->pRight = pSon;
            }
            else
            {
                pFind->pParent->pLeft = pSon;
            }

        }
        pSon->pParent = pFind->pParent;//更改父子关系

        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    return true;
}
//
bool CMyTree::DeleteCourName(CMyTreeNode* pFind)
{
    assert(pFind != nullptr);
    /*
    删除右3种情况;
    1.删除节点是树叶，则直接删除
    2.被删除的节点只有一个子节点，
    此时只需要将删除节点的上一个节点的指向该节点的指针指向该节点唯一的子节点
    3.被删除的节点有两个子节点
    */

    //删除同名
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //没有叶子节点,左右孩都是空
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = nullptr;//删除
        }
        else if (pFind->pParent->pLeft == pFind)
        {
            pFind->pParent->pLeft = nullptr;
        }
        else if (pFind->pParent->pRight == pFind)
        {
            pFind->pParent->pRight = nullptr;
        }
        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    //左右孩都有节点,取左子树的右子节点和删除的父节点做替换,为根节点
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//进左子树
        while (Max->pRight != nullptr)//查找左子树的最右子节点
        {
            Max = Max->pRight;
        }
        //找到后和父节点交换
        CCourseInformation Tmp = pFind->Cdata;
        pFind->Cdata = Max->Cdata;
        Max->Cdata = Tmp;

        //删除节点
        DeleteCourName(Max);
        // m_nSize--;
    }
    //只有一个子节点
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//申请一个交换变量
        //要么左边有值,要么右边有值
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //重新定义父子节点关系,抛弃原来的父子关系
        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = pSon;
        }
        else//有根节点
        {

            if (MyStr.Cmp(pSon->data.szName, pFind->pParent->data.szName)>0)
            {
                pFind->pParent->pRight = pSon;
            }
            else
            {
                pFind->pParent->pLeft = pSon;
            }

        }
        pSon->pParent = pFind->pParent;//更改父子关系

        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    return true;
}//

bool CMyTree::DeleteRecStuID(CMyTreeNode* pFind)//
{
    assert(pFind != nullptr);
    /*
    删除右3种情况;
    1.删除节点是树叶，则直接删除
    2.被删除的节点只有一个子节点，
    此时只需要将删除节点的上一个节点的指向该节点的指针指向该节点唯一的子节点
    3.被删除的节点有两个子节点
    */

    //删除同名
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //没有叶子节点,左右孩都是空
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = nullptr;//删除
        }
        else if (pFind->pParent->pLeft == pFind)
        {
            pFind->pParent->pLeft = nullptr;
        }
        else if (pFind->pParent->pRight == pFind)
        {
            pFind->pParent->pRight = nullptr;
        }
        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    //左右孩都有节点,取左子树的右子节点和删除的父节点做替换,为根节点
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//进左子树
        while (Max->pRight != nullptr)//查找左子树的最右子节点
        {
            Max = Max->pRight;
        }
        //找到后和父节点交换
        CRecord Tmp = pFind->Rdata;
        pFind->Rdata = Max->Rdata;
        Max->Rdata = Tmp;

        //删除节点
        DeleteRecStuID(Max);
        // m_nSize--;
    }
    //只有一个子节点
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//申请一个交换变量
        //要么左边有值,要么右边有值
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //重新定义父子节点关系,抛弃原来的父子关系
        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = pSon;
        }
        else//有根节点
        {

            if (pSon->data.nID > pFind->pParent->data.nID)
            {
                pFind->pParent->pRight = pSon;
            }
            else
            {
                pFind->pParent->pLeft = pSon;
            }

        }
        pSon->pParent = pFind->pParent;//更改父子关系

        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    return true;
}

bool CMyTree::DeleteRecCourID(CMyTreeNode* pFind)//
{
    assert(pFind != nullptr);
    /*
    删除右3种情况;
    1.删除节点是树叶，则直接删除
    2.被删除的节点只有一个子节点，
    此时只需要将删除节点的上一个节点的指向该节点的指针指向该节点唯一的子节点
    3.被删除的节点有两个子节点
    */

    //删除同名
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //没有叶子节点,左右孩都是空
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = nullptr;//删除
        }
        else if (pFind->pParent->pLeft == pFind)
        {
            pFind->pParent->pLeft = nullptr;
        }
        else if (pFind->pParent->pRight == pFind)
        {
            pFind->pParent->pRight = nullptr;
        }
        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    //左右孩都有节点,取左子树的右子节点和删除的父节点做替换,为根节点
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//进左子树
        while (Max->pRight != nullptr)//查找左子树的最右子节点
        {
            Max = Max->pRight;
        }
        //找到后和父节点交换
        CRecord Tmp = pFind->Rdata;
        pFind->Rdata = Max->Rdata;
        Max->Rdata = Tmp;

        //删除节点
        DeleteRecCourID(Max);
        // m_nSize--;
    }
    //只有一个子节点
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//申请一个交换变量
        //要么左边有值,要么右边有值
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //重新定义父子节点关系,抛弃原来的父子关系
        if (pFind->pParent == nullptr)//没有根节点
        {
            m_root = pSon;
        }
        else//有根节点
        {

            if (pSon->data.nID > pFind->pParent->data.nID)
            {
                pFind->pParent->pRight = pSon;
            }
            else
            {
                pFind->pParent->pLeft = pSon;
            }

        }
        pSon->pParent = pFind->pParent;//更改父子关系

        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    return true;
}


//查找
CMyTreeNode* CMyTree::findStuID(CStudent stu)//根据学生id查找
{
    CMyTreeNode* pFind = m_root;

    while (pFind != nullptr)
    {
        if (stu.nID < pFind->data.nID)//传入数据小于根节点数据,到左边子节点找
        {
            pFind = pFind->pLeft;
        }
        else if (stu.nID>pFind->data.nID)
        {
            pFind = pFind->pRight;//传入数据小于根节点数据,到右边子节点找
        }
        else
        {
            //pFind 对应的节点
            return pFind;
        }
    }
    return nullptr;
}

CMyTreeNode* CMyTree::findStuName(CStudent stu)//根据学生名字查找
{
    CMyTreeNode* pFind = m_root;
    string str1(stu.szName);
    string str2(pFind->data.szName);
    while (pFind != nullptr)
    {

        if (MyStr.Cmp(stu.szName ,pFind->data.szName)<0)//传入数据小于根节点数据,到左边子节点找
        //if (str1<str2)
        //if (stu< pFind->data)
        {
            pFind = pFind->pLeft;
        }
        else if (MyStr.Cmp(stu.szName, pFind->data.szName)>0)
        //else if (str1>str2)
        //else if (stu > pFind->data)
        {
            pFind = pFind->pRight;//传入数据小于根节点数据,到右边子节点找
        }
        else if (MyStr.Cmp(stu.szName, pFind->data.szName)==0)
        {
            //pFind 对应的节点
            return pFind;
        }
    }
    return nullptr;
}

CMyTreeNode*CMyTree::findCourName(CCourseInformation Courdata)//按课程名字查找
{
        CMyTreeNode* pFind = m_root;
        string str1(Courdata.szCourseName);
        string str2(pFind->Cdata.szCourseName);
        while (pFind != nullptr)
        {

            if (MyStr.Cmp(Courdata.szCourseName, pFind->Cdata.szCourseName) < 0)//传入数据小于根节点数据,到左边子节点找
            //if (str1<str2)
            //if (Courdata < pFind->Cdata)
            {
                pFind = pFind->pLeft;
            }
            else if (MyStr.Cmp(Courdata.szCourseName, pFind->Cdata.szCourseName) > 0)
            //else if (str1>str2)
            //else if (Courdata > pFind->Cdata)
            {
                pFind = pFind->pRight;//传入数据小于根节点数据,到右边子节点找
            }
            else if (MyStr.Cmp(Courdata.szCourseName, pFind->Cdata.szCourseName) == 0)
            {
                //pFind 对应的节点
                return pFind;
            }
        }
        return nullptr;
}

CMyTreeNode*CMyTree::findCourID(CCourseInformation data)//按课程id查找
{
    CMyTreeNode* pFind = m_root;

    while (pFind != nullptr)
    {
        if (data.nCourseID < pFind->Cdata.nCourseID)//传入数据小于根节点数据,到左边子节点找
        {
            pFind = pFind->pLeft;
        }
        else if (data.nCourseID>pFind->Cdata.nCourseID)
        {
            pFind = pFind->pRight;//传入数据小于根节点数据,到右边子节点找
        }
        else
        {
            //pFind 对应的节点
            return pFind;
        }
    }
    return nullptr;
}

CMyTreeNode*CMyTree::findRecCourID(CRecord data)//按选课记录课程名ID查找
{
    CMyTreeNode* pFind = m_root;

    while (pFind != nullptr)
    {
        if (data.nCourseID < pFind->Rdata.nCourseID)//传入数据小于根节点数据,到左边子节点找
        {
            pFind = pFind->pLeft;
        }
        else if (data.nCourseID>pFind->Rdata.nCourseID)
        {
            pFind = pFind->pRight;//传入数据小于根节点数据,到右边子节点找
        }
        else
        {
            //pFind 对应的节点
            return pFind;
        }
    }
    return nullptr;
}
CMyTreeNode*CMyTree::findRecStuID(CRecord data)//按选课记录学生id查找
{
    CMyTreeNode* pFind = m_root;

    while (pFind != nullptr)
    {
        if (data.nStuID < pFind->Rdata.nStuID)//传入数据小于根节点数据,到左边子节点找
        {
            pFind = pFind->pLeft;
        }
        else if (data.nStuID>pFind->Rdata.nStuID)
        {
            pFind = pFind->pRight;//传入数据小于根节点数据,到右边子节点找
        }
        else
        {
            //pFind 对应的节点
            return pFind;
        }
    }
    return nullptr;
}
//删除
bool CMyTree::DeleteStuID(CStudent data)
{
    CMyTreeNode*pFind = nullptr;
    pFind = findStuID(data);
    if (pFind==nullptr)
    {
        return false;
    }
    else
    {
        return DeleteStuID(pFind);
    }
    return true;
}

bool CMyTree::DeleteStuName(CStudent data)
{
    CMyTreeNode*pFind = nullptr;
    pFind = findStuName(data);
    if (pFind == nullptr)
    {
        return false;
    }
    else
    {
        return DeleteStuName(pFind);
    }
    return true;
}

bool CMyTree::DeleteCourID(CCourseInformation data)//按课程id删除
{
    CMyTreeNode*pFind = nullptr;
    pFind = findCourID(data);
    if (pFind == nullptr)
    {
        return false;
    }
    else
    {
        return DeleteCourID(pFind);
    }
    return true;
}
   
bool CMyTree::DeleteCourName(CCourseInformation data)//按课程名字删除
{
    CMyTreeNode*pFind = nullptr;
    pFind = findCourName(data);
    if (pFind == nullptr)
    {
        return false;
    }
    else
    {
        return DeleteCourName(pFind);
    }
    return true;
}

bool CMyTree::DeleteRecCourID(CRecord data)//按选课记录课程id删除
{
    CMyTreeNode*pFind = nullptr;
    pFind = findRecCourID(data);
    if (pFind == nullptr)
    {
        return false;
    }
    else
    {
        return DeleteRecCourID(pFind);
    }
    return true;
}
bool CMyTree::DeleteRecStuID(CRecord data)//按选课记录学生id删除
{
    CMyTreeNode*pFind = nullptr;
    pFind = findRecStuID(data);
    if (pFind == nullptr)
    {
        return false;
    }
    else
    {
        return DeleteRecStuID(pFind);
    }
    return true;
}
/*
50
30      80
10   40  70

50 30 80 10 40 70

队列:                   出:
50
30 80                   50
80 10 40                50 30
10 40 70                50 30 80
40 70                   50 30 80 10
70                      50 30 80 10 40
50 30 80 10 40 70

*/



void CMyTree::Layer()
{

    CMyQueue<CMyTreeNode*> queue;
    //CMyTreeNode* p= queue;
    //根不为空先压入根,找到根部再往下
    if (m_root!= nullptr)
    {  
        queue.push(m_root);
    }
    while (!queue.empty())
    {
        //取队列第一个元素,先从左边开始取值,然后右边
        CMyTreeNode*pCur = queue.front();
        if (pCur->pLeft!=nullptr)
        {
            queue.push(pCur->pLeft);
        }
        if (pCur->pRight!=nullptr)
        {
            queue.push(pCur->pRight);
        }
        printf("%d",pCur->data);
        queue.pop();//弹出第一个
    }

}


//名字层次遍历
void CMyTree::NameLayer()
{

    CMyQueue<CMyTreeNode*> queue;
    //CMyTreeNode* p= queue;
    //根不为空先压入根,找到根部再往下
    if (m_root != nullptr)
    {
        queue.push(m_root);
    }
    while (!queue.empty())
    {
        //取队列第一个元素,先从左边开始取值,然后右边
        CMyTreeNode*pCur = queue.front();
        if (pCur->pLeft != nullptr)
        {
            queue.push(pCur->pLeft);
        }
        if (pCur->pRight != nullptr)
        {
            queue.push(pCur->pRight);
        }
        printf("%d-%s\n", pCur->data.nID,pCur->data.szName);
        queue.pop();//弹出第一个
    }

}
//学生信息中序遍历
void CMyTree::StuLDR_stc(CMyTreeNode*pNode)
{
    CMyStack<CMyTreeNode*>stc;
    while (true)
    {

        while (pNode != nullptr)
        {
            stc.push(pNode);
            //(1)循环遍历(压栈)到最左边,出栈
            pNode = pNode->pLeft;
        }

        if (stc.empty())//栈为空跳出当前循环
        {
            break;
        }
        CMyTreeNode*pCur = stc.top();
        printf("%d-%s\n", pCur->data.nID, pCur->data.szName);

        stc.pop();
        //(2) 判断出栈的这个节点有没有右孩子,有则执行第一步
        pNode = pCur->pRight;

    }
}

//课程信息中序遍历
void CMyTree::CourLDR_stc(CMyTreeNode*pNode)
{
    CMyStack<CMyTreeNode*>stc;
    int n = 1;
    while (true)
    {

        while (pNode != nullptr)
        {
            stc.push(pNode);
            //(1)循环遍历(压栈)到最左边,出栈
            pNode = pNode->pLeft;
        }

        if (stc.empty())//栈为空跳出当前循环
        {
            break;
        }
        CMyTreeNode*pCur = stc.top();
        
        printf("%d-%s-%d\n", pCur->Cdata.nCourseID, pCur->Cdata.szCourseName,n);
        n++;
        stc.pop();
        //(2) 判断出栈的这个节点有没有右孩子,有则执行第一步
        pNode = pCur->pRight;

    }
}



//选课记录层次遍历
void CMyTree::RecLDR_stc(CMyTreeNode*pNode)
{
    CMyStack<CMyTreeNode*>stc;
    while (true)
    {

        while (pNode != nullptr)
        {
            stc.push(pNode);
            //(1)循环遍历(压栈)到最左边,出栈
            pNode = pNode->pLeft;
        }

        if (stc.empty())//栈为空跳出当前循环
        {
            break;
        }
        CMyTreeNode*pCur = stc.top();
        printf("%d-%d-%d\n", pCur->Rdata.nStuID, pCur->Rdata.nCourseID,pCur->Rdata.nScore);

        stc.pop();
        //(2) 判断出栈的这个节点有没有右孩子,有则执行第一步
        if (pCur->pList!=nullptr)
        {
            pNode = pCur->pList;
        }
        else
        {
            pNode = pCur->pRight;
        }
        

    }
}

/*
      50
  30      80
10   40  70

50 30 10 40 80 70
栈:                   出:

栈底---->栈顶
50
80  30             50
80  40  10         50  30
80  40             50  30  10
80                 50  30  10  40
70                 50  30  10  40  80
50  30  10  40  80  70
*/

//前序遍历栈实现

void CMyTree::DLR_stc(CMyTreeNode* pNode)
{
    CMyStack<CMyTreeNode*> stc;
    if (pNode != nullptr)
    {
        stc.push(pNode);
    }

    while (!stc.empty())
    {
        CMyTreeNode* pCur = stc.top();
        printf("%d\r\n", pCur->data);
        stc.pop();
        if (pCur->pRight!=nullptr)
        {
            stc.push(pCur->pRight);
        }

        if (pCur->pLeft != nullptr)
        {
            stc.push(pCur->pLeft);
        }
    }
}

//中序栈实现
/*
       50
   30      80
10   40  70

10 30 40 50 70 80
栈:                   出:
栈底---->栈顶
(1) 循环遍历(压栈)到最左边,出栈
(2) 判断出栈的这个节点有没有右孩子,有则执行第一步

50  30  10
50  30             10
50  40             10  30
50                 10  30  40
80  70             10  30  40  50
10  30  40  50  70  80
*/
void CMyTree::LDR_stc(CMyTreeNode*pNode)
{
    CMyStack<CMyTreeNode*>stc;
    while (true)
    {
        
        while(pNode != nullptr)
        {
            stc.push(pNode);
            //(1)循环遍历(压栈)到最左边,出栈
            pNode = pNode->pLeft;
        }
        
        if (stc.empty())//栈为空跳出当前循环
        {
            break;
        }
//             if (pNode->pLeft!=nullptr)
//             {
//                 
//                // stc.push(pNode);
//             }
          
                CMyTreeNode*pCur = stc.top();
                printf("%d\t", pCur->data);

                stc.pop();
                //(2) 判断出栈的这个节点有没有右孩子,有则执行第一步
                pNode = pCur->pRight;
     
    }
}


/*
       50
  30      80
10   40  70

10 40 30 70 80 50
栈:                   出:
栈底---->栈顶
(1) 循环遍历(压栈)到最左边,
(2) 判断栈顶节点有没有右孩子,有则执行第一步
(3) 如果没有右孩子,则出栈打印

50  30  10
50  30              10
50  30  40          10
50  30              10  40
50                  10  40  30
50  80  70          10  40  30
50  80  70          10  40  30
50  80              10  40  30  70
50                  10  40  30  70  80
10  40  30  70  80  50

*/
//4.后续序遍历(非递归实现)
void CMyTree::LRD_stc(CMyTreeNode*pNode)
{
    CMyStack<CMyTreeNode*>stc;
    CMyTreeNode*pTmp = nullptr;
    while (true)
    {
        while (pNode != nullptr)
        {
            stc.push(pNode);
            pNode = pNode->pLeft;
        }
        if (stc.empty())//栈为空跳出当前循环
        {
            break;
        }
        CMyTreeNode*pCur = stc.top();
        //pNode = pCur->pRight;
        if (pCur->pRight == nullptr || (pCur->pRight != nullptr) &&
            (pCur->pRight == pTmp))
        {
            printf("%d/t", pCur->data);
            pTmp = pCur;
            stc.pop();
            continue;//关键
        }
        pNode = pCur->pRight;
    }

}

//左单旋
/*
10(pK1)
20(pK2)
30

==>
20
10  30
---------------------------

   80
     100(pK1)
90    120(pK2)
 110    140
          160

     80
        120(pK2)
(pK1)100    140
   90  110     160

    pG
      pK1
    pA   pK2
        pB  pC

==>
    pG
       pK2
    pK1   pC
  pA  pB
*/
//左旋
void CMyTree::LeftRotate(CMyTreeNode* pK1, CMyTreeNode* pK2){
    CMyTreeNode* pG = pK1->pParent;
    CMyTreeNode* pA = pK1->pLeft;
    CMyTreeNode* pB = pK2->pLeft;
    CMyTreeNode* pC = pK2->pRight;

    if (pG == nullptr){
        m_root = pK2;
    }
    else{
        if (pG->pRight == pK1){
            pG->pRight = pK2;
        }
        else{
            pG->pLeft = pK2;
        }

    }

    pK1->pParent = pK2;
    pK1->pRight = pB;

    pK2->pParent = pG;
    pK2->pLeft = pK1;

    if (pB != nullptr){
        pB->pParent = pK1;
    }

    pK1->nHeight = max(GetHeight(pA), GetHeight(pB)) + 1;
    pK2->nHeight = max(GetHeight(pK1), GetHeight(pC)) + 1;
}

void CMyTree::RightRotate(CMyTreeNode* pK1, CMyTreeNode* pK2){
    CMyTreeNode* pG = pK1->pParent;
    CMyTreeNode* pA = pK1->pRight;
    CMyTreeNode* pB = pK2->pLeft;
    CMyTreeNode* pC = pK2->pRight;

    if (pG == nullptr){
        m_root = pK2;
    }
    else{
        if (pG->pLeft == pK1){
            pG->pLeft = pK2;
        }
        else{
            pG->pRight = pK2;
        }
    }

    pK1->pParent = pK2;
    pK1->pLeft = pC;

    pK2->pParent = pG;
    pK2->pRight = pK1;

    if (pC != nullptr){
        pC->pParent = pK1;
    }

    pK1->nHeight = max(GetHeight(pA), GetHeight(pC)) + 1;
    pK2->nHeight = max(GetHeight(pK1), GetHeight(pB)) + 1;
}

//字符串的左右旋转
// void CMyTree::StrLeftRotate(CMyTreeNode*pK1, CMyTreeNode*pK2)
// {
//     //描述关系
//     CMyTreeNode*pG = pK1->pParent;
//     CMyTreeNode*pA = pK1->pLeft;
//     CMyTreeNode*pB = pK2->pLeft;
//     CMyTreeNode*pC = pK2->pRight;
// 
//     //找  平衡点
// 
//     if (pG == nullptr)
//     {
//         m_root = pK2;
//     }
//     else
//     {
//         if (MyStr.Cmp(pG->pRight , pK1)=0)
//         {
//             pG->pRight = pK2;
//         }
//         else
//         {
//             pG->pLeft = pK2;
//         }
//     }
// 
//     pK1->pParent = pK2;
//     pK1->pRight = pB;
// 
//     pK2->pLeft = pK1;
//     pK2->pParent = pG;
//     pK1->nHeight = max(GetHeight(pA), GetHeight(pB)) + 1;
//     pK2->nHeight = max(GetHeight(pK1), GetHeight(pC)) + 1;
// }
// 
// 
// void CMyTree::StrRightRotate(CMyTreeNode*pK1, CMyTreeNode*pK2)
// {
//     //描述关系
//     CMyTreeNode*pG = pK1->pParent;
//     CMyTreeNode*pA = pK1->pRight;
//     CMyTreeNode*pB = pK2->pLeft;
//     CMyTreeNode*pC = pK2->pRight;
// 
//     //找  平衡点
//     if (pG == nullptr){
//         m_root = pK2;
//     }
//     else{
//         if (MyStr.Cmp(pG->pLeft , pK1)=0){
//             pG->pLeft = pK2;
//         }
//         else{
//             pG->pRight = pK2;
//         }
//     }
// 
//     pK1->pParent = pK2;
//     pK1->pLeft = pC;
// 
//     pK2->pParent = pG;
//     pK2->pRight = pK1;
// 
//     if (pC != nullptr){
//         pC->pParent = pK1;
//     }
// 
//     pK1->nHeight = max(GetHeight(pA), GetHeight(pC)) + 1;
//     pK2->nHeight = max(GetHeight(pK1), GetHeight(pB)) + 1;
// }
bool CMyTree::AdjustHeight(CMyTreeNode* pNode){

    if (pNode == nullptr){
        return false;
    }

    while (pNode != nullptr)
    {
        int nLeftHeight = GetHeight(pNode->pLeft);
        int nRightHeight = GetHeight(pNode->pRight);

        pNode->nHeight = max(nLeftHeight, nRightHeight) + 1;

        //判断pNode是否平衡
        if (abs(nLeftHeight - nRightHeight) > 1){
            //如果不平衡,判断是4种旋转的哪种情况
            CMyTreeNode* pK1 = pNode;
            CMyTreeNode* pK2 = nullptr;
            CMyTreeNode* pK3 = nullptr;

            //右边子树重
            if (GetHeight(pNode->pLeft) <
                GetHeight(pNode->pRight)){
                pK2 = pNode->pRight;
            }
            else{
                pK2 = pNode->pLeft;
            }

            if (GetHeight(pK2->pLeft) <
                GetHeight(pK2->pRight)){
                pK3 = pK2->pRight;
            }
            else{
                pK3 = pK2->pLeft;
            }

            if (pK1->pRight == pK2 && pK2->pRight == pK3){
                /*
                左单旋:
                10  pK1
                20 pK2
                30 pK3
                */
                LeftRotate(pK1, pK2);
            }
            else if (pK1->pLeft == pK2 && pK2->pLeft == pK3){
                /*
                右单旋:
                30
                20
                10
                */
                RightRotate(pK1, pK2);
            }
            else if (pK1->pRight == pK2 && pK2->pLeft == pK3){
                /*
                R-L双旋:
                30  pK1
                50  pK2
                40   pK3
                */
                RightRotate(pK2, pK3);
                LeftRotate(pK1, pK3);
            }
            else if (pK1->pLeft == pK2 && pK2->pRight == pK3){
                /*
                L-R双旋:
                40 pK1
                20  pK2
                30 pK3
                */
                LeftRotate(pK2, pK3);
                RightRotate(pK1, pK3);
            }
        }

        pNode = pNode->pParent;
    }


    return true;
}

// bool CMyTree::StrAdjustHeight(CMyTreeNode* pNode){
// 
//     if (pNode == nullptr){
//         return false;
//     }
// 
//     while (pNode != nullptr)
//     {
//         int nLeftHeight = GetHeight(pNode->pLeft);
//         int nRightHeight = GetHeight(pNode->pRight);
// 
//         pNode->nHeight = max(nLeftHeight, nRightHeight) + 1;
// 
//         //判断pNode是否平衡
//         if (abs(nLeftHeight - nRightHeight) > 1){
//             //如果不平衡,判断是4种旋转的哪种情况
//             CMyTreeNode* pK1 = pNode;
//             CMyTreeNode* pK2 = nullptr;
//             CMyTreeNode* pK3 = nullptr;
// 
//             //右边子树重
//             if (GetHeight(pNode->pLeft) <
//                 GetHeight(pNode->pRight)){
//                 pK2 = pNode->pRight;
//             }
//             else{
//                 pK2 = pNode->pLeft;
//             }
// 
//             if (GetHeight(pK2->pLeft) <
//                 GetHeight(pK2->pRight)){
//                 pK3 = pK2->pRight;
//             }
//             else{
//                 pK3 = pK2->pLeft;
//             }
//             
//                 if ((MyStr.Cmp(pK1->pRight, pK2) = 0) && (MyStr.Cmp(pK2->pRight, pK3) = 0)){
//                 /*
//                 左单旋:
//                 10  pK1
//                 20 pK2
//                 30 pK3
//                 */
//                 StrLeftRotate(pK1, pK2);
//             }
//                 
//                 else if ((MyStr.Cmp(pK1->pLeft, pK2) = 0) && (MyStr.Cmp(pK2->pLeft, pK3) = 0)){
//                 /*
//                 右单旋:
//                 30
//                 20
//                 10
//                 */
//                 StrRightRotate(pK1, pK2);
//             }
//                 
//                 else if ((MyStr.Cmp(pK1->pRight, pK2) = 0) && (MyStr.Cmp(pK2->pLeft, pK3) = 0)){
//                 /*
//                 R-L双旋:
//                 30  pK1
//                 50  pK2
//                 40   pK3
//                 */
//                 StrRightRotate(pK2, pK3);
//                 StrLeftRotate(pK1, pK3);
//             }
//                 
//                 else if ((MyStr.Cmp(pK1->pLeft, pK2) = 0) && (MyStr.Cmp(pK2->pRight, pK3) = 0)){
//                 /*
//                 L-R双旋:
//                 40 pK1
//                 20  pK2
//                 30 pK3
//                 */
//                 StrLeftRotate(pK2, pK3);
//                 StrRightRotate(pK1, pK3);
//             }
//         }
// 
//         pNode = pNode->pParent;
//     }
// 
// 
//     return true;
// }