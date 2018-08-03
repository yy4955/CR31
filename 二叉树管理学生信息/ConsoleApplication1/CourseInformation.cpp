#include "stdafx.h"
#include "CourseInformation.h"
#include "Mystring.h"

CCourseInformation::CCourseInformation()
{

}

CCourseInformation::CCourseInformation(int ID, char*name)
{
    nCourseID = ID;
    strcpy(szCourseName, name);
    /*memmove((void*)szCourseName, (void*)name, sizeof(name));*/
}

CCourseInformation::~CCourseInformation()
{

}