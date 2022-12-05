#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H

#include "Database.h"
#include "Queries.h"
#include "Rules.h"
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <deque>

using namespace std;

class Interpreter {
public:
    Interpreter(Database* database, vector<Queries*> queries, vector<Rules*> rules);
    ~Interpreter();
    void evaluateQueries();
    void evaluateRules();
    deque<Relation*> evaluatePredicates(Rules* rule);
    //string toString(); // not sure if I need this, just turned it off to pass off because it wasn't needed
private:
    Database* database;
    vector<Queries*> query_list;
    vector<Rules*> rule_list;
};


#endif //PROJECT1_INTERPRETER_H
