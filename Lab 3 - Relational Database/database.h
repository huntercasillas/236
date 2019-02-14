#ifndef DATABASE
#define DATABASE
#include <map>
#include "relation.h"

using namespace std;

class database {
public:
	database(){}
	~database(){}
	map<string, relation> relations;
	string toString() {
		string output;
		for (std::map<string,relation>::iterator it = relations.begin(); it != relations.end(); ++it) {
			output += it->second.toString() + "\n";
		}
		return output;
	}
private:
};

#endif
