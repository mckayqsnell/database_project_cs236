#include "Predicate.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Predicate::Predicate()
{

}

Predicate::~Predicate()
{

}

string Predicate::toString()
{
    stringstream ss;
    //ss << " this is Parameter number: " << num_Schemes << " - " << getName() << endl;
    ss << getName() << "(";
    vector<string> par = getParameterList();
    for(unsigned int i = 0; i < par.size(); i++)
    {
        ss << par.at(i);
        if(i < par.size()-1) {
            ss << ",";
        }
    }
    ss << ")";
    return ss.str();
}