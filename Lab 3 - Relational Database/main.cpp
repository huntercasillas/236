/*
 Hunter Casillas
 NetID: casillas
 CS 236
 Project 3: Relational Database
 */

#include "interpreter.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Error. Please be sure to include a single input file." << endl;
        return 0;
    }
    
	interpreter newInterpreter;
	newInterpreter.startToInterpret(argv[1]);

	return 0;
}
