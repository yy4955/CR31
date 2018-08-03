// Mystring.h: interface for the CMystring class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSTRING_H__D5CFEBE8_92E5_455C_A901_98FF06947F14__INCLUDED_)
#define AFX_MYSTRING_H__D5CFEBE8_92E5_455C_A901_98FF06947F14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMystring  
{
public:
    CMystring();
    CMystring(const char* pStr);
    //CMystring(int n);
    CMystring(const CMystring& obj);//深拷贝
    //CMystring(const char* pStr, int& n);

    //运算符重载;      
    char operator[](int nIndex);
    const CMystring& operator=(const CMystring& obj);
    friend CMystring operator+(CMystring &obj1, CMystring &obj2);

    ~CMystring();

    bool InitBuf(int nSize);
    bool ReleaseBuf();
   // friend CMystring operator+(const CMystring& string1, const CMystring& string2);

    const char* GetBuffer() { return m_szBuf; }
    int GetLength() const {
        //CMyString* p = this;
        //m_nLength = 1;
        m_ntest = 123;
        return m_nLength;
    }

    bool SetString(const char* pStr);

    /* 格式化字符串，功能类似于printf，但是结果保存在m_pStr中*/
    int Format(const char* strFormat, ...);//ok

    /*移除字符串首尾的空格（包括\r \n \t），例如："  hello  "，调用后变为"hello"*/
    void Strip();//ok

    /*根据字符集（字符串），移除字符串最开始或结尾处的字符，例如：
    "abbbbccdd"经过 .RightStrip("dc")后变为： "abbbb"
    */
    void LeftStrip(char *strStrip="\x20\n");
    void RightStrip(char *strStrip="\x20");

    /*
    判断字符串首尾是否是字符集中的字符开始或者结尾
    如：
    "hello"调用 IsEndwith("h")返回 false，调用IsStartWith("h")返回true
    */
    bool IsEndwith(const char* chSet = NULL) const;
    bool IsStartWith(const char* chSet = NULL) const;

    /*
    查找当前CMyString中是否存在指定子字符串，如果存在，则返回指定子字符串在m_pStr的偏移位置，
    如果不存在，则返回0
    如：
    "hello"调用 FinSubstr("llo")后，返回2
    "hello"调用 FinSubstr("no")后，返回0
    */
   int FindSubstr(char* strSub) const;


    /* 返回当前字符串长度*/
    inline int GetStrlen() const    {
        return m_nLength;
    };


    /* 比较字符串，参考strcmp */
  //  bool Cmp(string s1, string s2) ;
    
    int  Cmp(const char * src,const char * dst)
    {
        int ret = 0;

        while (!(ret = *(unsigned char *)src - *(unsigned char *)dst) && *dst)
            ++src, ++dst;

        if (ret < 0)
            ret = -1;
        else if (ret > 0)
            ret = 1;

        return(ret);
    }
    /* 返回一个缓冲区，其大小最少为nMinBuffLen(可以大于nMinBuffLen)。如果GetBuffer(0)，则返回
    当前缓冲区*/
    //char* GetBuffer(int nMinBuffLen);

    /* 获取当前m_pStr
    */
    //char* GetStr() const;
    
    /* 设置CMyString字符串(注意考虑新设置的字符串strSrc大于当前缓冲区的情况)*/
    int SetStr(const char* strSrc);//ok

    /* 连接strCat到当前对象，类似strcat*/
    //void Cat(const char* strCat);
    void Cat(const CMystring &strCat);
    void Cat(const char* strCat);
    /* 初始化自身（已有实现参考）*/
    //void InitSelf();//ok
    /* 释放自身（已有实现参考） */
    //void ReleaseSelf();//ok

    /* 将字符串全部转为大写 */
    void ToUpper();//ok
    /* 将字符串全部转为小写 */
    void ToLower();//ok

private:
    char* m_szBuf;//缓冲区
    int m_nBuffLen;
    int   m_nLength;  //表示字符串长度
    int   m_nBufSize; //表示缓冲区大小
    char* m_szStr;
    mutable int m_ntest;
    int*   m_pRef; //表示m_szBuf的引用计数
    //int& m_nRef;
    //const int m_nDefaultSize; //默认大小\

};

#endif // !defined(AFX_MYSTRING_H__D5CFEBE8_92E5_455C_A901_98FF06947F14__INCLUDED_)
