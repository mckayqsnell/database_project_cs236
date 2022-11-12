#ifndef PROJECT1_DATABASE_H
#define PROJECT1_DATABASE_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include "Relation.h"
#include "Header.h"
#include "Tuple.h"

using namespace std;

class Database {
public:
    Database();
    ~Database();
    // could add a constructor like in header.h that takes in a whole list of relations
    // since I have a relations list in parser.
    string toString();
    void addRelation(string name, Relation* relation);
    Relation* findRelation(string name);
    map<string, Relation*> getDatabase();
    void addTuple(string name, Tuple tuple);

private:
    map<string, Relation*> database;
};


#endif //PROJECT1_DATABASE_H
