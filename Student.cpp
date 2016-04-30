#include "Student.h"
#include <iostream>

Student::Student()
{
  waitTime = 0;
  timeNeeded = 0;
  entranceTime = 0;
  studentNum = 0;
}

Student::Student(int e, int t, int num)
{
  waitTime = 0;
  timeNeeded = t;
  entranceTime = e;
  studentNum = num;
}

Student::~Student()
{

}
