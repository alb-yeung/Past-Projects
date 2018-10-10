#include "timeProg.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
/*
	lcshelper accepts a pointer to the 2D array, the two input strings, and the indexes to check in the two strings
	It uses a top down approach with memorization
	Common holds the longest common substring for up to the ith letter in i1 and the jth letter in i2 but it skips some subproblems if it doesn't need to solve it
*/
void lcshelper(int** common, string i1, string i2, int index1, int index2){
	/*
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){
			cout << common[i][j] <<"\t";
		}
		cout << endl;
	}
	cout << endl;
	*/
	if (index1 == -1 || index2 == -1){
		return;
	}
	if (i1[index1] == i2[index2]){
		if (common[index1][index2] == -1){
			lcshelper(common, i1, i2, index1-1, index2-1);
		}
		common[index1+1][index2+1] = common[index1][index2] + 1;
	}else{
		if (common[index1][index2+1] == -1){
			lcshelper(common, i1, i2, index1-1, index2);
		}
		if (common[index1+1][index1] == -1){
			lcshelper(common, i1, i2, index1, index2-1);
		}
		common[index1+1][index2+1] = max(common[index1][index2+1], common[index1+1][index2]);
	}
}

/*
	lcs is used to call lcshelper
	It accepts the file names for the two files and a file name for the output file
*/
void lcs(string i1, string i2, string o){
	ifstream string1(i1); //string1 is used to read in the data from i1
	ifstream string2(i2); //string2 is used to read in the data from i2
	ofstream out(o);
	if (string1.fail()){
		cout << "Input file 1 not found" << endl;
		return;
	}
	if (string2.fail()){
		cout << "Input file 2 not found" << endl;
		return;
	}
	string a; //a holds the data in i1
	string b; //b holds the data in i2
	getline(string1, a, ' ');
	getline(string2, b, ' ');

	int** common = new int*[a.length()+1]; //This is the table for LCS
	for (int i = 0; i < a.length()+1; i++){
		common[i] = new int[b.length()+1];
	}
	for (int i = 0; i < a.length()+1; i++){
		for (int j = 0; j < b.length()+1; j++){
			if (i == 0 || j == 0)
				common[i][j] = 0;
			else
				common[i][j] = -1;
		}
	}
	lcshelper(common, a, b, a.length()-1, b.length()-1);
	/*
	for (int i = 0; i < a.length()+1; i++){
		for (int j = 0; j < b.length()+1; j++){
			cout << common[i][j] <<"\t";
		}
		cout << endl;
	}
	*/
	out << common[a.length()][b.length()] << endl;
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