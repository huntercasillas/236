/*
 Hunter Casillas
 NetID: casillas
 CS 236
 Project 1: Datalog Scanner
 */

#include <iostream>
#include "scanner.h"

using namespace std;

int main(int argc, char* argv[]) {
    
	if (argc != 2) {
		cout << "Error. Please be sure to include a single input file." << endl;
		return 0;
	}
    
	scanner newScanner;
	newScanner.scan(argv[1]);

	return 0;
}
