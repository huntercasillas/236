#ifndef DATABASE
#define DATABASE
#include <map>
#include "relation.h"

using namespace std;

class database {
public:
	database(){}
	~database(){}
	map<string, relation> relations;
	string toString();
	int getSize();
private:
};

#endif
