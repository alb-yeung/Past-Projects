
#ifndef COURSES_H
#define COURSES_H

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

class courses {
	public:
		courses();

	private:
		string name;
		char courseType;
		courses* prereqs;
};

#endif
