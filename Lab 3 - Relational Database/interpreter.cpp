#include <iostream>
#include "token.h"
#include "interpreter.h"

void interpreter::startToInterpret(string inputFile) {
	newParser.parse(inputFile);
	schemesList = newParser.schemesList;
	factsList = newParser.factsList;
	domain = newParser.domain;
	rulesList = newParser.rulesList;
	queryList = newParser.queryList;
	
	for (unsigned int i = 0; i < schemesList.size(); i++) {
		relation newRelation;
		newRelation.setScheme(schemesList[i]);
		db.relations.insert(pair<string, relation>(schemesList[i].name,newRelation));
	}
	for (unsigned int i = 0; i < factsList.size(); i++) {
		Tuple newTuple(factsList[i]);
		db.relations[factsList[i].name].addTuple(newTuple);
	}
    startToInterpret2();
}

void interpreter::startToInterpret2() {
    for (unsigned int i = 0; i < queryList.size(); i++) {
        relation selects = db.relations[queryList[i].name];
        relation projects;
        vector<int> projectsPos;
        vector<string> renameVals;
        for (unsigned int j = 0; j < queryList[i].parameterList.size(); j++) {
            parameter temp = queryList[i].parameterList[j];
            if (temp.type == STRING) {
                selects = selects.select(j+1, temp.value);
            }
        }
        for (unsigned int j = 0; j < queryList[i].parameterList.size(); j++) {
            for (unsigned int k = j+1; k < queryList[i].parameterList.size(); k++) {
                if (queryList[i].parameterList[j].value == queryList[i].parameterList[k].value) {
                    selects = selects.select(j,k);
                    break;
                }
            }
        }
        startToInterpret3(i, selects, projects, projectsPos, renameVals);
    }
}

void interpreter::startToInterpret3(int i, relation selects, relation projects, vector<int> projectsPos, vector<string> renameVals) {
    for (unsigned int k = 0; k < queryList[i].parameterList.size(); k++) {
        parameter temp = queryList[i].parameterList[k];
        if (temp.type == ID) {
            bool exists = false;
            for (unsigned int x = 0; x < projectsPos.size(); x++) {
                if (temp.value == renameVals[x]) {
                    exists = true;
                }
            }
            if (!exists) {
                projectsPos.push_back(k);
                renameVals.push_back(temp.value);
            }
        }
    }
    projects = selects.project(projectsPos);
    scheme tempScheme(queryList[i].name);
    tempScheme.addParameter(renameVals);
    projects.setScheme(tempScheme);
    cout << queryList[i].toString() << "? ";
    startToInterpret4(selects, projects);
}

void interpreter::startToInterpret4(relation selects, relation projects) {
    if ((selects.tupleList).empty()) {
        cout << "No\n";
    }
    else if((projects.tupleList).empty()) {
        cout << "Yes(1)\n";
    }
    else {
        cout << "Yes(" << projects.tupleList.size() << ")\n";
        for (set<Tuple>::iterator it = projects.tupleList.begin(); it != projects.tupleList.end(); ++it) {
            cout << "  ";
            int count = 0;
            for (unsigned int x = 0; x < projects.myScheme.parameterList.size(); x++) {
                if (count != 0) {
                    cout << ", ";
                }
                cout  << projects.myScheme.parameterList[x] << "="
                << (*it)[count];
                count++;
            }
            cout << endl;
        }
    }
}
