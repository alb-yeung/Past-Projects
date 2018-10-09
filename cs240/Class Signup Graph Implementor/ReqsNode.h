#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class ReqsNode{
public:
	string courseName;
	vector<ReqsNode*> reqs;

	ReqsNode();
	ReqsNode(string cn);

	void addReq(ReqsNode* req);
};