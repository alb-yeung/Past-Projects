#include <fstream>
#include <unordered_map>
#include "Course.h"
#include <sstream>

using namespace std;

typedef unordered_map<string, Course> courseTable;

class CourseMap{
 private:
  courseTable table;
 public:
  CourseMap();
  CourseMap(string input);
  void load(string input);
  void read();
  Course & operator[] (string key);
  
};
