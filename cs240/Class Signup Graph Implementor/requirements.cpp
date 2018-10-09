
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "requirements.h"

using namespace std;

requirements::requirements(){
	totalcredits = 0;
	typeCcredits = 0;
	typeHcredits = 0;
	typeFcredits = 0;
	list = NULL;
}

void requirements::total(int t){
	totalcredits = t;
	//cout << totalcredits << endl;
}

void requirements::credit(char type, int num){
	if(type == 'C'){
		typeCcredits = num;
	}
	if(type == 'H'){
		typeHcredits = num;
	}
	if(type == 'F'){
		typeFcredits = num;
	}
	//cout << typeCcredits << " " << typeHcredits << " " << typeFcredits << endl;
}

void requirements::course(string name, char type, vector<string> prereqs){

/*
	cout << name << " " << type << " ";
	for(int i = 0; i < prereqs.size(); i++){
		cout << prereqs[i];
	}
	cout << "\n";
*/
}

void requirements::choose(int num, vector<string> choosefromlist){

/*
	cout << num << " ";
	for(int i = 0; i < choosefromlist.size(); i++){
		cout << choosefromlist[i] << " ";
	}
	cout << "\n";
*/
}
