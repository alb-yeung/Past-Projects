#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Course{
 public:
  string courseName;
  int credits; // ranging from 1 to 4
  int offered; // 0 is spring 1 is fall 2 is both
  string tags;
  vector<string> prereqs;


  /*change pointer type later*/
  //void * graphLocation;

  Course();
};
