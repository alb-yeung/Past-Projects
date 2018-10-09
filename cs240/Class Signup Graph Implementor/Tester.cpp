#include "Student.h"

using namespace std;

int main(){
  CourseMap map = CourseMap();
  map.load("input.txt");
  Reqs* r = new Reqs();
  r->load("ReqsInput.txt");
  Student s = Student(r, map);
  s.calculateSchedule("scheduleInput.txt");
  return 0;
}
