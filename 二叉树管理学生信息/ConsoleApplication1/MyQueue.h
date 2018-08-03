#pragma once
#include <string>
#include "common.h"
#include <assert.h>


//�Լ��Ķ���
template<typename T>
struct TagNode{
    TagNode(){
        pNext = nullptr;
    }

    TagNode(T d){
        pNext = nullptr;
        data = d;
    }
    TagNode<T>* pNext;
    T   data;
};

 template<typename T>
class CMyQueue
{
public:
    CMyQueue();
    virtual ~CMyQueue();

    void push(T data);//�������
   
    bool pop();//������

    T front();//����Ԫ��

    int size();//���д�С
  
    bool empty();//�ж϶����Ƿ�Ϊ��
    

private:
    TagNode<T>* m_pHead;
    TagNode<T>* m_pTail;

    int    m_Size;
};

//�����ʼ��
template<typename T>
CMyQueue<T>::CMyQueue() :m_pHead(nullptr), m_pTail(nullptr), m_Size(0)
{
    m_pHead = new TagNode<T>();
    m_pTail = m_pHead;
    m_Size = 0;
}


//��������
template<typename T>
CMyQueue<T>::~CMyQueue()
{
    while (m_pHead->pNext!=nullptr)
    {
        TagNode<T>* pNode = m_pHead;
        m_pHead = m_pHead->pNext;
    }
    m_Size = 0;
}

template<typename T>
void CMyQueue<T>::push(T data)//�������
{
    TagNode<T>* pNew = new TagNode<T>(data);
    if (pNew == NULL)
    {
        std::string strError;
        OUTPUTDBG("new error", strError)
            throw CMyException(strError.c_str());
    }
    m_pTail->pNext = pNew;
    m_pTail = pNew;
    m_Size++;
}

template<typename T>
bool CMyQueue<T>::pop()//������
{
    TagNode<T>* pNew = m_pHead->pNext;
    if (m_Size != 0);
    {
        m_pHead->pNext = m_pHead->pNext->pNext;
        delete pNew;
        m_Size--;
        return true;
    }
    return false;

}

template<typename T>
T CMyQueue<T>::front()//����Ԫ��
{
    return m_pHead->pNext->data;
}

template<typename T>
int CMyQueue<T>::size()//���д�С
{
    return m_Size;
}
template<typename T>
bool CMyQueue<T>::empty()//�ж϶����Ƿ�Ϊ��
{
    if (m_Size == 0)
    {
        return true;
    }
    return false;
}
