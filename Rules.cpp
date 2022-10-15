#include "Rules.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

Rules::Rules()
{
    num_Rules = 0;
}

Rules::~Rules()
{

}

string Rules::toString()
{
    stringstream ss;
    ss << getHeadPredicate()->toString() << " :- ";
    for(unsigned int i = 0; i < predicates.size(); ++i)
    {
        ss << predicates.at(i)->toString();
        if(i < predicates.size()-1)
        {
            ss << ", ";
        }
    }
    ss << ".";
    return ss.str();
}

void Rules::setNumRules(int numRules)
{
    this->num_Rules = numRules;
}

int Rules::getNumRules()
{
    return num_Rules;
}

void Rules::addPredicate(Predicate *predicate)
{
    predicates.push_back(predicate);
}

Predicate* Rules::getHeadPredicate()
{
    return head_predicate;
}

void Rules::setHeadPredicate(Predicate *predicate)
{
    head_predicate = predicate;
}


vector<Predicate*> Rules::getPredicateList()
{
    return predicates;
}