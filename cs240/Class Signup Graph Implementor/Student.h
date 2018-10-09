#include "CourseMap.h"
//#include "requirements.h"
#include "Reqs.h"
#include <vector>

using namespace std;

typedef unordered_map<string, int> classTable;

class Student{
 private:
  classTable taken; //hashtable for quick searches for classes already taken
  Reqs* prereqsGraph;
  //requirements r;
  CourseMap table;
  int totalCredits;
  int totalC, totalH, totalF;
  
 public:
  string errorMessage;
  Student();
  Student(Reqs* r, CourseMap c);
  /*
    Input is course name (CS101)
    Returns whether or not all the prereqs to that course have been fulfilled
    Returns 0 if all prereqs are taken and course is given at that time
    Returns 1 if prereqs are not fulfilled
    Returns 2 if not offered at that time
   */
  int* checkClass(string courseName, int time);
  /*
    Input is file name
    Checks line by line so on
    Prints out errorMessage at the end of the function
   */
  void calculateSchedule(string inputFile);
  vector<string> reorderSchedule(string inputFile);
  
};
