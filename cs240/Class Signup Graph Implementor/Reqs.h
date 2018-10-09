#include "ReqsNode.h"
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

typedef unordered_map<string, ReqsNode*> locationMap;

class Reqs{
public:
	locationMap locations;
	int totalCredits;
	int totalC, totalH, totalF;
	vector<string> required;

	Reqs();

	void load(string inputFile);
	void loadCredits(string line);
	void loadCourse(string line);

	void addCourse(string cn);
};