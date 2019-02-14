#include "datalog.h"
#include <sstream>
#include <algorithm>

void datalog::addScheme(scheme s) {
    schemesList.push_back(s);
}

void datalog::addFact(scheme f) {
    factsList.push_back(f);
    domain.insert(domain.end(), f.parameterList.begin(), f.parameterList.end());
}

void datalog::addRule(rule r) {
    rulesList.push_back(r);
}

void datalog::addQuery(predicate p) {
    queryList.push_back(p);
}

void datalog::makeDomain() {
    sort(domain.begin(), domain.end());
    domain.erase(unique(domain.begin(), domain.end()), domain.end());
}

string datalog::toString() {
    string output;
    output = "Schemes(" + numToString(schemesList.size()) + "):\n";
    for (unsigned int i = 0; i < schemesList.size(); i++) {
        output += "  " + schemesList[i].toString() + "\n";
    }
    output += "Facts(" + numToString(factsList.size()) +  "):\n";
    for (unsigned int i = 0; i < factsList.size(); i++) {
        output += "  " + factsList[i].toString() + ".\n";
    }
    output += "Rules(" + numToString(rulesList.size()) + "):\n";
    for (unsigned int i = 0; i < rulesList.size(); i++) {
        output += "  " + rulesList[i].toString() + ".\n";
    }
    output += "Queries(" + numToString(queryList.size()) + "):\n";
    for (unsigned int i = 0; i < queryList.size(); i++) {
        output += "  " + queryList[i].toString() + "?\n";
    }
    output += "Domain(" + numToString(domain.size()) + "):\n";
    for (unsigned int i = 0; i < domain.size(); i++) {
        output += "  " + domain[i] + "\n";
    }
    return output;
}

string datalog::numToString(unsigned long x)
{
    stringstream convert;
    convert << x;
    string output = convert.str();
    return output;
}
