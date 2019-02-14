#ifndef SCHEME
#define SCHEME
#include <string>
#include <vector>
#include "predicate.h"

using namespace std;

class scheme {
public:
	scheme(string n) {
		name = n;
	}
	scheme(){}
	~scheme(){}
	string name;
	vector<string> parameterList;
	void addName(string n) {
		name = n;
	}
	void addParameter(string param) {
		parameterList.push_back(param);
	}
	void addParameter(vector<string> params) {
		parameterList.insert(parameterList.end(),params.begin(), params.end());
	}
	void editParameter(int pos, string val) {
		parameterList[pos] = val;
	}
	predicate toPred() {
		predicate temp(name);
		for (unsigned int i = 0; i < parameterList.size(); i++) {
			parameter tempParam;
			tempParam.value = parameterList[i];
			tempParam.type = ID;
			temp.addParameter(tempParam);
		}
		return temp;
	}
	string toString() {
		string output;
		output = name + "(";
		for (unsigned int i = 0; i < parameterList.size()-1; i++) {
			output = output + parameterList[i] + ",";
		}
		output += parameterList[parameterList.size()-1] + ")";
		return output;
	}
};

#endif
