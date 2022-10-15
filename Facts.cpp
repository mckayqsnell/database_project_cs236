#include "Facts.h"
#include <iostream>
#include <sstream>

using namespace std;

Facts::Facts()
{
    num_Facts = 0;
}

Facts::~Facts()
{

}

void Facts::setNumFacts(int numFacts)
{
    this->num_Facts = numFacts;
}

int Facts::getNumFacts()
{
    return num_Facts;
}

string Facts::toString()
{
    stringstream ss;
    //ss << " this is fact number: " << getNumFacts() << " - " << getName() << endl;
    ss << getName() << "(";
    vector<string> string_List = getStringList();
    for(unsigned int i = 0; i < string_List.size(); i++)
    {
        ss << string_List.at(i);
        if(i < string_List.size()-1)
        {
            ss << ",";
        }
    }
    ss << ")." << endl;
    return ss.str();
}