#include "CourseMap.h"

using namespace std;

CourseMap::CourseMap(){
  table = courseTable();
}

void CourseMap::load(string input){
  ifstream f(input);
  if (f.fail()){
    cout << "File not found" << endl;
    return;
  }
  
  string::size_type sz;
  string data;
  string cn, tags;
  int credits, offered;
  stringstream stream;
  
  //initialize data to first line -> runs until data is empty
  for (getline(f, data, '\n'); data != ""; getline(f, data, '\n')){
    stream = stringstream(data);
    getline(stream, data, ' ');
    cn = data;
    getline(stream, data, ' ');
    credits = stoi(data, &sz);
    getline(stream, data, ' ');
    if (data == "S") offered = 0;
    if (data == "F") offered = 1;
    if (data == "E") offered = 2;
    getline(stream, data, ' ');
    if (data == "S" || data == "F" || data == "E") tags = "";
    else tags = data;

    Course temp = Course();
    temp.courseName = cn;
    temp.credits = credits;
    temp.offered = offered;
    temp.tags = tags;

    table[cn] = temp;
  }
}

void CourseMap::read(){
  for (auto it = table.begin(); it != table.end(); ++it){
    cout << it->first << " : " << (it->second).courseName << " " << (it->second).credits << " " << (it->second).offered << " " << (it->second).tags << endl; 
  }
  return;
}

CourseMap::CourseMap(string input){
  table = courseTable();
  load(input);
}

Course & CourseMap::operator[] (string key){
  return table[key];
}
