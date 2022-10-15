//
// Created by McKay Snell on 10/12/22.
//

#include "Stuff.h"

void Stuff::setName(string name)
{
    this->name = name;
}

string Stuff::getName()
{
    return name;
}

void Stuff::addID(string id)
{
    //cerr << "Adding " << id << " to idList" << endl;
    idList.push_back(id);
}

void Stuff::addString(string string_to_add)
{
    stringList.push_back(string_to_add);
}

void Stuff::addParameter(string parameter)
{
    parameterList.push_back(parameter);
}

vector<string> Stuff::getIDList()
{
    return idList;
}

vector<string> Stuff::getStringList()
{
    return stringList;
}

vector<string> Stuff::getParameterList()
{
    return parameterList;
}
