#ifndef RELATION
#define RELATION
#include "tuple.h"
#include <iostream>
#include <set>

using namespace std;

class relation {
public:
	relation(){}
	~relation(){}
	void setScheme(scheme s);
	void addTuple(Tuple t);
	string toString();
	relation select(int pos, string val);
	relation select(int pos1, int pos2);
	relation project(vector<int> pos);
	string printResult();
	set<Tuple> tupleList;
	scheme myScheme;
};

#endif
