/*
 Hunter Casillas
 NetID: casillas
 CS 236
 Project 4: Datalog Interpreter
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
	newInterpreter.start(argv[1]);

	return 0;
}
