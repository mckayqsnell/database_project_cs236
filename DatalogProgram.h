//
// Created by McKay Snell on 10/12/22.
//

#ifndef PROJECT1_DATALOGPROGRAM_H
#define PROJECT1_DATALOGPROGRAM_H

#include <vector>
#include <string>
#include "Schemes.h"

using namespace std;

class DatalogProgram {
private:
    string tmp;
    vector<Schemes*> schemesList; //TODO: needs to be vector of predicates for schemes
public:
    DatalogProgram();
    ~DatalogProgram();
    string ToString();
};


#endif //PROJECT1_DATALOGPROGRAM_H
