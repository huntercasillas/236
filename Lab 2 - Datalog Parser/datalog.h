#ifndef DATALOGPROGRAM
#define DATALOGPROGRAM
#include <vector>
#include "scheme.h"
#include "rule.h"

using namespace std;

class datalog {
public:
	datalog(){}
	~datalog(){}
	void addScheme(scheme s);
	void addFact(scheme f);
	void addRule(rule r);
	void addQuery(predicate p);
	void makeDomain();
	string toString();
private:
	vector<scheme> schemesList;
	vector<scheme> factsList;
	vector<string> domain;
	vector<rule> rulesList;
	vector<predicate> queryList;
	string numToString(unsigned long);
};

#endif
