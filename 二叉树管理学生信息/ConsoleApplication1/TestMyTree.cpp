// TestTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "common.h"
#include "MyTree.h"


int _tmain(int argc, _TCHAR* argv[])
{
    CMyTree tree;
    
    tree.Insert(50);

    tree.Insert(30);
    tree.Insert(80);

    tree.Insert(10);
    tree.Insert(40);

    tree.Insert(70);
    //tree.Delete(80);
    //tree.Layer();
    tree.LRD_stc(tree.GetRoot());
    return 0;
}

