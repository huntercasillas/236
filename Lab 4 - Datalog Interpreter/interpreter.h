#ifndef INTERPRETER
#define INTERPRETER
#include "parser.h"
#include "database.h"

using namespace std;

class interpreter {
public:
	interpreter(){}
	~interpreter(){}
	void start(string inputFile);
	vector<scheme> schemesList;
	vector<scheme> factsList;
	vector<string> domain;
	vector<rule> rulesList;
	vector<predicate> queryList;
private:
	parser myParser;
	database db;
	void processRules();
	void processQueries();
	void printParameters(relation afterProjects);
	relation selects(predicate query);
	relation projectQuery(predicate query, relation rel);
	relation projectJoin(predicate query, relation rel);
	void rename(string name, vector<string> param, relation &renameRel);
	relation join(relation a, relation b);
	bool joinable(Tuple a, Tuple b, vector<string> aParam, vector<string> bParam);
};

#endif
