/*
 Hunter Casillas
 NetID: casillas
 CS 236
 Project 2: Datalog Parser
 */

#include <iostream>
#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        cout << "Error. Please be sure to include a single input file." << endl;
        return 0;
    } 
	parser newParser(argv[1]);
	newParser.parse();

	return 0;
}
