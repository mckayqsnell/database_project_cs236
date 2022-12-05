#include "Header.h"

Header::Header()
{

}

Header::~Header()
{

}

string Header::toString()
{
    stringstream ss;
    for(string s : attributes)
    {
        ss << s << " ";
    }
    return ss.str();
}

unsigned int Header::getSize()
{
    return attributes.size();
}

string Header::getAttribute(unsigned int index)
{
    if(index >= getSize())
    {
        throw "Header : Index Out of Bounds! Header size is";
    }
    return attributes.at(index);
}

void Header::addAttribute(string attribute)
{
    attributes.push_back(attribute);
}

void Header::addAttributeList(vector<string> attributeList)
{
    for(string attribute : attributeList)
    {
        addAttribute(attribute);
    }
}

vector<string> Header::getAttributes()
{
    return attributes;
}

unsigned int Header::getAttributeIndex(string attribute)
{
    for(unsigned int i = 0; i < getSize(); i++)
    {
        if(attributes.at(i) == attribute)
        {
            return i;
        }
    }
    throw "Header : Attribute not found!";
}

//Project 4
Header Header::combineHeaders(Header otherHeader)
{
    //combine the two headers, no duplicates
    Header combinedHeader;
    for(string attribute : attributes)
    {
        combinedHeader.addAttribute(attribute);
    }
    for(string attribute : otherHeader.getAttributes())
    {
        if(!combinedHeader.containsAttribute(attribute))
        {
            combinedHeader.addAttribute(attribute);
        }
    }

    return combinedHeader;
}

// contains attribute
bool Header::containsAttribute(string attribute)
{
    for(string s : attributes)
    {
        if(s == attribute)
        {
            return true;
        }
    }
    return false;
}

