//
// Created by McKay Snell on 10/13/22.
//

#ifndef PROJECT1_QUERIES_H
#define PROJECT1_QUERIES_H
#include <iostream>
#include "Stuff.h"

using namespace std;

class Queries:public Stuff {
private:
    int num_Queries;
public:
    Queries();
    ~Queries();
    void setNumQueries(int numQueries);
    int getNumQueries();
    string toString();
};


#endif //PROJECT1_QUERIES_H
