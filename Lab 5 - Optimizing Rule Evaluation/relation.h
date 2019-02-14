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
    void addTuples(relation tups);
    string toString();
    string printTuple();
    string printString();
    relation select(int pos, string val);
    relation select(int pos1, int pos2);
    relation project(vector<int> pos);
    string printResult();
    unsigned long getSize();
    set<Tuple> tupleList;
    scheme myScheme;
};

#endif
