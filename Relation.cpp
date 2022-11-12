#include "Relation.h"

Relation::Relation()
{

}

Relation::~Relation()
{

}

string Relation:: toString()
{
    stringstream ss;
    for(Tuple tuple : tuples)
    {
        if(tuple.getSize() > 0) //linux might get mad
        {
            ss << " " << tuple.toString(header) << endl;
        }
    }
    return ss.str();
}

void Relation::addTuple(Tuple tuple)
{
    tuples.insert(tuple);
}

void Relation::setName(string name)
{
    this->name = name;
}

Header Relation::getHeader()
{
    return header;
}

void Relation::setHeader(const Header &header)
{
    this->header = header;
}

const set<Tuple> &Relation::getTuples() const
{
    return tuples;
}

void Relation::setTuples(const set<Tuple> &tuples)
{
    this->tuples = tuples;
}

const string &Relation::getName() const
{
    return name;
}

unsigned int Relation::getSize()
{
    return tuples.size();
}

Relation* Relation::select(unsigned int col, string value)
{
    Relation* newRelation = new Relation(); // new empty relation

    newRelation->setName(name); //copy
    newRelation->setHeader(header); //copy
    for(Tuple tuple : tuples)
    {
        if(tuple.getValue(col) == value)
        {
            newRelation->addTuple(tuple);
        }
    }
    return newRelation;
}

Relation* Relation::select_two(unsigned int col1, unsigned int col2)
{
    Relation* newRelation = new Relation(); // new empty relation

    newRelation->setName(name); //copy
    newRelation->setHeader(header); //copy
    for(Tuple tuple : tuples)
    {
        if(tuple.getValue(col1) == tuple.getValue(col2))
        {
            newRelation->addTuple(tuple);
        }
    }
    return newRelation;
}

//Renaming just 1 column
Relation* Relation::rename(unsigned int col_to_rename, string new_name)
{
    Relation* newRelation = new Relation(); // new empty relation
    // Name
    newRelation->setName(name);
    // Header
    Header newHeader = header;
    newHeader.getAttribute(col_to_rename) = new_name;
    newRelation->setHeader(newHeader);
    // Tuples
    newRelation->setTuples(tuples);

    return newRelation;
}

// Renaming multiple columns
// [A, B, C, D] -> [E, F, G, H]
Relation* Relation::rename(vector<string> newAttributes)
{
    Relation* newRelation = new Relation(); // new empty relation
    // Make a new Header with newAttributes as its contents
    Header newHeader = Header(newAttributes);
    newRelation->setHeader(newHeader);
    // Copy over the name
    newRelation->setName(name);
    // Copy over the tuples
    newRelation->setTuples(tuples);

    return newRelation;
}

Relation* Relation::project(vector<unsigned int> columns_to_keep) {
    Relation *newRelation = new Relation(); // new empty relation
    // {3,2}
    // Name
    newRelation->setName(name);
    // create a new header(empty)
    Header newHeader = Header();

    // fill the new header with the attributes we want to keep
    // {A, B, C, D} -> {D, C}
    for (unsigned int colIndex : columns_to_keep) {
        newHeader.addAttribute(header.getAttribute(colIndex));
    }
    // put the new header in the new relation
    newRelation->setHeader(newHeader);

    // for each tuple t
    for (Tuple t: tuples)
    {
        // new empty tuple
        Tuple newTuple = Tuple();
        //fill that tuple with reorganized values
        // (1, 2, 3, 4) -> (4, 3)
        for(unsigned int colIndex : columns_to_keep)
        {
            newTuple.addValue(t.getValue(colIndex));
        }
        // add that tuple to the new relation
        newRelation->addTuple(newTuple);
    }
    return newRelation;
}

Relation* Relation::project(vector<string> columns_to_keep)
{
    Relation* newRelation = new Relation(); // new empty relation
    // {3,2}
    // Name
    newRelation->setName(name);
    // create a new header(empty)
    Header newHeader = Header();

    // fill the new header with the attributes we want to keep
    // {A, B, C, D} -> {D, C}
    for(string colName : columns_to_keep)
    {
        newHeader.addAttribute(colName);
    }
    // put the new header in the new relation
    newRelation->setHeader(newHeader);

    // for each tuple t
    for(Tuple t : tuples)
    {
        // new empty tuple
        Tuple newTuple = Tuple();
        //fill that tuple with reorganized values
        // (1, 2, 3, 4) -> (4, 3)
        for(string colName : columns_to_keep)
        {
            newTuple.addValue(t.getValue(header.getAttributeIndex(colName)));
            cerr << "getting the value of " << colName << " from " << header.getAttributeIndex(colName) << endl;
        }
        // add that tuple to the new relation
        newRelation->addTuple(newTuple);
    }
    return newRelation;
}
