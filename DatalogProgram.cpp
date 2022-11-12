#include "DatalogProgram.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

DatalogProgram::DatalogProgram()
{

}

DatalogProgram::~DatalogProgram()
{

}

string DatalogProgram::ToString()
{
    stringstream ss;
    ss << tmp << endl;
    for(auto & i : schemesList)
    {
        ss << i->toString() << endl;
    }
    return ss.str();
}