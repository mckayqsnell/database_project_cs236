//
// Created by McKay Snell on 10/12/22.
//

#ifndef PROJECT1_STUFF_H
#define PROJECT1_STUFF_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stuff {
private:
    string name;
    vector<string> idList; //for schemes
    vector<string> stringList; // for facts
    vector<string> parameterList; // for queries
public:
    void setName(string name);
    string getName();
    void addID(string id);
    void addString(string string_to_add);
    void addParameter(string parameter);
    vector<string> getIDList(); // for domain
    vector<string> getStringList();
    vector<string> getParameterList();
};


#endif //PROJECT1_STUFF_H
