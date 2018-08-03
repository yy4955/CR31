// Mystring.cpp: implementation of the CMystring class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4996)
#include "stdafx.h"
#include "Mystring.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//:m_nDefaultSize(0xf), m_nRef(n)
CMystring::CMystring(/*int n*/)
{
    InitBuf(16/*m_nDefaultSize*/);
}


bool ReleaseBuf()
{
    printf("bool ReleaseBuf()\r\n");
    return true;
}
CMystring::~CMystring()
{
    ReleaseBuf();
}


CMystring::CMystring(const char* str)
{
    assert(str != NULL);//����
    int nLength = strlen(str) + 1;
    bool bRet = InitBuf(nLength * 2);
    if (!bRet)
    {
        return;
    }

    strcpy_s(m_szBuf, nLength, str);
    m_nLength = nLength;
}

//����ռ�
bool CMystring::InitBuf(int nSize)
{
    assert(nSize > 0);//����

    if (nSize <= 0)
    {
        return false;
    }

    m_nBufSize = 0;
    m_nLength = 0;

    m_szBuf = reinterpret_cast<char*>(malloc(nSize));
    if (m_szBuf == NULL)
    {
        return false;
    }

    m_nBufSize = nSize;

    return true;
}

bool CMystring::ReleaseBuf()
{
    if (m_szBuf != NULL)
    {
        free(m_szBuf);
        m_szBuf = NULL;
    }

    m_nLength = 0;
    m_nBufSize = 0;

    return true;
}

bool CMystring::SetString(const char* pStr)
{
    assert(pStr != NULL);//����
    int nLength = strlen(pStr) + 1;
    bool bRet = false;

    //�����ǰ��nLength > m_nBufSize;
    //��Ҫ���·���ռ�
    if (nLength > m_nBufSize)
    {
        bRet = ReleaseBuf();
        if (!bRet)
        {
            return false;
        }

        bRet = InitBuf(nLength * 2);
        if (!bRet)
        {
            return false;
        }
    }

    //��ʾ�ռ乻
    strcpy_s(m_szBuf, nLength, pStr);
    m_nLength = nLength;

    return true;
}

int CMystring::Format(const char* strFormat, ...)
{
    char* szTemp = NULL;
    va_list arglist;
    va_start(arglist, strFormat);
    char szBuf[1024] = { 0 };

    // 	char* arg1 = va_arg(arglist, char*);
    // 	int arg2 = va_arg(arglist, int);
    _vsnprintf_s(szBuf, 1024, strFormat, arglist);

    va_end(arglist);

    m_nLength = strlen(szTemp);

    if (m_nLength >= m_nBuffLen)
    {
        free(m_szStr);
        m_nBuffLen = m_nLength * 2;
        m_szStr = (char*)malloc(m_nBuffLen);
    }
    strcpy(m_szStr, szTemp);
    if (szTemp != NULL)
    {
        free(szTemp);
    }
    return 0;
}


void  CMystring::Strip()
{
   // char szTemStr[100] = "";
    int nLenStart = 0;
    int nLenEnd = 0;
    int nLen = 0;
    for (int i = 0; i < m_nLength; i++)
    {
        if (m_szStr[i] == ' ' || m_szStr[i] == '\r' ||
            m_szStr[i] == '\t' || m_szStr[i] == '\n')
        {
            continue;
        }
        else
        {
            nLenStart = i;
            break;
        }
    }
    for (int i = m_nLength ; i >= 0; i--)
    {
        if (m_szStr[i] == ' ' || m_szStr[i] == '\r' ||
            m_szStr[i] == '\t' || m_szStr[i] == '\n')
        {
            continue;
        }
        else
        {
            nLenEnd = i + 1;
            m_szStr[nLenEnd] = '\0';
            break;
        }
    }
    nLen = nLenEnd - nLenStart + 1;
    memmove(m_szStr, m_szStr, nLen);
    m_nLength = strlen(m_szStr) + 1;
}




void CMystring::ToLower()/* ���ַ���ȫ��תΪСд */
{
    for (int i = 0; i < m_nLength; i++)
    {
        if ((m_szStr[i] >= 'A') && (m_szStr[i] <= 'Z'))
        {
            m_szStr[i] += 32;
        }
    }
}

void CMystring::ToUpper()/* ���ַ���ȫ��תΪ��д */
{
    for ( int i = 0; i < m_nLength; i++)
    {
        if ((m_szStr[i] >= 'a') && (m_szStr[i] <= 'z'))
        {
            m_szStr[i] -= 32;
        }
    }
}

//�ַ���ƴ��
void CMystring::Cat(const char* strCat)
{
    char szTempBuf[1024] = { 0 };
    strcpy_s(szTempBuf, m_nLength, m_szBuf);
    for (unsigned int i = 0; i < strlen(strCat); i++)
    {
        szTempBuf[strlen(szTempBuf)] = strCat[i];
    }
    SetStr(szTempBuf);
}
void CMystring::Cat(const CMystring &strCat)
{
    char szTempBuf[1024] = { 0 };
    strcpy_s(szTempBuf, m_nLength, m_szBuf);
    for (unsigned int i = 0; i < strlen(strCat.m_szBuf); i++)
    {
        szTempBuf[strlen(szTempBuf)] = strCat.m_szBuf[i];
    }
    SetStr(szTempBuf);
}
//CMystring::CMystring(const char* strSrc)
//{
//    InitSelf();
//    SetStr(strSrc);
//}

int CMystring::SetStr(const char* strSrc)
{
    m_nLength = strlen(strSrc);
    int nLen = m_nLength + 1;
    if (nLen > m_nBuffLen)
    {
        free(m_szStr);
        m_nBuffLen = nLen * 2;
        m_szStr = (char*)malloc(m_nBuffLen);
    }
    if (m_szStr == NULL)
    {
        return 0;
    }
    strcpy_s(m_szStr, nLen, strSrc);
    return 1;
}


//���
CMystring::CMystring(const CMystring& obj)
{
    int nLength = obj.m_nLength;
    m_szBuf = obj.m_szBuf;
    m_pRef = obj.m_pRef;
    m_nBufSize = obj.m_nBufSize;

    //���ü���+1
    (*m_pRef)++;

}

char CMystring::operator[](int nIndex)
{
    return m_szBuf[nIndex];
}

const CMystring& CMystring::operator=(const CMystring &obj)
{
    printf("const CMystring CMystring::operator=(const CMystring &obj)\r\n");
    if (this == &obj)
    {
        return *this;
    }

    int nLen = obj.m_nLength;
    if (nLen > m_nBufSize)
    {
        ReleaseBuf();
        if (InitBuf(obj.m_nBufSize) == false)
        {
            return *this;
        }
    }

    m_nLength = obj.m_nLength;
    strcpy_s(m_szBuf, m_nLength, obj.m_szBuf);
    return *this;
}

CMystring operator+(CMystring &obj1, CMystring &obj2)
{
    CMystring str = obj1;
    str.Cat(obj2);
    return str;
}

//�Ƚ��ַ���
//��� 0 С�� ���� ���� ����
// int CMystring::Cmp(const char* strSrc) const
// {
//     int i = 0;
//     for (; i < m_nLength - 1; i++)
//     {
//         if (m_szBuf[i] != strSrc[i])
//         {
//             return m_szBuf[i] - strSrc[i];
//         }
//     }
//     return m_szBuf[i] - strSrc[i];
// }
// bool CMystring::Cmp(string s1, string s2)
// {
// 
//     int len1 = s1.size();
//     int len2 = s2.size();
//     int i = 0;
//     while (i < len1 && i < len2)
//     {
//         if (s1[i] == s2[i])
//         {
//             i++;
//         }
//         else
//         {
//             if (s1[i] < s2[i])
//             {
//                 return true;
//             }
//             else if (s1[i] > s2[i])
//             {
//                 return false;
//             }
//         }
//     }
// }
//�Ƚ��ַ���
//��� 0 С�� ���� ���� ����
// int CMystring::Cmp(const CMystring &strCmp) const
// {
//     int i = 0;
//     for (; i < m_nLength - 1; i++)
//     {
//         if (m_szBuf[i] != strCmp.m_szBuf[i])
//         {
//             return m_szBuf[i] - strCmp.m_szBuf[i];
//         }
//     }
//     return m_szBuf[i] - strCmp.m_szBuf[i];
// }

/*
���ҵ�ǰCMyString���Ƿ����ָ�����ַ�����������ڣ��򷵻�ָ�����ַ�����m_pStr��ƫ��λ�ã�
��������ڣ��򷵻�0
�磺
"hello"���� FinSubstr("llo")�󣬷���2
"hello"���� FinSubstr("no")�󣬷���0
*/

int CMystring::FindSubstr(char* strSub) const
{
    int nSubLen = strlen(strSub);
    int nIndex = 10000;
    int nCount = 0;
    int j = 0;
    if (m_nLength >= (nSubLen + 1))
    {
        for (int i = 0; i < nSubLen; i++)
        {
            for (; j < m_nLength - 1; j++)
            {
                if (strSub[i] == m_szBuf[j])
                {
                    if (nIndex > j)
                    {
                        nIndex = j;
                    }

                    if (nCount == nSubLen - 1)
                    {
                        return nIndex;
                    }
                    else
                    {
                        nCount++;
                        j++;
                    }
                    break;
                }
                else
                {
                    nCount = 0;
                }
            }
        }
    }
    return -1;
}
/*
�ж��ַ�����β�Ƿ����ַ����е��ַ���ʼ���߽�β
�磺
"hello"���� IsEndwith("h")���� false������IsStartWith("h")����true
*/
bool CMystring::IsEndwith(const char* chSet) const
{
    for (unsigned int i = 0; i < strlen(chSet); i++)
    {
        if (m_szBuf[m_nLength - 2] == chSet[i])
        {
            return true;
        }
    }
    return false;
}

bool CMystring::IsStartWith(const char* chSet) const
{
    for (unsigned int i = 0; i < strlen(chSet); i++)
    {
        if (m_szBuf[0] == chSet[i])
        {
            return true;
        }
    }
    return false;
}

/*�����ַ������ַ��������Ƴ��ַ����ʼ���β�����ַ������磺
"abbbbccdd"���� .RightStrip("dc")���Ϊ�� "abbbb"
*/
void CMystring::LeftStrip(char *strStrip)
{
    char szTemp[512] = { 0 };
    int k = 0;
    int j = 0;
    for (unsigned int i = 0; i < strlen(strStrip); i++)
    {
        for (; j < m_nLength - 1;)
        {
            if (m_szBuf[j] == strStrip[i])
            {
                j++;
                k++;
            }
            else
            {
                break;
            }
        }
    }
    memmove(szTemp, m_szBuf + k, m_nLength - k);
    SetStr(szTemp);
}

void CMystring::RightStrip(char *strStrip)
{
    char szTemp[512] = { 0 };
    int k = 0;
    int j = m_nLength - 2;
    for (unsigned int i = 0; i < strlen(strStrip); i++)
    {
        for (; j >= 0;)
        {
            if (m_szBuf[j] == strStrip[i])
            {
                j--;
                k++;
            }
            else
            {
                break;
            }
        }
    }
    memmove(szTemp, m_szBuf, m_nLength - k - 1);
    SetStr(szTemp);
}