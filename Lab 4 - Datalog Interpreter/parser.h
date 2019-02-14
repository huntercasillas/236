#ifndef PARSER
#define PARSER
#include "scanner.h"
#include "scheme.h"
#include "datalog.h"

class parser {
public:
	parser(){}
	~parser(){}
	void parse(string inputFile);
	token getToken();
	void match(tokenType t);
	void error();
	void parseScheme();
	void parseSchemeList();
	void parseFactList();
	void parseFact();
	void parseRuleList();
	void parseRule();
	predicate headPredicate();
	predicate parsePredicate();
	vector<predicate> parsePredicateList();
	parameter parseParameter();
	vector<parameter> parseParameterList();
	string parseExpression();
	string parseOperator();
	void parseQuery();
	void parseQueryList();
	vector<string> idList();
	vector<string> stringList();
	token newToken;
	vector<scheme> schemesList;
	vector<scheme> factsList;
	vector<string> domain;
	vector<rule> rulesList;
	vector<predicate> queryList;
private:
	vector<token> tokenList;
	datalog program;
	scanner lexer;
};

#endif
