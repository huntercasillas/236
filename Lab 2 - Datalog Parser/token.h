#ifndef TOKEN
#define TOKEN
#include <string>
#include <map>

using namespace std;

enum tokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD,
    SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, END
};

class token {
public:
	token(tokenType t, string v, int l):type(t),value(v),line(l) {
		tokenMap[COMMA] = "COMMA";
		tokenMap[PERIOD] = "PERIOD";
		tokenMap[Q_MARK] = "Q_MARK";
		tokenMap[LEFT_PAREN] = "LEFT_PAREN";
		tokenMap[RIGHT_PAREN] = "RIGHT_PAREN";
		tokenMap[COLON] = "COLON";
		tokenMap[COLON_DASH] = "COLON_DASH";
		tokenMap[MULTIPLY] = "MULTIPLY";
		tokenMap[ADD] = "ADD";
		tokenMap[SCHEMES] = "SCHEMES";
		tokenMap[FACTS] = "FACTS";
		tokenMap[RULES] = "RULES";
		tokenMap[QUERIES] = "QUERIES";
		tokenMap[ID] = "ID";
		tokenMap[STRING] = "STRING";
		tokenMap[COMMENT] = "COMMENT";
		tokenMap[WHITESPACE] = "WHITESPACE";
		tokenMap[UNDEFINED] = "UNDEFINED";
		tokenMap[END] = "EOF";
	}
	token(){}
	~token(){}
	tokenType type;
	string value;
	string print();
	string lineToString();
private:
	int line;
	map<tokenType, string> tokenMap;
};

#endif
