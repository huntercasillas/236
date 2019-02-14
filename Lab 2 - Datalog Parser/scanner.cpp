#include "scanner.h"
#include <fstream>
#include <cctype>
#include <iostream>

void scanner::scan(string fileName) {
	inputFile.open(fileName.c_str());

	if (inputFile) {
		while (inputFile.get(current)) {
			scanToken();
		}
		makeToken(END, line);

		outputFile.open("output.txt");
		for (unsigned int i = 0; i < myVector.size(); i++) {
			outputFile << myVector[i].print() << endl;
		}
		outputFile << "Total Tokens = " << myVector.size();
		outputFile.close();
	}
    else {
		cout << "Error. File not found. Please be sure to use a valid input file." << endl;
        exit(0);
    }
}

void scanner::scanToken() {
	while (isspace(current)) {
        if (current == '\n') {
			line++;
        }
		inputFile.get(current);
        if (inputFile.eof()) {
			break;
        }
	}
	switch (current) {
	case ',':
		value = ",";
		makeToken(COMMA, line);
		break;
	case '.':
		value = ".";
		makeToken(PERIOD, line);
		break;
	case '?':
		value = "?";
		makeToken(Q_MARK, line);
		break;
	case '(':
		value = "(";
		makeToken(LEFT_PAREN, line);
		break;
	case ')':
		value = ")";
		makeToken(RIGHT_PAREN, line);
		break;
	case '*':
		value = "*";
		makeToken(MULTIPLY, line);
		break;
	case '+':
		value = "+";
		makeToken(ADD, line);
		break;
	case ':':
		value = ":";
		next = inputFile.peek();
		if (next == '-') {
			value = ":-";
			makeToken(COLON_DASH, line);
			inputFile.get(current);
		}
        else {
			makeToken(COLON, line);
        }
		break;
	case '\'':
		scanString();
		break;
	case '#':
		scanComment();
		break;
	default:
        if (isalpha(current)) {
			scanID();
        }
		else if (!inputFile.eof()) {
			value += current;
			makeToken(UNDEFINED, line);
		}
		break;
	}
}

void scanner::scanID() {
	value += current;
	inputFile.get(current);
	while (isalnum(current)) {
		value += current;
		inputFile.get(current);
	}
	valueToUpper();
    if (valueUpper == "SCHEMES") {
		makeToken(SCHEMES, line);
    }
    else if (valueUpper == "FACTS") {
		makeToken(FACTS, line);
    }
    else if (valueUpper == "RULES") {
		makeToken(RULES, line);
    }
    else if (valueUpper == "QUERIES") {
		makeToken(QUERIES, line);
    }
    else {
		makeToken(ID, line);
    }
	scanToken();
}

void scanner::scanString() {
	bool endOfString = false;
	value += current;
	lineStart = line;
	while (endOfString == false) {
		if (inputFile.peek() == EOF) {
			makeToken(UNDEFINED, lineStart);
			endOfString = true;
		}
		else {
			inputFile.get(current);
			switch(current) {
			case '\n':
				line++;
				value += current;
				break;
			case '\'':
				value += current;
				next = inputFile.peek();
				if (next != '\'') {
					makeToken(STRING, lineStart);
					endOfString = true;
				}
				else {
					inputFile.get(current);
					value += current;
				}
				break;
			default:
				value += current;
				break;
			}
		}
	}
}

void scanner::scanComment() {
	value += current;
	lineStart = line;
	next = inputFile.peek();
	if (next != '|') {
		inputFile.get(current);
		while (current != '\n') {
			value += current;
			inputFile.get(current);
		}
        if (current == '\n') {
			line++;
        }
		makeToken(COMMENT, lineStart);
	}
    else {
        scanComment2();
    }
}

void scanner::scanComment2() {
    inputFile.get(current);
    value += current;
    inputFile.get(current);
    next = inputFile.peek();
    while ((current != '|' || next != '#') && current != EOF) {
        if (current == '\n') {
            line++;
        }
        value += current;
        if (inputFile.eof()) {
            break;
        }
        inputFile.get(current);
        next = inputFile.peek();
    }
    scanComment3();
}

void scanner::scanComment3() {
    if (current == '|' && next == '#') {
        value += current;
        inputFile.get(current);
        value += current;
        makeToken(COMMENT, lineStart);
    }
    else {
        makeToken(UNDEFINED, lineStart);
    }
}

void scanner::makeToken(tokenType type, int lineNum) {
	token newToken(type, value, lineNum);
	if (type != COMMENT) {
		myVector.push_back(newToken);
	}
	value = "";
	valueUpper = "";
}

void scanner::valueToUpper() {
	for (unsigned int i = 0; i < value.length(); i++) {
		valueUpper += toupper(value[i]);
	}
}

vector<token> scanner::getVector() {
	return myVector;
}

