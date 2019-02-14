#include "interpreter.h"
#include <iostream>
#include <algorithm>
#include "token.h"

void interpreter::start(string inputFile) {
    
	myParser.parse(inputFile);
	schemesList = myParser.schemesList;
	factsList = myParser.factsList;
	domain = myParser.domain;
	rulesList = myParser.rulesList;
	queryList = myParser.queryList;

    //Create Relations
    for (unsigned int i = 0; i < schemesList.size(); i++) {
        relation newRelation;
        newRelation.setScheme(schemesList[i]);
        db.relations.insert(pair<string, relation>(schemesList[i].name,newRelation));
    }
    //Add Tuples to Relations
    for (unsigned int i = 0; i < factsList.size(); i++) {
        Tuple newTuple(factsList[i]);
        db.relations[factsList[i].name].addTuple(newTuple);
    }
	evalRule();
    processQueries();
}

void interpreter::processQueries() {
    cout << "Query Evaluation" << endl;
    for (unsigned int i = 0; i < queryList.size(); i++) {
        relation afterSelects;
        relation afterProjects;
        afterSelects = selects(queryList[i]);
        afterProjects = projectQuery(queryList[i], afterSelects);
        
        //Print Results
        cout << queryList[i].toString() << "? ";
        if ((afterSelects.tupleList).empty()) {
            cout << "No\n";
        }
        else if ((afterProjects.tupleList).empty()) {
            cout << "Yes(1)\n";
        }
        else {
            cout << "Yes(" << afterProjects.tupleList.size() << ")\n";
            printParameters(afterProjects);
        }
    }
}

void interpreter::printParameters(relation afterProjects) {
    for (set<Tuple>::iterator it = afterProjects.tupleList.begin(); it != afterProjects.tupleList.end(); ++it) {
        cout << "  ";
        int count = 0;
        for (unsigned int x = 0; x < afterProjects.myScheme.parameterList.size(); x++) {
            if (count != 0) {
                cout << ", ";
            }
            std::basic_string<char> valX = afterProjects.myScheme.parameterList[x];
            cout  << valX << "=" << (*it)[count];
            count++;
        }
        cout << endl;
    }
}

void interpreter::processRule(rule r) {
	predicate headPred = r.headPredicate;
	vector<predicate> predList = r.predList;
	relation afterPreds;
    vector<string> renameVals;

	afterPreds = selects(predList[0]);
	afterPreds = projectQuery(predList[0], afterPreds);

	for (unsigned int i = 1; i < predList.size(); i++) {
		afterPreds = join(afterPreds, projectQuery(predList[i], selects(predList[i])));
	}

	afterPreds = projectJoin(headPred, afterPreds);
    
    cout << r.toString() << "." << endl;
    renameVals = db.relations[headPred.name].myScheme.parameterList;
    rename(headPred.name, renameVals, afterPreds);
    
    for (set<Tuple>::iterator it = afterPreds.tupleList.begin(); it != afterPreds.tupleList.end(); ++it) {
        if (db.relations[headPred.name].tupleList.count(*it) == 0) {
            cout << "  ";
            int count = 0;
            for (unsigned int x = 0; x < afterPreds.myScheme.parameterList.size(); x++) {
                if (count != 0) {
                    cout << ", ";
                }
                std::basic_string<char> valX = afterPreds.myScheme.parameterList[x];
                cout  << valX << "=" << (*it)[count];
                count++;
            }
            cout << endl;
            db.relations[headPred.name].addTuple(*it);
        }
    }
}

relation interpreter::selects(predicate query) {
    relation newRelation = db.relations[query.name];
    for (unsigned int j = 0; j < query.parameterList.size(); j++) {
        parameter temp = query.parameterList[j];
        if (temp.type == STRING) {
            newRelation = newRelation.select(j, temp.value);
        }
    }
    for (unsigned int j = 0; j < query.parameterList.size(); j++) {
        for (unsigned int k = j+1; k < query.parameterList.size(); k++) {
            if (query.parameterList[j].value == query.parameterList[k].value) {
                newRelation = newRelation.select(j,k);
                break;
            }
        }
    }
    return newRelation;
}

relation interpreter::projectQuery(predicate query, relation rel) {
    vector<int> projectsPos;
    vector<string> renameVals;
    relation newRelation;
    for (unsigned int k = 0; k < query.parameterList.size(); k++) {
        parameter temp = query.parameterList[k];
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
    newRelation = rel.project(projectsPos);
    rename(query.name, renameVals, newRelation);
    return newRelation;
}

relation interpreter::projectJoin(predicate query, relation rel) {
    vector<int> projectsPos;
    vector<string> renameVals;
    relation newRelation;
    for (unsigned int k = 0; k < query.parameterList.size(); k++) {
        parameter temp = query.parameterList[k];
        if (temp.type == ID) {
            bool exists = false;
            for (unsigned int x = 0; x < projectsPos.size(); x++) {
                if (temp.value == renameVals[x]) {
                    exists = true;
                }
            }
            if (!exists) {
                for (unsigned int l = 0; l < rel.myScheme.parameterList.size(); l++) {
                    if (temp.value == rel.myScheme.parameterList[l]) {
                        projectsPos.push_back(l);
                        renameVals.push_back(temp.value);
                        break;
                    }
                }
                
            }
            
        }
    }
    newRelation = rel.project(projectsPos);
    rename(query.name, renameVals, newRelation);
    return newRelation;
}

void interpreter::rename(string name, vector<string> param, relation &renameRel) {
	scheme tempScheme(name);
	tempScheme.addParameter(param);
	renameRel.setScheme(tempScheme);
}

relation interpreter::join(relation a, relation b) {
	relation product;
	predicate joinProj;
	scheme productScheme = a.myScheme;
	productScheme.addParameter(b.myScheme.parameterList);
	product.setScheme(productScheme);

	for(set<Tuple>::iterator it = a.tupleList.begin(); it != a.tupleList.end(); ++it) {
		for(set<Tuple>::iterator jt = b.tupleList.begin(); jt != b.tupleList.end(); ++jt) {
			if (joinable((*it),(*jt),a.myScheme.parameterList, b.myScheme.parameterList)) {
				Tuple newTuple = (*it);
				newTuple.insert(newTuple.end(), (*jt).begin(), (*jt).end());
				product.addTuple(newTuple);
			}
		}
	}
	vector<string>::iterator it = unique(productScheme.parameterList.begin(), productScheme.parameterList.end());
	productScheme.parameterList.resize(distance(productScheme.parameterList.begin(),it));
	joinProj = productScheme.toPred();
	product = projectJoin(joinProj, product);
	return product;
}

bool interpreter::joinable(Tuple a, Tuple b, vector<string> aParam, vector<string> bParam) {
	for (unsigned int i = 0; i < a.size(); i++) {
		for (unsigned int j=0; j < b.size(); j++) {
            if (aParam[i] == bParam[j] && a[i] != b[j]) {
				return false;
            }
		}
	}
	return true;
}

void interpreter::evalRule() {
	myGraph = makeGraph();
	revGraph = makeRevGraph();
	cout << "Dependency Graph" << endl;
	cout << myGraph.toString() << endl;
	vector<node> postOrder = revGraph.getPostOrder();

	while (!postOrder.empty()) {
		unsigned long i = postOrder.size() - 1;
		if (!myGraph.nodes[postOrder[i].name].visited) {
			vector<node> temp = myGraph.dfs(myGraph.nodes[postOrder[i].name]);
			sort(temp.begin(), temp.end());
			temp.erase(unique(temp.begin(),temp.end()), temp.end());
			sccs.push_back(temp);
		}
		postOrder.pop_back();
	}
    evalRule2();
}

void interpreter::evalRule2() {
    
    cout << "Rule Evaluation" << endl;
    
    for (unsigned int i = 0;  i < sccs.size(); i++) {
        int numPasses = 0;
        if (sccs[i].size() == 1 && !sccs[i][0].isCyclic()) {
            cout << "SCC: R" << sccs[i][0].name << endl;
            processRule(rulesList[sccs[i][0].name]);
            cout << "1 passes: R" << sccs[i][0].name << endl;
        }
        else {
            int sizeBefore = 0;
            int sizeAfter = 0;
            cout << "SCC: R" << sccs[i][0].name;
            for (unsigned int j = 1; j < sccs[i].size(); j++) {
                cout << ",R" << sccs[i][j].name;
            }
            cout << endl;
            do {
                sizeBefore = db.getSize();
                for (unsigned int k = 0; k < sccs[i].size(); k++) {
                    processRule(rulesList[sccs[i][k].name]);
                }
                sizeAfter = db.getSize();
                numPasses++;
            } while (sizeBefore != sizeAfter);
            
            cout << numPasses << " passes: R" << sccs[i][0].name;
            for (unsigned int l = 1; l < sccs[i].size(); l++) {
                cout << ",R" << sccs[i][l].name;
            }
            cout << endl;
        }
    }
    cout << endl;
}

graph interpreter::makeGraph() {
	graph thisGraph;
	for (unsigned int i =0; i < rulesList.size(); i++) {
		rule thisRule = rulesList[i];
		node thisNode;
		thisNode.name = i;
		for (unsigned int j = 0; j < thisRule.predList.size(); j++) {
			predicate thisPred = thisRule.predList[j];
			for (unsigned int k = 0; k < rulesList.size(); k++) {
				if (thisPred.name == rulesList[k].headPredicate.name) {
					thisNode.adjacentNodes.push_back(k);
				}
			}
		}
		sort(thisNode.adjacentNodes.begin(), thisNode.adjacentNodes.end());
		thisNode.adjacentNodes.erase(unique(thisNode.adjacentNodes.begin(), thisNode.adjacentNodes.end()), thisNode.adjacentNodes.end());
		thisGraph.nodes.insert(pair<int, node>(i, thisNode));
	}
	return thisGraph;
}

graph interpreter::makeRevGraph() {
	graph thisGraph;

	for (unsigned int i = 0; i < rulesList.size(); i++) {
		rule thisRule = rulesList[i];
		node thisNode;
		thisNode.name = i;
		for (unsigned int j = 0; j < rulesList.size(); j++) {
			for (unsigned int k = 0; k < rulesList[j].predList.size(); k++) {
				if (rulesList[j].predList[k].name == thisRule.headPredicate.name) {
					thisNode.adjacentNodes.push_back(j);
				}
			}
		}
		sort(thisNode.adjacentNodes.begin(), thisNode.adjacentNodes.end());
		thisNode.adjacentNodes.erase(unique(thisNode.adjacentNodes.begin(), thisNode.adjacentNodes.end()), thisNode.adjacentNodes.end());
		thisGraph.nodes.insert(pair<int,node>(i,thisNode));
	}
	return thisGraph;
}
