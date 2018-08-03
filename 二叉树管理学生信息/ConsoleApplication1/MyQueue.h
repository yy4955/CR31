#pragma once
#include <string>
#include "common.h"
#include <assert.h>


//自己的队列
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

    void push(T data);//进入队列
   
    bool pop();//出队列

    T front();//队首元素

    int size();//队列大小
  
    bool empty();//判断队列是否为空
    

private:
    TagNode<T>* m_pHead;
    TagNode<T>* m_pTail;

    int    m_Size;
};

//构造初始化
template<typename T>
CMyQueue<T>::CMyQueue() :m_pHead(nullptr), m_pTail(nullptr), m_Size(0)
{
    m_pHead = new TagNode<T>();
    m_pTail = m_pHead;
    m_Size = 0;
}


//析构函数
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
void CMyQueue<T>::push(T data)//进入队列
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
bool CMyQueue<T>::pop()//出队列
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
T CMyQueue<T>::front()//队首元素
{
    return m_pHead->pNext->data;
}

template<typename T>
int CMyQueue<T>::size()//队列大小
{
    return m_Size;
}
template<typename T>
bool CMyQueue<T>::empty()//判断队列是否为空
{
    if (m_Size == 0)
    {
        return true;
    }
    return false;
}
