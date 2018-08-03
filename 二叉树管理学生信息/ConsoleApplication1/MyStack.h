#pragma once
#include "common.h"
#include <assert.h>
//自己的栈
template<typename T>
struct Node{
    Node(){
        pNext = nullptr;
    }

    Node(T d){
        pNext = nullptr;
        data = d;
    }
    Node<T>* pNext;
    T   data;
};

template<typename T>
class CMyStack
{
public:
    CMyStack();
    virtual ~CMyStack();

    bool empty();//判断队列是否为空
    
    int size();//栈大小

    void push(T data);//压栈

    T pop();//出栈

    T top();//栈顶
private:
    Node<T>* m_pHead;
    int m_Size;
};

template<typename T>
CMyStack<T>::CMyStack()
{
    m_pHead = new Node<T>();
    m_Size = 0;
}

template<typename T>
CMyStack<T>::~CMyStack()
{
    while (m_pHead->pNext != nullptr)
    {
        Node<T>* pNode = m_pHead->pNext;//第一个元素
        m_pHead->pNext = pNode->pNext;
        delete pNode;
    }
    m_Size = 0;
}

template<typename T>
bool CMyStack<T>::empty()//判断队列是否为空
{
    return size() == 0 ? true : false;
}

template<typename T>
int CMyStack<T>::size()//栈大小
{
    return m_Size;
}

template<typename T>
void CMyStack<T>::push(T data)//压栈
{
    Node<T>* pNew = new Node<T>(data);
    if (pNew==NULL)
    {
        std::string strError;
        OUTPUTDBG("new error", strError)
            throw CMyException(strError.c_str());
    }
    pNew->pNext = m_pHead->pNext;
    m_pHead->pNext = pNew;
    m_Size++;
}

template<typename T>
T  CMyStack<T>::pop()//出栈
{
    Node<T>* pNode = m_pHead->pNext;
    if (m_pHead->pNext!=nullptr)
    {
        m_pHead->pNext = m_pHead->pNext->pNext;
        T data = pNode->data;
        delete pNode;
        m_Size--;
        return data;
    }
}

template<typename T>
T CMyStack<T>::top()//栈顶
{
    if (m_pHead->pNext!=nullptr)
    {
        return m_pHead->pNext->data;
    }
}