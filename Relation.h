#ifndef PROJECT1_RELATION_H
#define PROJECT1_RELATION_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <string>
#include "Header.h"
#include "Tuple.h"

using namespace std;

class Relation {
public:
    Relation();
    ~Relation();
    string toString();
    void addTuple(Tuple tuple);
    void setName(string name);
    Header getHeader();
    void setHeader(const Header &header);
    const set<Tuple> &getTuples() const;
    void setTuples(const set<Tuple> &tuples);
    const string &getName() const;
    unsigned int getSize();
    //TODO:select(int column index, string value)
    Relation* select(unsigned int col, string value);
    //TODO:select 2
    Relation* select_two(unsigned int col1, unsigned int col2);
    //TODO:rename
    Relation* rename(unsigned int col_to_rename, string new_name);
    //TODO:rename 2
    Relation* rename(vector<string> newAttributes);
    //TODO:project
    Relation* project(vector<unsigned int> columns_to_keep);
    Relation* project(vector<string> columns_to_keep);

private:
    string name;
    set<Tuple> tuples;
    Header header;
};


#endif //PROJECT1_RELATION_H
