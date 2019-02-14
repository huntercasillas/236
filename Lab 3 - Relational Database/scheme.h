#ifndef SCHEME
#define SCHEME
#include <string>
#include <vector>

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
