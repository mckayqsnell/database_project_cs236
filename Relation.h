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
    //select(int column index, string value)
    Relation* select(unsigned int col, string value);
    //select 2
    Relation* select_two(unsigned int col1, unsigned int col2);
    //rename
    Relation* rename(unsigned int col_to_rename, string new_name);
    //rename 2
    Relation* rename(vector<string> newAttributes);
    //project
    Relation* project(vector<unsigned int> columns_to_keep);

    //Project 4
    // Natural Join
    Relation* naturalJoin(Relation* relation);
    // Unionize
    Relation* unionize(Relation* old_relation, Relation* new_relation);
    // Replace relation with new unionized relation
    void replaceRelation(Relation* relation);
    // find a tuple in a relation
    bool findTuple(Tuple tuple);

private:
    string name;
    set<Tuple> tuples;
    Header header;
};


#endif //PROJECT1_RELATION_H


/* steps for project 4
 * Get union working
 * Get Natural Join working
 * Figure out algorithm for evaluating the rules now that we have these functions
*/