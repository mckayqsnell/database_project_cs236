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

bool Tuple::canJoin(Tuple otherTuple, Header header1, Header header2)
{
    for (unsigned i = 0; i < header1.getSize(); i++) {
        for (unsigned j = 0; j < header2.getSize(); j++) {
            if (header1.getAttribute(i) == header2.getAttribute(j)) {
                if (getValue(i) != otherTuple.getValue(j)) {
                    return false;
                }
            }
        }
    }
    return true;
}

Tuple Tuple::combineTuples(Tuple otherTuple, Header header1, Header header2)
{
    // inner join the two tuples, and make sure the values are in the order of the combined header
    // combine the two headers
    /*cout << "Combining Tuples" << endl;
    cout << "Header 1: " << header1.toString() << endl;
    cout << toString(header1) << endl;
    cout << "Header 2: " << header2.toString() << endl;
    cout << otherTuple.toString(header2) << endl; */

    // combine the two headers
    Header combinedHeader = header1;
    for (unsigned i = 0; i < header2.getSize(); i++) {
        string attribute = header2.getAttribute(i);
        if (!combinedHeader.containsAttribute(attribute)) {
            combinedHeader.addAttribute(attribute);
        }
    }
    //cout << "Combined Header: " << combinedHeader.toString() << "from combineTuples" << endl;

    // combine the two tuples
    Tuple combinedTuple;
    for (unsigned i = 0; i < combinedHeader.getSize(); i++) {
        string attribute = combinedHeader.getAttribute(i);
        if (header1.containsAttribute(attribute)) {
            combinedTuple.addValue(getValue(header1.getAttributeIndex(attribute)));
        } else {
            combinedTuple.addValue(otherTuple.getValue(header2.getAttributeIndex(attribute)));
        }
    }
    //cout << "Combined Tuple: " << combinedTuple.toString(combinedHeader) << endl; //this is right

    return combinedTuple;





    /*Tuple newTuple;
    for (unsigned i = 0; i < header1.getSize(); i++) {
        newTuple.addValue(getValue(i));
    }
    for (unsigned i = 0; i < header2.getSize(); i++) {
        bool found = false;
        for (unsigned j = 0; j < header1.getSize(); j++) {
            if (header1.getAttribute(j) == header2.getAttribute(i)) {
                found = true;
            }
        }
        if (!found) {
            newTuple.addValue(otherTuple.getValue(i));
        }
    }
    return newTuple; */
}
