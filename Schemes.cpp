#include "Schemes.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

Schemes::Schemes()
{
    this->tmp = "hi";
}

Schemes::~Schemes()
{

}

string Schemes::toString()
{
   stringstream ss;
   ss << tmp << " this is scheme number: " << num_Schemes << endl;
   return ss.str();
}

void Schemes::setNumSchemes(int numSchemes)
{
    this->num_Schemes = numSchemes;
}

int Schemes:: getNumSchemes()
{
    return num_Schemes;
}