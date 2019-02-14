#ifndef INTERPRETER
#define INTERPRETER
#include "parser.h"
#include "database.h"

using namespace std;

class interpreter {
public:
	interpreter(){}
	~interpreter(){}
	void startToInterpret(string inputFile);
    void startToInterpret2();
    void startToInterpret3(int i, relation selects, relation projects, vector<int> projectsPos, vector<string> renameVals);
    void startToInterpret4(relation selects, relation projects);
	vector<scheme> schemesList;
	vector<scheme> factsList;
	vector<string> domain;
	vector<rule> rulesList;
	vector<predicate> queryList;
private:
	parser newParser;
	database db;
};

#endif
