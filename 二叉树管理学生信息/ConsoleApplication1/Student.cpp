
#include "stdafx.h"
#include "Student.h"

CStudent::CStudent(int ID, char* name){
//     nID = ID;
//     memmove((void*)szName, (void*)name, sizeof(name));
   
    nID = ID;
    strcpy(szName, name);
}

CStudent::~CStudent(){}