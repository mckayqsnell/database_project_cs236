//
// Created by McKay Snell on 10/12/22.
//

#ifndef PROJECT1_FACTS_H
#define PROJECT1_FACTS_H

#include <iostream>
#include "Stuff.h"

using namespace std;

class Facts: public Stuff {
private:
    int num_Facts;
public:
    Facts();
    ~Facts();
    void setNumFacts(int numFacts);
    int getNumFacts();
    string toString();
};


#endif //PROJECT1_FACTS_H
