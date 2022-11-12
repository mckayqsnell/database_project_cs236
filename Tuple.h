#ifndef PROJECT1_TUPLE_H
#define PROJECT1_TUPLE_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include "Header.h"

using namespace std;

class Tuple { // These come from FACTS
public:
    Tuple();
    Tuple(vector<string> values) : values(values){}
    ~Tuple();
    bool operator<(const Tuple t) const {
        return values < t.values;
    }
    string toString(Header header);
    void addValue(string value);
    string getValue(unsigned int index);
    unsigned int getSize();

private:
    vector<string> values;

};


#endif //PROJECT1_TUPLE_H
