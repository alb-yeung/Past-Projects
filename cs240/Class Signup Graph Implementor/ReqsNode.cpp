#include "ReqsNode.h"

ReqsNode::ReqsNode(){
	courseName = "";
	reqs = vector<ReqsNode*>();
}

ReqsNode::ReqsNode(string cn){
	courseName = cn;
	reqs = vector<ReqsNode*>();
}

void ReqsNode::addReq(ReqsNode* req){
	reqs.push_back(req);
}