#ifndef PROJECT1_PREDICATE_H
#define PROJECT1_PREDICATE_H

#include <iostream>
#include "Stuff.h"

using namespace std;

class Predicate: public Stuff {
public:
    Predicate();
    ~Predicate();
    string toString();
};


#endif //PROJECT1_PREDICATE_H
