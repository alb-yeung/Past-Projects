#include <time.h>
//#include <string>
//#include <iostream>

//using namespace std;

time_t start_t, end_t; //start_t and end_t are used for start and end times
double diff_t; //diff_t is used to calculate the difference between start and end

/*
	getTimeOne records the time it is called into start_t
*/
void getTimeOne(){
  time(&start_t);
}

/*
	getTimeTwo records the time it is called into end_t
*/
void getTimeTwo(){
  time(&end_t);
}

/*
	getTotalTime returns the difference between start_t and end_t
*/
double getTotalTime(){
  diff_t = difftime(end_t, start_t);
  //printf("Total execution time - %f\n", diff_t);
  return diff_t;
}
