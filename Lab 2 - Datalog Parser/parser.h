#ifndef PARSER
#define PARSER
#include "scanner.h"
#include "scheme.h"
#include "datalog.h"

class parser {
public:
	parser(string inputFile) {
		lexer.scan(inputFile);
		tokenList = lexer.getVector();
		newToken = tokenList[0];
		tokenList.erase(tokenList.begin());
	}
	~parser(){}
	void parse();
	token getToken();
	void match(tokenType t);
	void error();
	void toString();
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
private:
	vector<token> tokenList;
	datalog program;
	scanner lexer;
};

#endif
