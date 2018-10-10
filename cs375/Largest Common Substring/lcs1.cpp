#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "timeProg.h"
//#include <unistd.h>

using namespace std;

/*
	lcshelper accepts the two input strings, the lengths of the input strings, and an output file to write to
	It uses dynamic programming, and has two tables, common and direction, to store the data necessary for dynamic programming
	Common holds the longest common substring up until the first ith letters of the first string and the first jth letters of the second string
	Direction holds the direction for where the common[i][j] got its value from
	Direction is used at the end to get the final common substring
*/
void lcshelper(string i1, string i2, int len1, int len2, string output){
	ofstream out(output); //out is the file we are writing to
	int** common; //This is the table for LCS until that point
	int** direction; //This is where the common[i][j] got their values
	common = new int*[len1+1];
	direction = new int*[len1+1];
	// 1 = up
	// 2 = left
	// 3 = diagonal
	for (int i = 0; i < len1+1; i++){ //i here is used to create the second dimension of the 2D arrays
		common[i] = new int[len2+1];
		direction[i] = new int[len2+1];
	}
	for (int i = 0; i < len1+1; i++){
		for (int j = 0; j < len2+1; j++){ //i and j here are used to initialize the arrays
			common[i][j] = 0;
			direction[i][j] = 0;
		}
	}

	for (int i = 1; i < len1+1; i++){
		for (int j = 1; j < len2+1; j++){ //i and j here are used as indexes to go through the array indexes one by one
			if (i1[i-1] == i2[j-1]){
				//cout << "match" << endl;
				common[i][j] = common[i-1][j-1]+1;
				direction[i][j] = 3;
			}else{
				if (common[i-1][j] > common[i][j-1]){
					common[i][j] = common[i-1][j];
					direction[i][j] = 1;
				}else{
					common[i][j] = common[i][j-1];
					direction[i][j] = 2;
				}
			}
		}
	}

	string max = ""; //max is used to store the max substring
	int i = len1; //used for table index
	int j = len2; //used for table index
	while (i > 0 && j > 0){ //i and j here are used to count backwards to get the actual substring
		if (direction[i][j] == 3){
			max += i1[i-1];
			i--;
			j--;
		}
		if (direction[i][j] == 1){
			i--;
		}
		if (direction[i][j] == 2){
			j--;
		}
	}
	reverse(max.begin(), max.end());
	//cout << max << endl;

	if (len1 <= 10 && len2 <= 10){
		for (int i = 0; i < len1+1; i++){
			for (int j = 0; j < len2+1; j++){ //i and j here are used to traverse the array to print out
				out << common[i][j];
			}
			out << endl;
		}
		out << max << endl;
		//sleep(1);
		getTimeTwo();
		out << to_string(getTotalTime()) << endl;
	}else{
		out << common[len1][len2] << endl;
		getTimeTwo();
		out << to_string(getTotalTime()) << endl;
	}
	out.close();
	return;
}

/*
	lcs is used to call lcshelper
*/
void lcs(string i1, string i2, string o){
	ifstream string1(i1); //string1 is used to read in the data from i1
	ifstream string2(i2); //string2 is used to read in the data from i2
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
	lcshelper(a, b, a.length(), b.length(), o);
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