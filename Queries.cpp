#include "Queries.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

Queries::Queries()
{
    num_Queries = 0;
}

Queries::~Queries()
{

}

string Queries::toString()
{
    stringstream ss;
    //ss << " this is Query number: " << num_Schemes << " - " << getName() << endl;
    ss << getName() << "(";
    vector<string> par = getParameterList();
    for(unsigned int i = 0; i < par.size(); i++)
    {
        ss << par.at(i);
        if(i < par.size()-1) {
            ss << ",";
        }
    }
    ss << ")?";
    return ss.str();
}

void Queries::setNumQueries(int numQueries)
{
    this->num_Queries = numQueries;
}

int Queries:: getNumQueries()
{
    return num_Queries;
}