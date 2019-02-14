#ifndef RULE
#define RULE
#include "predicate.h"

using namespace std;

class rule {
public:
    rule(){}
    ~rule(){}
    predicate headPredicate;
    vector<predicate> predicateList;
    void addHead(predicate a) {
        headPredicate = a;
    }
    void addPredicate(predicate x) {
        predicateList.push_back(x);
    }
    void addPredicate(vector<predicate> v) {
        predicateList.insert(predicateList.end(), v.begin(), v.end());
    }
    string toString() {
        string output = headPredicate.toString() + " :- ";
        for (unsigned int i = 0; i < predicateList.size()-1; i++) {
            output += predicateList[i].toString() + ",";
        }
        output += predicateList[predicateList.size()-1].toString();
        return output;
    }
};

#endif
