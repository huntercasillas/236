#ifndef GRAPH
#define GRAPH
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include "node.h"

using namespace std;

class graph {
public:
	graph(){}
	~graph(){}
	map<int,node> nodes;
	string toString();
	string intToString(int n);
	vector<node> getPostOrder();
	vector<node> dfs(node& x);
};

#endif
