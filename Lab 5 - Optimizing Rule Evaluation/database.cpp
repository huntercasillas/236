#include "database.h"

string database::toString() {
    string output;
    output = "";
    for (map<string,relation>::iterator it = relations.begin(); it != relations.end(); ++it) {
        output += it->second.toString() + "\n";
    }
    return output;
}

int database::getSize() {
    int size = 0;
    for (map<string, relation>::iterator it = relations.begin(); it != relations.end(); ++it) {
        size += it->second.getSize();
    }
    return size;
}
