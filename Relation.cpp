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

Relation* Relation::naturalJoin(Relation* otherRelation)
{
    //make the header h for the result relation
    //(combine r1's header with r2's header)
    Header newHeader = Header();
    newHeader = header.combineHeaders(otherRelation->getHeader());
    //cout << "newHeader: " << newHeader.toString() << endl;

    //make a new empty relation r using header h
    Relation* newRelation = new Relation();
    newRelation->setHeader(newHeader);
    newRelation->setName(name + otherRelation->getName()); // shouldn't matter

    //for each tuple t1 in r1
    for(Tuple t1 : tuples)
    {
        //for each tuple t2 in r2
        for(Tuple t2 : otherRelation->getTuples())
        {
            //if t1 and t2 can join
            if(t1.canJoin(t2, header, otherRelation->getHeader()))
            {
                //join t1 and t2 to make tuple t
                Tuple newTuple = t1.combineTuples(t2, header, otherRelation->getHeader());
                //add tuple t to relation r
                //cout << "From naturalJoin: " << newHeader.toString() << endl;
                //cout << "From naturalJoin: " << newTuple.toString(newHeader) << endl;
                newRelation->addTuple(newTuple);
            }
        }
    }

    return newRelation;
}

//Unionize
Relation* Relation::unionize(Relation* old_relation, Relation* new_relation)
{
    /*cout << "Unionizing " << old_relation->getName() << " and " << new_relation->getName() << endl;
    cout << "Old Relation: " << endl;
    cout << old_relation->toString() << endl;
    cout << "New Relation: " << endl;
    cout << new_relation->toString() << endl; */

    //make a new empty relation r using header h
    Relation* newRelation = new Relation();
    newRelation->setHeader(old_relation->getHeader());
    newRelation->setName(old_relation->getName()); // shouldn't matter

    // add all the tuples from the old relation
    for(Tuple t : old_relation->getTuples())
    {
        newRelation->addTuple(t);
    }
    // add all the tuples from the new relation, if they don't already exist
    for(Tuple t : new_relation->getTuples())
    {
        if(!newRelation->findTuple(t))
        {
            newRelation->addTuple(t);
            cout << t.toString(header) << endl;
        }
    }

    return newRelation;
}

// Replace the current relation with the new relation(for unionize)
void Relation::replaceRelation(Relation* newRelation)
{
    name = newRelation->getName();
    header = newRelation->getHeader();
    tuples = newRelation->getTuples();
}

// Find a tuple in the relation
bool Relation::findTuple(Tuple t)
{
    for(Tuple tuple : tuples)
    {
        if(tuple == t)
        {
            return true;
        }
    }
    return false;
}
