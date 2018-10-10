#include "timeProg.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
/*
	lcshelper accepts the two strings
	Tt recursively finds the LCS.
	It starts from the end
		-If the last two characters are the same, remove them both from the strings and add 1 to LCS of the two substrings without the final character
		-Otherwise return the max of two LCS's of each one minus their last letter.
*/
int lcshelper(string i1, string i2){
	if (i1.length() == 0){
		return 0;
	}
	if (i2.length() == 0){
		return 0;
	}
	if (i1[i1.length()-1] == i2[i2.length()-1])
		return lcshelper(i1.substr(0,i1.length()-1), i2.substr(0,i1.length()-1)) + 1;
	else
		return max(lcshelper(i1.substr(0,i1.length()-1), i2), lcshelper(i1, i2.substr(0, i2.length()-1)));
}

/*
	lcs is just used to call lcshelper
	It accepts two input strings and an output string
*/
void lcs(string i1, string i2, string o){
	ifstream string1(i1); //string1 is used for getting the data in i1
	ifstream string2(i2); //string2 is used for getting the data in i2
	ofstream out(o); //out is used to write into the out file
	if (string1.fail()){
		cout << "Input file 1 not found" << endl;
		return;
	}
	if (string2.fail()){
		cout << "Input file 2 not found" << endl;
		return;
	}
	string a; // a is the string in i1
	string b; // b is the string in i2
	getline(string1, a, ' ');
	getline(string2, b, ' ');
	out << lcshelper(a, b) << endl;
	getTimeTwo();
	out << to_string(getTotalTime()) << endl;
	out.close();
}

/*
	It's the main function
*/
int main(int argc, char* argv[]){
	if (argc != 4){
		cout << "Please use ./program1 <input-file1> <input-file2> <output-file>" << endl;
		return 1;
	}
	getTimeOne();
	lcs(argv[1], argv[2], argv[3]);
	return 0;
}