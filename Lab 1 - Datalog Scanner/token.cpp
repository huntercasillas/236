#include "token.h"
#include <sstream>

string token::print() {
	string output;
	output = "(" + tokenMap[type] + ",\"" + value + "\"," + lineToString() + ")";
	return output;
}

string token::lineToString() {
	stringstream convert;
	convert << line;
	string lineNumber = convert.str();
	return lineNumber;
}
