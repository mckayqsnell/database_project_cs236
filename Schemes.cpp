#include "Schemes.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

Schemes::Schemes()
{
    num_Schemes = 0;
}

Schemes::~Schemes()
{

}

string Schemes::toString()
{
   stringstream ss;
   //ss << tmp << " this is scheme number: " << num_Schemes << " - " << getName() << endl;
   ss << getName() << "(";
   vector<string> idl = getIDList();
   for(unsigned int i = 0; i < idl.size(); i++)
   {
       ss << idl.at(i);
       if(i < idl.size()-1) {
           ss << ",";
       }
   }
   ss << ")" << endl;
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