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
    CMystring(const CMystring& obj);//���
    //CMystring(const char* pStr, int& n);

    //���������;      
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

    /* ��ʽ���ַ���������������printf�����ǽ��������m_pStr��*/
    int Format(const char* strFormat, ...);//ok

    /*�Ƴ��ַ�����β�Ŀո񣨰���\r \n \t�������磺"  hello  "�����ú��Ϊ"hello"*/
    void Strip();//ok

    /*�����ַ������ַ��������Ƴ��ַ����ʼ���β�����ַ������磺
    "abbbbccdd"���� .RightStrip("dc")���Ϊ�� "abbbb"
    */
    void LeftStrip(char *strStrip="\x20\n");
    void RightStrip(char *strStrip="\x20");

    /*
    �ж��ַ�����β�Ƿ����ַ����е��ַ���ʼ���߽�β
    �磺
    "hello"���� IsEndwith("h")���� false������IsStartWith("h")����true
    */
    bool IsEndwith(const char* chSet = NULL) const;
    bool IsStartWith(const char* chSet = NULL) const;

    /*
    ���ҵ�ǰCMyString���Ƿ����ָ�����ַ�����������ڣ��򷵻�ָ�����ַ�����m_pStr��ƫ��λ�ã�
    ��������ڣ��򷵻�0
    �磺
    "hello"���� FinSubstr("llo")�󣬷���2
    "hello"���� FinSubstr("no")�󣬷���0
    */
   int FindSubstr(char* strSub) const;


    /* ���ص�ǰ�ַ�������*/
    inline int GetStrlen() const    {
        return m_nLength;
    };


    /* �Ƚ��ַ������ο�strcmp */
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
    /* ����һ�������������С����ΪnMinBuffLen(���Դ���nMinBuffLen)�����GetBuffer(0)���򷵻�
    ��ǰ������*/
    //char* GetBuffer(int nMinBuffLen);

    /* ��ȡ��ǰm_pStr
    */
    //char* GetStr() const;
    
    /* ����CMyString�ַ���(ע�⿼�������õ��ַ���strSrc���ڵ�ǰ�����������)*/
    int SetStr(const char* strSrc);//ok

    /* ����strCat����ǰ��������strcat*/
    //void Cat(const char* strCat);
    void Cat(const CMystring &strCat);
    void Cat(const char* strCat);
    /* ��ʼ����������ʵ�ֲο���*/
    //void InitSelf();//ok
    /* �ͷ���������ʵ�ֲο��� */
    //void ReleaseSelf();//ok

    /* ���ַ���ȫ��תΪ��д */
    void ToUpper();//ok
    /* ���ַ���ȫ��תΪСд */
    void ToLower();//ok

private:
    char* m_szBuf;//������
    int m_nBuffLen;
    int   m_nLength;  //��ʾ�ַ�������
    int   m_nBufSize; //��ʾ��������С
    char* m_szStr;
    mutable int m_ntest;
    int*   m_pRef; //��ʾm_szBuf�����ü���
    //int& m_nRef;
    //const int m_nDefaultSize; //Ĭ�ϴ�С\

};

#endif // !defined(AFX_MYSTRING_H__D5CFEBE8_92E5_455C_A901_98FF06947F14__INCLUDED_)
