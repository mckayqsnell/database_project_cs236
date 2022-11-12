#include "Interpreter.h"

Interpreter::Interpreter(Database* database, vector<Queries*> queries)
{
    this->database = database;
    this->query_list = queries;
}

Interpreter::~Interpreter()
{

}

void Interpreter::evaluateQueries()
{
    //database->toString();

     /*cout << "QueryList:" << endl;
    for(Queries* query : query_list)
    {
        cout << query->toString() << endl;
    } */

    for(Queries* query : query_list)
    {
        Relation* relation = database->findRelation(query->getName());
        vector<string> parameters = query->getParameterList();
        vector<unsigned int> columns_to_keep; //project
        vector<string> newAttributes; //rename
        map<string, unsigned int> seen;

        // For each parameter in the query, check if it is a string or and ID
        // If it is a string, select the column that matches the parameter
        // If it is an ID, mark the column in seen and add it to the columns_to_keep vector
        // If it is an ID and it has already been seen, select the column that matches the parameter
        // After the loop, project the columns that were marked in seen
        // After the loop, rename the columns that were marked in seen
        for(unsigned int i = 0; i < parameters.size(); i++)
        {
            //cerr << "Parameter: " << parameters.at(i) << endl;
            if(parameters.at(i).at(0) == '\'')
            {
                relation = relation->select(i, parameters.at(i));
                //columns_to_keep.push_back(i);
                //newAttributes.push_back(relation->getHeader().getAttribute(i));
            }
            else
            {
                if(seen.find(parameters.at(i)) == seen.end())
                {
                    seen.insert(pair<string, unsigned int>(parameters.at(i), i));
                    //cerr << "seen: " << parameters.at(i) << " " << i << endl;
                    columns_to_keep.push_back(i);
                    newAttributes.push_back(parameters.at(i));
                    //cerr << "newAttributes: " << parameters.at(i) << endl;
                }
                else
                {
                    relation = relation->select_two(i, seen.at(parameters.at(i)));
                }
            }
        }

        /*
        for(unsigned int i = 0; i < columns_to_keep.size(); i++)
        {
            newAttributes.push_back(relation->getHeader().getAttributes().at(columns_to_keep.at(i)));
        }
         */
        //relation = relation->rename(newAttributes);
        relation = relation->project(columns_to_keep);
        relation = relation->rename(newAttributes);
        cout << query->toString();
        if(!relation->getTuples().empty())
        {
            cout << " Yes(" << relation->getTuples().size() << ")" << endl;
            cout << relation->toString();
        }
        else
        {
            cout << " No" << endl;
        }
    }
}