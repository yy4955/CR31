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

//���ӵ��߼�
/*
��<��<�Һ�


*/

bool CMyTree::InsertStuID(CStudent stu)//����ѧ�Ų���
{
    CMyTreeNode* pNew = new CMyTreeNode(stu);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //�и��ڵ�,�ҵ����ʵ�λ�ò���
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    while (true)
    {
        if (stu.nID < pInsert->data.nID)//��������С�ڸ��ڵ�����
        {
            if (pInsert->pLeft == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//��ֵ����ӽڵ�
            continue;
        }
        else if (stu.nID > pInsert->data.nID)
        {
            if (pInsert->pRight == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//�Һ�ֵ����ӽڵ�
            continue;
        }
        else
        {
            CMyTreeNode* pFind = findStuID(stu);
            if (pFind != nullptr)
            {
                //printf("%d,%d,%s,ѧ����ͬ,���ɲ���\r\n",pFind->data.nLine,pFind->data.nID,pFind->data.szName);
                return false;
            }
            return false;
        }
    }
    AdjustHeight(pInsert);
    m_nSize++;
    return true;
}

bool CMyTree::InsertStuName(CStudent stu)//����ѧ����������
{
    CMyTreeNode* pNew = new CMyTreeNode(stu);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //�и��ڵ�,�ҵ����ʵ�λ�ò���
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    string str1(stu.szName);
    string str2(pInsert->data.szName);
    while (true)
    {

        if (MyStr.Cmp(stu.szName, pInsert->data.szName)<0)//��������С�ڸ��ڵ�����
        //if (str1<str2)
        //if (stu < pInsert->data)
        {
            if (pInsert->pLeft == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//��ֵ����ӽڵ�
            continue;
        }
        else if (MyStr.Cmp(stu.szName, pInsert->data.szName)>0)
        //else if (str1>str2)
        //else if(stu> pInsert->data)
        {
            if (pInsert->pRight == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//�Һ�ֵ����ӽڵ�
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

//�γ���Ϣ����
bool CMyTree::InsertCourName(CCourseInformation data)//���γ����ֲ���
{
    CMyTreeNode* pNew = new CMyTreeNode(data);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //�и��ڵ�,�ҵ����ʵ�λ�ò���
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    string str1(data.szCourseName);
    string str2(pInsert->Cdata.szCourseName);
    while (true)
    {

        if (MyStr.Cmp(data.szCourseName, pInsert->Cdata.szCourseName) < 0)//��������С�ڸ��ڵ�����
        //if (str1<str2)
        //if (data < pInsert->Cdata)
        {
            if (pInsert->pLeft == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//��ֵ����ӽڵ�
        }
        else if (MyStr.Cmp(data.szCourseName, pInsert->Cdata.szCourseName) > 0)
        //else if (str1>str2)
        //else if (data > pInsert->Cdata)
        {
            if (pInsert->pRight == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//�Һ�ֵ����ӽڵ�
        }
        else if(MyStr.Cmp(data.szCourseName, pInsert->Cdata.szCourseName) == 0)
        {
            CMyTreeNode* pFind = findCourName(data);
            if(pFind != nullptr)
            {
                //printf("%d,%d,%s,�γ�����ͬ,���ɲ���\r\n", pFind->Cdata.nLine, pFind->Cdata.nCourseID, pFind->Cdata.szCourseName);
                return false;
            }
            return false;
        }
    }
    AdjustHeight(pInsert);
    m_nSize++;
    return true;
}

bool CMyTree::InsertCourID(CCourseInformation data)//���γ�id����
{
    CMyTreeNode* pNew = new CMyTreeNode(data);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //�и��ڵ�,�ҵ����ʵ�λ�ò���
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    while (true)
    {
        if (data.nCourseID < pInsert->Cdata.nCourseID)//��������С�ڸ��ڵ�����
        {
            if (pInsert->pLeft == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//��ֵ����ӽڵ�
        }
        else if (data.nCourseID > pInsert->Cdata.nCourseID)
        {
            if (pInsert->pRight == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//�Һ�ֵ����ӽڵ�
        }
        else
        {
            CMyTreeNode* pFind = findCourID(data);
            if(pFind != nullptr)
            {
                //printf("%d,%d,%s,�γ�id,���ɲ���\r\n",pFind->Cdata.nLine,pFind->Cdata.nCourseID,pFind->Cdata.szCourseName);
                return false;
            }
            return false;
        }
    }
    AdjustHeight(pInsert);
    m_nSize++;
    return true;
}

//ѡ�μ�¼����
bool CMyTree::InsertRecStuId(CRecord Rec)//���γ���id����
{
    CMyTreeNode* pNew = new CMyTreeNode(Rec);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //�и��ڵ�,�ҵ����ʵ�λ�ò���
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    while (true)
    {
        if (Rec.nStuID< pInsert->Rdata.nStuID)//��������С�ڸ��ڵ�����
        {
            if (pInsert->pLeft == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//��ֵ����ӽڵ�
            continue;
        }
        else if (Rec.nStuID > pInsert->Rdata.nStuID)
        {
            if (pInsert->pRight == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//�Һ�ֵ����ӽڵ�
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

bool CMyTree::InsertRecCourId(CRecord Rec)//���γ���id����
{
    CMyTreeNode* pNew = new CMyTreeNode(Rec);
    if (m_root == nullptr)
    {
        m_root = pNew;
        m_nSize++;
        return true;
    }

    //�и��ڵ�,�ҵ����ʵ�λ�ò���
    CMyTreeNode*pInsert = m_root;
    CMyTreeNode*pParent = m_root;
    while (true)
    {
        if (Rec.nCourseID< pInsert->Rdata.nCourseID)//��������С�ڸ��ڵ�����
        {
            if (pInsert->pLeft == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pLeft = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pLeft;//��ֵ����ӽڵ�
            //printf("node ptr: %p, Height:%d\r\n", pInsert, pInsert->nHeight);
            continue;
        }
        else if (Rec.nCourseID > pInsert->Rdata.nCourseID)
        {
            if (pInsert->pRight == nullptr)//�����ֵΪ��,�������ݾ�����ֵ
            {
                pInsert->pRight = pNew;
                pNew->pParent = pInsert;
                break;
            }
            pInsert = pInsert->pRight;//�Һ�ֵ����ӽڵ�
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
//�ڵ�ɾ��
bool CMyTree::DeleteStuName(CMyTreeNode* pFind)//ɾ������
{
    assert(pFind != nullptr);
    /*
    ɾ����3�����;
    1.ɾ���ڵ�����Ҷ����ֱ��ɾ��
    2.��ɾ���Ľڵ�ֻ��һ���ӽڵ㣬
    ��ʱֻ��Ҫ��ɾ���ڵ����һ���ڵ��ָ��ýڵ��ָ��ָ��ýڵ�Ψһ���ӽڵ�
    3.��ɾ���Ľڵ��������ӽڵ�
    */

    //ɾ��ͬ��
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //û��Ҷ�ӽڵ�,���Һ����ǿ�
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = nullptr;//ɾ��
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
    //���Һ����нڵ�,ȡ�����������ӽڵ��ɾ���ĸ��ڵ����滻,Ϊ���ڵ�
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//��������
        while (Max->pRight != nullptr)//�����������������ӽڵ�
        {
            Max = Max->pRight;
        }
        //�ҵ���͸��ڵ㽻��
        CStudent Tmp = pFind->data;
        pFind->data = Max->data;
        Max->data = Tmp;

        //ɾ���ڵ�
        DeleteStuName(Max);
        // m_nSize--;
    }
    //ֻ��һ���ӽڵ�
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//����һ����������
        //Ҫô�����ֵ,Ҫô�ұ���ֵ
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //���¶��常�ӽڵ��ϵ,����ԭ���ĸ��ӹ�ϵ
        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = pSon;
        }
        else//�и��ڵ�
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
        pSon->pParent = pFind->pParent;//���ĸ��ӹ�ϵ

        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    return true;
}
bool CMyTree::DeleteStuID(CMyTreeNode* pFind)//ɾ��id
{
    assert(pFind != nullptr);
    /*
    ɾ����3�����;
    1.ɾ���ڵ�����Ҷ����ֱ��ɾ��
    2.��ɾ���Ľڵ�ֻ��һ���ӽڵ㣬
    ��ʱֻ��Ҫ��ɾ���ڵ����һ���ڵ��ָ��ýڵ��ָ��ָ��ýڵ�Ψһ���ӽڵ�
    3.��ɾ���Ľڵ��������ӽڵ�
    */

    //ɾ��ͬ��
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp!=nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //û��Ҷ�ӽڵ�,���Һ����ǿ�
    if (pFind->pLeft==nullptr && pFind->pRight==nullptr)
    {
        
        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = nullptr;//ɾ��
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
    //���Һ����нڵ�,ȡ�����������ӽڵ��ɾ���ĸ��ڵ����滻,Ϊ���ڵ�
    else if (pFind->pLeft!=nullptr && pFind->pRight!=nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//��������
        while (Max->pRight != nullptr)//�����������������ӽڵ�
        {
            Max = Max->pRight;
        }
        //�ҵ���͸��ڵ㽻��
        CStudent Tmp = pFind->data;
        pFind->data = Max->data;
        Max->data = Tmp;

        //ɾ���ڵ�
        DeleteStuID(Max);
       // m_nSize--;
    }
    //ֻ��һ���ӽڵ�
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//����һ����������
        //Ҫô�����ֵ,Ҫô�ұ���ֵ
        if (pFind->pLeft!=nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //���¶��常�ӽڵ��ϵ,����ԭ���ĸ��ӹ�ϵ
        if (pFind->pParent==nullptr)//û�и��ڵ�
        {
            m_root = pSon;
        }
        else//�и��ڵ�
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
        pSon->pParent = pFind->pParent;//���ĸ��ӹ�ϵ

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
    ɾ����3�����;
    1.ɾ���ڵ�����Ҷ����ֱ��ɾ��
    2.��ɾ���Ľڵ�ֻ��һ���ӽڵ㣬
    ��ʱֻ��Ҫ��ɾ���ڵ����һ���ڵ��ָ��ýڵ��ָ��ָ��ýڵ�Ψһ���ӽڵ�
    3.��ɾ���Ľڵ��������ӽڵ�
    */

    //ɾ��ͬ��
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //û��Ҷ�ӽڵ�,���Һ����ǿ�
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = nullptr;//ɾ��
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
    //���Һ����нڵ�,ȡ�����������ӽڵ��ɾ���ĸ��ڵ����滻,Ϊ���ڵ�
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//��������
        while (Max->pRight != nullptr)//�����������������ӽڵ�
        {
            Max = Max->pRight;
        }
        //�ҵ���͸��ڵ㽻��
        CCourseInformation Tmp = pFind->Cdata;
        pFind->Cdata = Max->Cdata;
        Max->Cdata = Tmp;

        //ɾ���ڵ�
        DeleteCourID(Max);
        // m_nSize--;
    }
    //ֻ��һ���ӽڵ�
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//����һ����������
        //Ҫô�����ֵ,Ҫô�ұ���ֵ
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //���¶��常�ӽڵ��ϵ,����ԭ���ĸ��ӹ�ϵ
        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = pSon;
        }
        else//�и��ڵ�
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
        pSon->pParent = pFind->pParent;//���ĸ��ӹ�ϵ

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
    ɾ����3�����;
    1.ɾ���ڵ�����Ҷ����ֱ��ɾ��
    2.��ɾ���Ľڵ�ֻ��һ���ӽڵ㣬
    ��ʱֻ��Ҫ��ɾ���ڵ����һ���ڵ��ָ��ýڵ��ָ��ָ��ýڵ�Ψһ���ӽڵ�
    3.��ɾ���Ľڵ��������ӽڵ�
    */

    //ɾ��ͬ��
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //û��Ҷ�ӽڵ�,���Һ����ǿ�
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = nullptr;//ɾ��
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
    //���Һ����нڵ�,ȡ�����������ӽڵ��ɾ���ĸ��ڵ����滻,Ϊ���ڵ�
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//��������
        while (Max->pRight != nullptr)//�����������������ӽڵ�
        {
            Max = Max->pRight;
        }
        //�ҵ���͸��ڵ㽻��
        CCourseInformation Tmp = pFind->Cdata;
        pFind->Cdata = Max->Cdata;
        Max->Cdata = Tmp;

        //ɾ���ڵ�
        DeleteCourName(Max);
        // m_nSize--;
    }
    //ֻ��һ���ӽڵ�
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//����һ����������
        //Ҫô�����ֵ,Ҫô�ұ���ֵ
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //���¶��常�ӽڵ��ϵ,����ԭ���ĸ��ӹ�ϵ
        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = pSon;
        }
        else//�и��ڵ�
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
        pSon->pParent = pFind->pParent;//���ĸ��ӹ�ϵ

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
    ɾ����3�����;
    1.ɾ���ڵ�����Ҷ����ֱ��ɾ��
    2.��ɾ���Ľڵ�ֻ��һ���ӽڵ㣬
    ��ʱֻ��Ҫ��ɾ���ڵ����һ���ڵ��ָ��ýڵ��ָ��ָ��ýڵ�Ψһ���ӽڵ�
    3.��ɾ���Ľڵ��������ӽڵ�
    */

    //ɾ��ͬ��
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //û��Ҷ�ӽڵ�,���Һ����ǿ�
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = nullptr;//ɾ��
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
    //���Һ����нڵ�,ȡ�����������ӽڵ��ɾ���ĸ��ڵ����滻,Ϊ���ڵ�
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//��������
        while (Max->pRight != nullptr)//�����������������ӽڵ�
        {
            Max = Max->pRight;
        }
        //�ҵ���͸��ڵ㽻��
        CRecord Tmp = pFind->Rdata;
        pFind->Rdata = Max->Rdata;
        Max->Rdata = Tmp;

        //ɾ���ڵ�
        DeleteRecStuID(Max);
        // m_nSize--;
    }
    //ֻ��һ���ӽڵ�
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//����һ����������
        //Ҫô�����ֵ,Ҫô�ұ���ֵ
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //���¶��常�ӽڵ��ϵ,����ԭ���ĸ��ӹ�ϵ
        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = pSon;
        }
        else//�и��ڵ�
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
        pSon->pParent = pFind->pParent;//���ĸ��ӹ�ϵ

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
    ɾ����3�����;
    1.ɾ���ڵ�����Ҷ����ֱ��ɾ��
    2.��ɾ���Ľڵ�ֻ��һ���ӽڵ㣬
    ��ʱֻ��Ҫ��ɾ���ڵ����һ���ڵ��ָ��ýڵ��ָ��ָ��ýڵ�Ψһ���ӽڵ�
    3.��ɾ���Ľڵ��������ӽڵ�
    */

    //ɾ��ͬ��
    CMyTreeNode* pTemp = pFind->pList;
    while (pTemp != nullptr)
    {
        CMyTreeNode* pTemp2 = pTemp;
        pTemp = pTemp->pList;
        delete pTemp2;
    }
    //û��Ҷ�ӽڵ�,���Һ����ǿ�
    if (pFind->pLeft == nullptr && pFind->pRight == nullptr)
    {

        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = nullptr;//ɾ��
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
    //���Һ����нڵ�,ȡ�����������ӽڵ��ɾ���ĸ��ڵ����滻,Ϊ���ڵ�
    else if (pFind->pLeft != nullptr && pFind->pRight != nullptr)
    {
        CMyTreeNode*Max = pFind->pLeft;//��������
        while (Max->pRight != nullptr)//�����������������ӽڵ�
        {
            Max = Max->pRight;
        }
        //�ҵ���͸��ڵ㽻��
        CRecord Tmp = pFind->Rdata;
        pFind->Rdata = Max->Rdata;
        Max->Rdata = Tmp;

        //ɾ���ڵ�
        DeleteRecCourID(Max);
        // m_nSize--;
    }
    //ֻ��һ���ӽڵ�
    else if (pFind->pLeft != nullptr || pFind->pRight != nullptr)
    {
        CMyTreeNode*pSon = nullptr;//����һ����������
        //Ҫô�����ֵ,Ҫô�ұ���ֵ
        if (pFind->pLeft != nullptr)
        {
            pSon = pFind->pLeft;
        }
        else
        {
            pSon = pFind->pRight;
        }

        //���¶��常�ӽڵ��ϵ,����ԭ���ĸ��ӹ�ϵ
        if (pFind->pParent == nullptr)//û�и��ڵ�
        {
            m_root = pSon;
        }
        else//�и��ڵ�
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
        pSon->pParent = pFind->pParent;//���ĸ��ӹ�ϵ

        AdjustHeight(pFind->pParent);
        delete pFind;
        m_nSize--;
    }
    return true;
}


//����
CMyTreeNode* CMyTree::findStuID(CStudent stu)//����ѧ��id����
{
    CMyTreeNode* pFind = m_root;

    while (pFind != nullptr)
    {
        if (stu.nID < pFind->data.nID)//��������С�ڸ��ڵ�����,������ӽڵ���
        {
            pFind = pFind->pLeft;
        }
        else if (stu.nID>pFind->data.nID)
        {
            pFind = pFind->pRight;//��������С�ڸ��ڵ�����,���ұ��ӽڵ���
        }
        else
        {
            //pFind ��Ӧ�Ľڵ�
            return pFind;
        }
    }
    return nullptr;
}

CMyTreeNode* CMyTree::findStuName(CStudent stu)//����ѧ�����ֲ���
{
    CMyTreeNode* pFind = m_root;
    string str1(stu.szName);
    string str2(pFind->data.szName);
    while (pFind != nullptr)
    {

        if (MyStr.Cmp(stu.szName ,pFind->data.szName)<0)//��������С�ڸ��ڵ�����,������ӽڵ���
        //if (str1<str2)
        //if (stu< pFind->data)
        {
            pFind = pFind->pLeft;
        }
        else if (MyStr.Cmp(stu.szName, pFind->data.szName)>0)
        //else if (str1>str2)
        //else if (stu > pFind->data)
        {
            pFind = pFind->pRight;//��������С�ڸ��ڵ�����,���ұ��ӽڵ���
        }
        else if (MyStr.Cmp(stu.szName, pFind->data.szName)==0)
        {
            //pFind ��Ӧ�Ľڵ�
            return pFind;
        }
    }
    return nullptr;
}

CMyTreeNode*CMyTree::findCourName(CCourseInformation Courdata)//���γ����ֲ���
{
        CMyTreeNode* pFind = m_root;
        string str1(Courdata.szCourseName);
        string str2(pFind->Cdata.szCourseName);
        while (pFind != nullptr)
        {

            if (MyStr.Cmp(Courdata.szCourseName, pFind->Cdata.szCourseName) < 0)//��������С�ڸ��ڵ�����,������ӽڵ���
            //if (str1<str2)
            //if (Courdata < pFind->Cdata)
            {
                pFind = pFind->pLeft;
            }
            else if (MyStr.Cmp(Courdata.szCourseName, pFind->Cdata.szCourseName) > 0)
            //else if (str1>str2)
            //else if (Courdata > pFind->Cdata)
            {
                pFind = pFind->pRight;//��������С�ڸ��ڵ�����,���ұ��ӽڵ���
            }
            else if (MyStr.Cmp(Courdata.szCourseName, pFind->Cdata.szCourseName) == 0)
            {
                //pFind ��Ӧ�Ľڵ�
                return pFind;
            }
        }
        return nullptr;
}

CMyTreeNode*CMyTree::findCourID(CCourseInformation data)//���γ�id����
{
    CMyTreeNode* pFind = m_root;

    while (pFind != nullptr)
    {
        if (data.nCourseID < pFind->Cdata.nCourseID)//��������С�ڸ��ڵ�����,������ӽڵ���
        {
            pFind = pFind->pLeft;
        }
        else if (data.nCourseID>pFind->Cdata.nCourseID)
        {
            pFind = pFind->pRight;//��������С�ڸ��ڵ�����,���ұ��ӽڵ���
        }
        else
        {
            //pFind ��Ӧ�Ľڵ�
            return pFind;
        }
    }
    return nullptr;
}

CMyTreeNode*CMyTree::findRecCourID(CRecord data)//��ѡ�μ�¼�γ���ID����
{
    CMyTreeNode* pFind = m_root;

    while (pFind != nullptr)
    {
        if (data.nCourseID < pFind->Rdata.nCourseID)//��������С�ڸ��ڵ�����,������ӽڵ���
        {
            pFind = pFind->pLeft;
        }
        else if (data.nCourseID>pFind->Rdata.nCourseID)
        {
            pFind = pFind->pRight;//��������С�ڸ��ڵ�����,���ұ��ӽڵ���
        }
        else
        {
            //pFind ��Ӧ�Ľڵ�
            return pFind;
        }
    }
    return nullptr;
}
CMyTreeNode*CMyTree::findRecStuID(CRecord data)//��ѡ�μ�¼ѧ��id����
{
    CMyTreeNode* pFind = m_root;

    while (pFind != nullptr)
    {
        if (data.nStuID < pFind->Rdata.nStuID)//��������С�ڸ��ڵ�����,������ӽڵ���
        {
            pFind = pFind->pLeft;
        }
        else if (data.nStuID>pFind->Rdata.nStuID)
        {
            pFind = pFind->pRight;//��������С�ڸ��ڵ�����,���ұ��ӽڵ���
        }
        else
        {
            //pFind ��Ӧ�Ľڵ�
            return pFind;
        }
    }
    return nullptr;
}
//ɾ��
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

bool CMyTree::DeleteCourID(CCourseInformation data)//���γ�idɾ��
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
   
bool CMyTree::DeleteCourName(CCourseInformation data)//���γ�����ɾ��
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

bool CMyTree::DeleteRecCourID(CRecord data)//��ѡ�μ�¼�γ�idɾ��
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
bool CMyTree::DeleteRecStuID(CRecord data)//��ѡ�μ�¼ѧ��idɾ��
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

����:                   ��:
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
    //����Ϊ����ѹ���,�ҵ�����������
    if (m_root!= nullptr)
    {  
        queue.push(m_root);
    }
    while (!queue.empty())
    {
        //ȡ���е�һ��Ԫ��,�ȴ���߿�ʼȡֵ,Ȼ���ұ�
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
        queue.pop();//������һ��
    }

}


//���ֲ�α���
void CMyTree::NameLayer()
{

    CMyQueue<CMyTreeNode*> queue;
    //CMyTreeNode* p= queue;
    //����Ϊ����ѹ���,�ҵ�����������
    if (m_root != nullptr)
    {
        queue.push(m_root);
    }
    while (!queue.empty())
    {
        //ȡ���е�һ��Ԫ��,�ȴ���߿�ʼȡֵ,Ȼ���ұ�
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
        queue.pop();//������һ��
    }

}
//ѧ����Ϣ�������
void CMyTree::StuLDR_stc(CMyTreeNode*pNode)
{
    CMyStack<CMyTreeNode*>stc;
    while (true)
    {

        while (pNode != nullptr)
        {
            stc.push(pNode);
            //(1)ѭ������(ѹջ)�������,��ջ
            pNode = pNode->pLeft;
        }

        if (stc.empty())//ջΪ��������ǰѭ��
        {
            break;
        }
        CMyTreeNode*pCur = stc.top();
        printf("%d-%s\n", pCur->data.nID, pCur->data.szName);

        stc.pop();
        //(2) �жϳ�ջ������ڵ���û���Һ���,����ִ�е�һ��
        pNode = pCur->pRight;

    }
}

//�γ���Ϣ�������
void CMyTree::CourLDR_stc(CMyTreeNode*pNode)
{
    CMyStack<CMyTreeNode*>stc;
    int n = 1;
    while (true)
    {

        while (pNode != nullptr)
        {
            stc.push(pNode);
            //(1)ѭ������(ѹջ)�������,��ջ
            pNode = pNode->pLeft;
        }

        if (stc.empty())//ջΪ��������ǰѭ��
        {
            break;
        }
        CMyTreeNode*pCur = stc.top();
        
        printf("%d-%s-%d\n", pCur->Cdata.nCourseID, pCur->Cdata.szCourseName,n);
        n++;
        stc.pop();
        //(2) �жϳ�ջ������ڵ���û���Һ���,����ִ�е�һ��
        pNode = pCur->pRight;

    }
}



//ѡ�μ�¼��α���
void CMyTree::RecLDR_stc(CMyTreeNode*pNode)
{
    CMyStack<CMyTreeNode*>stc;
    while (true)
    {

        while (pNode != nullptr)
        {
            stc.push(pNode);
            //(1)ѭ������(ѹջ)�������,��ջ
            pNode = pNode->pLeft;
        }

        if (stc.empty())//ջΪ��������ǰѭ��
        {
            break;
        }
        CMyTreeNode*pCur = stc.top();
        printf("%d-%d-%d\n", pCur->Rdata.nStuID, pCur->Rdata.nCourseID,pCur->Rdata.nScore);

        stc.pop();
        //(2) �жϳ�ջ������ڵ���û���Һ���,����ִ�е�һ��
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
ջ:                   ��:

ջ��---->ջ��
50
80  30             50
80  40  10         50  30
80  40             50  30  10
80                 50  30  10  40
70                 50  30  10  40  80
50  30  10  40  80  70
*/

//ǰ�����ջʵ��

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

//����ջʵ��
/*
       50
   30      80
10   40  70

10 30 40 50 70 80
ջ:                   ��:
ջ��---->ջ��
(1) ѭ������(ѹջ)�������,��ջ
(2) �жϳ�ջ������ڵ���û���Һ���,����ִ�е�һ��

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
            //(1)ѭ������(ѹջ)�������,��ջ
            pNode = pNode->pLeft;
        }
        
        if (stc.empty())//ջΪ��������ǰѭ��
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
                //(2) �жϳ�ջ������ڵ���û���Һ���,����ִ�е�һ��
                pNode = pCur->pRight;
     
    }
}


/*
       50
  30      80
10   40  70

10 40 30 70 80 50
ջ:                   ��:
ջ��---->ջ��
(1) ѭ������(ѹջ)�������,
(2) �ж�ջ���ڵ���û���Һ���,����ִ�е�һ��
(3) ���û���Һ���,���ջ��ӡ

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
//4.���������(�ǵݹ�ʵ��)
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
        if (stc.empty())//ջΪ��������ǰѭ��
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
            continue;//�ؼ�
        }
        pNode = pCur->pRight;
    }

}

//����
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
//����
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

//�ַ�����������ת
// void CMyTree::StrLeftRotate(CMyTreeNode*pK1, CMyTreeNode*pK2)
// {
//     //������ϵ
//     CMyTreeNode*pG = pK1->pParent;
//     CMyTreeNode*pA = pK1->pLeft;
//     CMyTreeNode*pB = pK2->pLeft;
//     CMyTreeNode*pC = pK2->pRight;
// 
//     //��  ƽ���
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
//     //������ϵ
//     CMyTreeNode*pG = pK1->pParent;
//     CMyTreeNode*pA = pK1->pRight;
//     CMyTreeNode*pB = pK2->pLeft;
//     CMyTreeNode*pC = pK2->pRight;
// 
//     //��  ƽ���
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

        //�ж�pNode�Ƿ�ƽ��
        if (abs(nLeftHeight - nRightHeight) > 1){
            //�����ƽ��,�ж���4����ת���������
            CMyTreeNode* pK1 = pNode;
            CMyTreeNode* pK2 = nullptr;
            CMyTreeNode* pK3 = nullptr;

            //�ұ�������
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
                ����:
                10  pK1
                20 pK2
                30 pK3
                */
                LeftRotate(pK1, pK2);
            }
            else if (pK1->pLeft == pK2 && pK2->pLeft == pK3){
                /*
                �ҵ���:
                30
                20
                10
                */
                RightRotate(pK1, pK2);
            }
            else if (pK1->pRight == pK2 && pK2->pLeft == pK3){
                /*
                R-L˫��:
                30  pK1
                50  pK2
                40   pK3
                */
                RightRotate(pK2, pK3);
                LeftRotate(pK1, pK3);
            }
            else if (pK1->pLeft == pK2 && pK2->pRight == pK3){
                /*
                L-R˫��:
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
//         //�ж�pNode�Ƿ�ƽ��
//         if (abs(nLeftHeight - nRightHeight) > 1){
//             //�����ƽ��,�ж���4����ת���������
//             CMyTreeNode* pK1 = pNode;
//             CMyTreeNode* pK2 = nullptr;
//             CMyTreeNode* pK3 = nullptr;
// 
//             //�ұ�������
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
//                 ����:
//                 10  pK1
//                 20 pK2
//                 30 pK3
//                 */
//                 StrLeftRotate(pK1, pK2);
//             }
//                 
//                 else if ((MyStr.Cmp(pK1->pLeft, pK2) = 0) && (MyStr.Cmp(pK2->pLeft, pK3) = 0)){
//                 /*
//                 �ҵ���:
//                 30
//                 20
//                 10
//                 */
//                 StrRightRotate(pK1, pK2);
//             }
//                 
//                 else if ((MyStr.Cmp(pK1->pRight, pK2) = 0) && (MyStr.Cmp(pK2->pLeft, pK3) = 0)){
//                 /*
//                 R-L˫��:
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
//                 L-R˫��:
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