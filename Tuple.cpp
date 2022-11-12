#include "Tuple.h"

Tuple::Tuple()
{

}

Tuple::~Tuple()
{

}

string Tuple::toString(Header header)
{
    if (getSize() != header.getSize()) {
        throw "Tuple size has to equal Header size!";
    }

    stringstream ss;
    string seperator = "";

    for (unsigned i = 0; i < getSize(); i++) {
        string name = header.getAttribute(i);
        string value = getValue(i);
        ss << seperator << " " << name << "=" << value;
        seperator = ",";
    }
    return ss.str();
}

void Tuple::addValue(string value)
{
    values.push_back(value);
}

string Tuple::getValue(unsigned int index)
{
    // for get_ methods
    if (index >= getSize()) {
        throw "Tuple : Index Out of Bounds!";
    }
    return values.at(index);
}

unsigned int Tuple::getSize()
{
    return values.size();
}
