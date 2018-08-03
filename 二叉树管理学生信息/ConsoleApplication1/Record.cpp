#include "stdafx.h"
#include "Record.h"

CRecord::CRecord()
{
}

CRecord::CRecord(int stuID, int CourseID, int Scorse){
    nStuID = stuID;
    nCourseID = CourseID;
    nScore = Scorse;
}

CRecord::~CRecord()
{
}
