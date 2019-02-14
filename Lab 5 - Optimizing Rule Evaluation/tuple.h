#ifndef TUPLE
#define TUPLE
#include <string>
#include "scheme.h"

using namespace std;


class Tuple : public vector<string> {
public:
    Tuple(scheme s) {
        for (unsigned int i = 0; i < s.parameterList.size(); i++) {
            push_back(s.parameterList[i]);
        }
    }
    Tuple(){}
    ~Tuple(){}
    string toString() const {
        string output;
        for (vector<string>::const_iterator it = this->begin(); it != this->end(); ++it) {
            output +=  *it + "  ";
        }
        return output;
    }
    string printTuple() const {
        string output;
        for (vector<string>::const_iterator it = this->begin(); it != this->end(); ++it) {
            output += "=" + *it + "  ";
        }
        return output;
    }
};

#endif
