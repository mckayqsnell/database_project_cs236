#include "Database.h"

Database::Database()
{

}
Database::~Database()
{

}

string Database::toString()
{
    stringstream ss;
    for( const auto& relation : database)
    {
        //cerr << "In toString database function" << endl;
        cout << endl;
        ss << "relationName: " << relation.first << " headers: " << relation.second->getHeader().toString()
        << endl << "Tuples: " << endl << relation.second->toString() << endl;
    }

    return ss.str();
}

void Database::addRelation(string name, Relation* relation)
{
       database.insert(pair<string, Relation*>(name, relation));
       //pretty sure order doesn't matter here, but I could be wrong
} //might need to return a relation pointer?

Relation* Database::findRelation(string name)
{
    if(database.find(name) != database.end()) //might need to change this to >= database.size()
    {
        return database.at(name);
    }
    else
    {
        return nullptr;
    }
}

void Database::addTuple(string name, Tuple tuple)
{
    database.at(name)->addTuple(tuple);
}

map<string, Relation*> Database::getDatabase()
{
    return database;
}