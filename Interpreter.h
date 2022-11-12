#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H

#include "Database.h"
#include "Queries.h"
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Interpreter {
public:
    Interpreter(Database* database, vector<Queries*> queries);
    ~Interpreter();
    void evaluateQueries();
private:
    Database* database;
    vector<Queries*> query_list;
};


#endif //PROJECT1_INTERPRETER_H
