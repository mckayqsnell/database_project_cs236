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
#include "Graph.h"

using namespace std;

class Interpreter {
public:
    Interpreter(Database* database, vector<Queries*> queries, vector<Rules*> rules);
    ~Interpreter();
    void evaluateQueries();
    void evaluateRules(vector<Rules*> rules_to_evaluate, set<int> sccs);
    deque<Relation*> evaluatePredicates(Rules* rule);
    void rulesOptimization();
    bool detectSelfLoop(Rules* rule);
private:
    Database* database;
    vector<Queries*> query_list;
    vector<Rules*> rule_list;
    Graph* graph;
    Graph* reverseGraph;
};


#endif //PROJECT1_INTERPRETER_H
