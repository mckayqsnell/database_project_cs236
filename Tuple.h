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

    //Project 4
    vector<string> getValues() { return values; }
    bool operator==(const Tuple t) const {
        return values == t.values;
    }

    bool canJoin(Tuple otherTuple, Header header1, Header header2);
    Tuple combineTuples(Tuple otherTuple, Header header1, Header header2);

private:
    vector<string> values;

};


#endif //PROJECT1_TUPLE_H
