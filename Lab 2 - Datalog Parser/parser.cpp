#include "parser.h"
#include "rule.h"
#include "parameter.h"
#include <algorithm>
#include <iostream>

void parser::parse() {
	match(SCHEMES);
	match(COLON);
	parseScheme();
	parseSchemeList();

	match(FACTS);
	match(COLON);
	parseFactList();
	program.makeDomain();

	match(RULES);
	match(COLON);
	parseRuleList();

	match(QUERIES);
	match(COLON);
	parseQuery();
	parseQueryList();

	cout << "Success!\n" << program.toString();
}

void parser::match(tokenType t) {
	if (newToken.type == t) {
		newToken = tokenList[0];
		tokenList.erase(tokenList.begin());
	}
    else {
		error();
    }
}

void parser::error() {
	cout << "Failure!\n  " << newToken.print() << endl;
	exit(0);
}

void parser::parseScheme() {
	scheme newScheme(newToken.value);
	match(ID);
	match(LEFT_PAREN);
	newScheme.addParameter(newToken.value);
	match(ID);
	newScheme.addParameter(idList());
	match(RIGHT_PAREN);
	program.addScheme(newScheme);
}

void parser::parseSchemeList() {
	if (newToken.type != FACTS) {
		parseScheme();
		parseSchemeList();
	}
}

void parser::parseFact() {
	scheme newFact(newToken.value);
	match(ID);
	match(LEFT_PAREN);
	newFact.addParameter(newToken.value);
	match(STRING);
	newFact.addParameter(stringList());
	match(RIGHT_PAREN);
	match(PERIOD);
	program.addFact(newFact);
}

void parser::parseFactList() {
	if (newToken.type != RULES) {
		parseFact();
		parseFactList();
	}
}

void parser::parseRuleList() {
	if (newToken.type != QUERIES) {
		parseRule();
		parseRuleList();
	}
}

void parser::parseRule() {
	rule newRule;
	newRule.addHead(headPredicate());
	match(COLON_DASH);
	newRule.addPredicate(parsePredicate());
	newRule.addPredicate(parsePredicateList());
	match(PERIOD);
	program.addRule(newRule);
}

predicate parser::headPredicate() {
	predicate newHead(newToken.value);
	parameter initial;
	vector<parameter> pList;
	vector<string> temp;
	match(ID);
	match(LEFT_PAREN);
	initial.value = newToken.value;
	newHead.addParameter(initial);
	match(ID);
	temp = idList();
	for (unsigned int i = 0; i < temp.size(); i++) {
		parameter a;
		a.value = temp[i];
		pList.push_back(a);
	}
	newHead.addParameter(pList);
	match(RIGHT_PAREN);
	return newHead;
}

predicate parser::parsePredicate() {
	predicate newPred(newToken.value);
	match(ID);
	match(LEFT_PAREN);
	newPred.addParameter(parseParameter());
	newPred.addParameter(parseParameterList());
	match(RIGHT_PAREN);
	return newPred;
}

vector<predicate> parser::parsePredicateList() {
	vector<predicate> newpredicateList;
	if (newToken.type != PERIOD && newToken.type != QUERIES) {
		match(COMMA);
		newpredicateList.push_back(parsePredicate());
		vector<predicate> temp = parsePredicateList();
		newpredicateList.insert(newpredicateList.end(), temp.begin(), temp.end());
	}
	return newpredicateList;
}

parameter parser::parseParameter() {
	parameter newParam;
	if (newToken.type == STRING) {
		newParam.value = newToken.value;
		match(STRING);
	}
	else if (newToken.type == ID) {
		newParam.value = newToken.value;
		match(ID);
	}
	else {
		newParam.value = parseExpression();
	}
	return newParam;
}

vector<parameter> parser::parseParameterList() {
	vector<parameter> newParamList;
	if (newToken.type != RIGHT_PAREN) {
		match(COMMA);
		newParamList.push_back(parseParameter());
		vector<parameter> temp = parseParameterList();
		newParamList.insert(newParamList.end(), temp.begin(), temp.end());
	}
	return newParamList;
}

string parser::parseExpression() {
	string exp = "(";
	match(LEFT_PAREN);
	exp += parseParameter().value + " ";
	exp += parseOperator() + " ";
	exp += parseParameter().value;
	match(RIGHT_PAREN);
	exp += ")";
	return exp;
}

string parser::parseOperator() {
	if (newToken.type == ADD) {
		match(ADD);
		return "+";
	}
	else if (newToken.type == MULTIPLY) {
		match(MULTIPLY);
		return "*";
	}
    else {
		error();
    }
    return "";
}

void parser::parseQuery() {
	program.addQuery(parsePredicate());
	match(Q_MARK);
}

void parser::parseQueryList() {
	if (newToken.type != END) {
		parseQuery();
		parseQueryList();
	}
}

vector<string> parser::idList() {
	vector<string> myList;
	if (newToken.type != RIGHT_PAREN) {
		match(COMMA);
		myList.push_back(newToken.value);
		match(ID);
		vector<string> temp = idList();
		myList.insert(myList.end(), temp.begin(), temp.end());
	}
	return myList;
}

vector<string> parser::stringList() {
	vector<string> myList;
	if (newToken.type != RIGHT_PAREN) {
		match(COMMA);
		myList.push_back(newToken.value);
		match(STRING);
		vector<string> temp = stringList();
		myList.insert(myList.end(), temp.begin(), temp.end());
	}
	return myList;
}
