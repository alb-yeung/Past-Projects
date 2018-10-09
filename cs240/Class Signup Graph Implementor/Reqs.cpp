#include "Reqs.h"

using namespace std;

Reqs::Reqs(){
	totalCredits = 0;
	totalC = 0;
	totalH = 0;
	totalF = 0;
	required = vector<string>();
}

void Reqs::load(string inputFile){
	ifstream f(inputFile);
	if (f.fail()){
		std::cout << "Reqs file not found" << endl;
		return;
	}
	
	string line;
	string reader;
	stringstream stream;

	for (getline(f, line, '\n'); line != ""; getline(f, line, '\n')){
		stream = stringstream(line);
		getline(stream, reader, ' ');
		if (reader == "TOTAL") loadCredits(line);
		if (reader == "CREDIT") loadCredits(line);
		if (reader == "COURSE") loadCourse(line);
		if (reader == "CHOOSE") loadCourse(line);
	}
}

void Reqs::loadCredits(string line){
	stringstream stream = stringstream(line);
	string reader;
	string::size_type sz;

	getline(stream, reader, ' ');
	if (reader == "TOTAL"){
		getline(stream, reader, '\n');
		totalCredits = stoi(reader, &sz);
	}
	if (reader == "CREDIT"){
		getline(stream, reader, ' ');
		if (reader == "C"){
			getline(stream, reader, '\n');
			totalC = stoi(reader, &sz);
		}
		if (reader == "H"){
			getline(stream, reader, '\n');
			totalH = stoi(reader, &sz);
		}
		if (reader == "F"){
			getline(stream, reader, '\n');
			totalF = stoi(reader, &sz);
		}
		
	}

	return;
}

void Reqs::loadCourse(string line){
	string cn;
	ReqsNode* course;
	stringstream stream = stringstream(line);
	string reader;

	getline(stream, reader, ' ');
	if (reader == "COURSE"){
		getline(stream, reader, ' ');
		cn = reader;

		if (locations.count(cn) == 0){
			addCourse(cn);
			course = locations[cn];
		}else{
			course = locations[cn];
		}
		getline(stream, reader, ' ');
		if (reader == "M" || reader == "R"){
			required.push_back(cn);
		}
		/*
		for (getline(stream, reader, ' '); reader.size() > 2; getline(stream, reader, ' ')){
			
			if (locations.count(reader) == 0){
				addCourse(reader);
			}
			course->addReq(locations[reader]);
			reader = "";
		}
		*/
	}

	return;
}

void Reqs::addCourse(string cn){
	locations[cn] = new ReqsNode(cn);
}