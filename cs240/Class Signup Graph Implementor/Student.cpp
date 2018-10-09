#include "Student.h"

using namespace std;

Student::Student(){
  taken = classTable();
  totalCredits = 0;
  totalC = 0;
  totalH = 0;
  totalF = 0;
  errorMessage = "Bad plan. Here's why:\n";
  table = CourseMap();
  prereqsGraph = new Reqs();
  
}

Student::Student(Reqs* r, CourseMap c){
  taken = classTable();
  prereqsGraph = r;
  table = c;
  totalCredits = 0;
  totalC = 0;
  totalH = 0;
  totalF = 0;
  errorMessage = "Bad plan. Here's why:\n";
}

/*
  time is 0 if spring, 1 if fall
  Returns 0 if all prereqs are taken and course is given at that time
  Returns 1 if prereqs are not fulfilled
  Returns 2 if not offered at that time
*/
int* Student::checkClass(string courseName, int time){
  /*
    If not offered at time return 2
    Search up graph location in courseMap
       -> traverse all of prereqs
           ->for each prereq check if taken/being taken
	        ->if not return 1
    else return 0
   */
  //{if possible message, total credits, totalC, totalH, totalF}
  int* retData = new int[5];
  
  taken[courseName] = 1;

  retData[0] = 0;
  retData[1] = 0;
  retData[2] = 0;
  retData[3] = 0;
  retData[4] = 0;
  if (time != (table[courseName]).offered && (table[courseName]).offered != 2) retData[0] = 2;

  retData[1] = (table[courseName]).credits;
  if ((table[courseName]).tags.find('C') != -1) retData[2] = retData[1];
  if ((table[courseName]).tags.find('H') != -1) retData[3] = retData[1];
  if ((table[courseName]).tags.find('F') != -1) retData[4] = retData[1];

  //prereqs checker
  //ReqsNode* c = (prereqsGraph->locations)[courseName];
  //cout << c->courseName << endl;
  //vector<ReqsNode*>::iterator it;
  //it = (c->reqs).begin();
  //cout << "Course checking is - " << courseName << endl;
  //for (vector<ReqsNode*>::iterator it = prereqs.begin(); it < prereqs.end(); it++){
  //  cout << *it << endl;
    //cout << (*it)->courseName << endl;
    /*
    if (taken.count((*it)->courseName) == 0){
      retData[0] = 1;
    } */
  //}

  return retData;
}

vector<string> Student::reorderSchedule(string inputFile){
  ifstream f(inputFile);
  vector<string> temp;
  string data;
  string year1;
  string year2;
  vector<string>::iterator it;
  for (getline (f, data, '\n'); data != ""; getline(f, data, '\n')){
    for (it = temp.begin(); it < temp.end(); it++){
      year1 = data[1]+data[2]+data[3]+data[4];
      year2 = (*it)[1]+(*it)[2]+(*it)[3]+(*it)[4];
      if (year1 > year2){
	continue;
      }
      if (year1 == year2){
	if (data[0] == 'S'){
	  temp.insert(it, data);
	}
	else{
	  it++;
	  temp.insert(it, data);
	}
      }
      if (year1 < year2){
	temp.insert(it, data);
      }
      break;
    }
    if (it == temp.end()) temp.push_back(data);
  }
  return temp;
}

void Student::calculateSchedule(string inputFile){
  ifstream f(inputFile);
  if (f.fail()){
    cout << "Schedule file not found" << endl;
    return;
  }

  vector<string> ordered = reorderSchedule(inputFile);
  
  string data;
  stringstream stream;
  int semester; // 0 if spring 1 if fall
  int* temp;
  /*
    for each line store time and add to Student's taken table
    go through each course one by one and checkClass on every one
       -> add to errorMessage if needed
    at end if all credits add up change errorMessage to "Good plan. Get to work."
   */
  for (vector<string>::iterator it = ordered.begin(); it < ordered.end(); it++){
    cout << *it << endl;
    stream = stringstream(*it);
    getline(stream, data, ' ');
    if (data[0] == 'S') semester = 0;
    else semester = 1;

    getline(stream, data, ' ');
    temp = checkClass(data, semester);
    totalCredits += temp[1];
    totalC += temp[2];
    totalH += temp[3];
    totalF += temp[4];
    if (temp[0]){
      if (temp[0] == 1) errorMessage += "Not all of the prereqs for " + data + " are completed.\n";
      if (temp[0] == 2) errorMessage += data + " is not offered at that time.\n";
    }

    getline(stream, data, ' ');
    temp = checkClass(data, semester);
    totalCredits += temp[1];
    totalC += temp[2];
    totalH += temp[3];
    totalF += temp[4];
    if (temp[0]){
      if (temp[0] == 1) errorMessage += "Not all of the prereqs for " + data + " are completed.\n";
      if (temp[0] == 2) errorMessage += data + " is not offered at that time.\n";
    }

    getline(stream, data, ' ');
    temp = checkClass(data, semester);
    totalCredits += temp[1];
    totalC += temp[2];
    totalH += temp[3];
    totalF += temp[4];
    if (temp[0]){
      if (temp[0] == 1) errorMessage += "Not all of the prereqs for " + data + " are completed.\n";
      if (temp[0] == 2) errorMessage += data + " is not offered at that time.\n";
    }

    getline(stream, data, ' ');
    temp = checkClass(data, semester);
    totalCredits += temp[1];
    totalC += temp[2];
    totalH += temp[3];
    totalF += temp[4];
    if (temp[0]){
      if (temp[0] == 1) errorMessage += "Not all of the prereqs for " + data + " are completed.\n";
      if (temp[0] == 2) errorMessage += data + " is not offered at that time.\n";
    }
  }

  if (totalCredits < prereqsGraph->totalCredits) errorMessage += "Not enough total credits\n";
  if (totalC < prereqsGraph->totalC) errorMessage += "Not enough C credits\n";
  if (totalH < prereqsGraph->totalH) errorMessage += "Not enough H credits\n";
  if (totalF < prereqsGraph->totalF) errorMessage += "Not enough F credits\n";

  for (vector<string>::iterator it = (prereqsGraph->required).begin(); it < (prereqsGraph->required).end(); it++){
    if (taken.count(*it) == 0) errorMessage += *it + " must be taken\n";
  }

  /* if everything meets requirements change errorMessage */

  if (errorMessage == "Bad plan. Here's why:\n") errorMessage = "Good plan. Get to work!";
  
  cout << errorMessage << endl;
}
