#include <iostream>
#include <fstream>
#include <string>
#include "Queue.cpp"
#include "Window.h"

using namespace std;

void collectData(string file);
void addStudents(int time, int num, DoublyLL<Student> &students, ifstream &fin, int &studNum);
void runProgram(Window *windows, int numWindows, Student *students, int studentSize);
void calculate(Window *windows, int numWindows, Student *students, int studentSize);

int main(int argc, char** argv)
{
  string fileName = "";
  if(argc >= 2)
  {
    fileName = argv[1];
  }
  else
  {
    cout<<"No file input given"<<endl;
    exit(1);
  }

  collectData(fileName);


  return 0;
}


void collectData(string file)
{

  DoublyLL<Student> students;
  int studentNum = 0;
  ifstream fin;
  fin.open(file);
  if (fin.fail( ))
  {
    cout << "Input file opening failed.\n"<<endl;
    exit(1);
  }

   string line;
   int numWindows = 0;
   int timeOfArrival = 0;
   int numStudents = 0;

   getline(fin,line);

   numWindows = atoi(line.c_str());

   Window *windows;
   windows = new Window[numWindows];
   Window *temp;
   for(int i = 0; i<numWindows; i++)
   {
     temp = new Window();
     windows[i] = *temp;
   }

   //while the input is not at the end of file
  while (getline(fin,line))
  {

    timeOfArrival = atoi(line.c_str());
    getline(fin,line);
    numStudents = atoi(line.c_str());
    addStudents(timeOfArrival, numStudents, students, fin, studentNum);
  }

  Student *studs;
  studs = new Student[students.getSize()];
  ListNode<Student> *tempStud = students.getFront();
  for(int k = 0; k<students.getSize(); ++k)
  {
    studs[k] = tempStud->data;
    studs[k].studentNum = k;
    tempStud = tempStud->next;
  }


  runProgram(windows, numWindows, studs, students.getSize());


}

void addStudents(int time, int num, DoublyLL<Student> &students, ifstream &fin, int &studNum)
{
  string line;
  for(int i = 0; i<num; ++i)
  {
    getline(fin,line);
    Student temp(time, atoi(line.c_str()),studNum);
    students.insertBack(temp);
    studNum++;
  }
}

void runProgram(Window *windows, int numWindows, Student *students, int studentSize)
{
  Queue<Student> waitLine;
  int studentsArrived = 0;
  int minute = 0;
  int windowsOpen = 0;


  while(waitLine.isEmpty() != true || windowsOpen!=numWindows || studentsArrived != studentSize)
  {
    //shift arriving students from LL to Queue
    for(int a = 0; a<studentSize; ++a)
    {
      if(students[a].entranceTime == minute)
      {
        waitLine.insert(students[a]);

      }
    }


    //update windows and set windowsOpen
    windowsOpen = 0;
    for(int i = 0; i<numWindows; ++i)
    {

      if(windows[i].occupied == false)
      {
        windows[i].waitTime++;
        windowsOpen++;
      }
      else
      {
        windows[i].currentStudent.timeNeeded--;
        if(windows[i].currentStudent.timeNeeded==0) //student can leave window
        {
          windows[i].occupied = false;
          windowsOpen++;
        }
      }
    }

    //send students to open windows
    int j = 0;
    while(windowsOpen!=0&&waitLine.isEmpty()==false)
    {
        if(windows[j].occupied==false)
        {

          windows[j].currentStudent = waitLine.remove();
          windows[j].occupied = true;
          windowsOpen--;
          studentsArrived++;

        }
        ++j;
    }

    //increment the wait time of waiting students

    if(waitLine.isEmpty()!=true)
    {
      int lineSize = waitLine.getSize();
      for(int k = 0; k<lineSize; ++k)
      {
        Student temp = waitLine.remove();
        students[temp.studentNum].waitTime++;

        waitLine.insert(temp);
      }
    }

    minute++;
  }

  calculate(windows, numWindows, students, studentSize);
}

void calculate(Window *windows, int numWindows, Student *students, int studentSize)
{
  int windSum = 0;
  int studSum = 0;
  bool valueInserted = false;
  Queue<Student> orderedStudent;
  Queue<Window> orderedWindow;
  for(int i = 0; i<numWindows; ++i)
  {
    windSum += windows[i].waitTime;
  }
  for(int j = 0; j<studentSize; ++j)
  {
    studSum += students[j].waitTime;
  }

  Window tmp;

  for (int i = 0; i < numWindows; i++)
  {
    for (int j = i + 1; j < numWindows; j++)
    {
      if (windows[i].waitTime > windows[j].waitTime)
      {
        tmp = windows[i];
        windows[i] = windows[j];
        windows[j] = tmp;
      }
    }
  }
  Student temp;
  for (int i = 0; i < studentSize; i++)
  {
    for (int j = i + 1; j < studentSize; j++)
    {
      if (students[i].waitTime > students[j].waitTime)
      {
        temp = students[i];
        students[i] = students[j];
        students[j] = temp;
      }
    }
  }
  cout<<"Average Window Idle Time: "<<windSum/numWindows<<endl;

  cout<<"Average Student Wait Time: "<<studSum/studentSize<<endl;

  //calculate and display median

  double medianWin;
  if (numWindows % 2 == 0)
      medianWin = ((double)windows[numWindows/2].waitTime + (double)windows[numWindows/2 - 1].waitTime)/2;
  else
      medianWin = (double) windows[numWindows/2].waitTime;

  double medianStud;
  if (studentSize % 2 == 0)
      medianStud = ((double)students[studentSize/2].waitTime + (double)students[studentSize/2 - 1].waitTime)/2;
  else
      medianStud = (double) students[studentSize/2].waitTime;

  cout<<"Median Window Idle Time: "<<medianWin<<endl;
  cout<<"Median Student Wait Time: "<<medianStud<<endl;

  //display longest wait and idle times
  cout<<"Longest Window Idle Time: "<<windows[numWindows-1].waitTime<<endl;
  cout<<"Longest Student Wait Time: "<<students[studentSize-1].waitTime<<endl;

  //calculate and display window waiting over 5 minutes
  int idleLong = 0;
  for(int i = 0; i<numWindows; ++i)
  {
    if(windows[i].waitTime > 5)
    {
      idleLong++;
    }
  }
  cout<<"Number of Windows Idle for more than 5 minutes: "<<idleLong<<endl;
  //calculate and display students waiting over 10 minutes
  int waitLong = 0;
  for(int j = 0; j<studentSize; ++j)
  {
    if(students[j].waitTime > 10)
    {
      waitLong++;
    }
  }

  cout<<"Number of Students waiting for more than 10 minutes: "<<waitLong<<endl;

}
