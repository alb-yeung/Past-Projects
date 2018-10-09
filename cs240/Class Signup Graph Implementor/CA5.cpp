
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <sstream>
#include "Student.h"

using namespace std;

int main(int argc, char* argv[]){

	if (argc != 4){
		cout << "Not enough files" << endl;
		return 0;
	}

	CourseMap map = CourseMap();
  	map.load(argv[2]);
 	Reqs* r = new Reqs();
  	r->load(argv[1]);
  	Student s = Student(r, map);
  	s.calculateSchedule(argv[3]);

  	cout << "Prerequisites don't quite work but everything else (I think) works" << endl;

  	return 0;

	//argv[1] is the requirement file
	//requirements requirements;
	//CourseMap map;
	//Student s = Student(requirements, map);
	
	/* It'll probably be cleaner if this read in function is in the requirements file so that the main function can just have simple function calls and variable declarations */
	
	//open file in read mode

	/*
	ifstream infile;
	infile.open(argv[1]);

	string tag;

	while(!infile.eof()){
		infile >> tag;
		if(tag == "TOTAL"){
			int t;
			infile >> t;
			requirements.total(t);
		}
		if(tag == "CREDIT"){
			char type;
			int num;
			infile >> type >> num;
			requirements.credit(type, num);
		}
		if(tag == "COURSE"){
			string name;
			char type;
			string line;
			vector<string> prereqs;

			infile >> name >> type;

			// separate out the strings within the line
			getline(infile, line);
			istringstream ss(line);
			for(string part; ss >> part;){
				prereqs.push_back(part);
			}

			requirements.course(name, type, prereqs);
		}
		if(tag == "CHOOSE"){
			int num;
			string line;
			vector<string> choosefromlist;

			infile >> num;
			
			getline(infile, line);
			istringstream ss(line);
			for(string part; ss >> part;){
				choosefromlist.push_back(part);
			}

			requirements.choose(num, choosefromlist);
		}
		
	}
	
	infile.close();
	*/
}

