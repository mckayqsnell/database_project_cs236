#include "Interpreter.h"

Interpreter::Interpreter(Database* database, vector<Queries*> queries, vector<Rules*> rules)
{
    this->database = database;
    this->query_list = queries;
    this->rule_list = rules;
}

Interpreter::~Interpreter()
{

}

void Interpreter::evaluateQueries()
{
    cout << "Query Evaluation" << endl;
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

void Interpreter:: evaluateRules() // Fix this
{
    bool changed = true;
    int count = 0; // will need this later
    cout << "Rule Evaluation" << endl;
    while(changed)
    {
        changed = false;
        for(Rules* rule : rule_list)
        {
            deque<Relation*> predicate_relations = evaluatePredicates(rule);
            //Natural Join the relations in the deque using deque methods
            if(predicate_relations.size() >= 2)
            {
                Relation* p1 = predicate_relations.front();
                predicate_relations.pop_front();
                Relation* p2 = predicate_relations.front();
                predicate_relations.pop_front();
                predicate_relations.push_front(p1->naturalJoin(p2));
                while(predicate_relations.size() > 1)
                {
                    Relation* p1 = predicate_relations.front();
                    predicate_relations.pop_front();
                    Relation* p2 = predicate_relations.front();
                    predicate_relations.pop_front();
                    predicate_relations.push_front(p1->naturalJoin(p2));
                }
            }

            vector<unsigned int> columns_to_keep; //project
            vector<string> newAttributes; //rename
            vector<string> head_parameters = rule->getHeadPredicate()->getParameterList();
            vector<string> joined_relation_attributes = predicate_relations.front()->getHeader().getAttributes();
            // Get columns to keep for project
            for(unsigned int i = 0; i < head_parameters.size(); i++)
            {
                for(unsigned int j = 0; j < joined_relation_attributes.size(); j++)
                {
                    if(head_parameters.at(i) == joined_relation_attributes.at(j))
                    {
                        //cerr << "head_parameters.at(i): " << head_parameters.at(i) << endl;
                        //cerr << "joined_relation_attributes.at(j): " << joined_relation_attributes.at(j) << endl;
                        columns_to_keep.push_back(j);
                    }
                }
            }
            predicate_relations.front() = predicate_relations.front()->project(columns_to_keep);

            // get the new attributes from the head of the rule and rename the columns based on that
            for(unsigned int i = 0; i < head_parameters.size(); i++)
            {
                newAttributes.push_back(head_parameters.at(i));
            }
            predicate_relations.front() = predicate_relations.front()->rename(newAttributes);
            //Save the old relation
            Relation* old_relation = database->findRelation(rule->getHeadPredicate()->getName());

            cout << rule->toString() << endl;
            //cout << old_relation->toString() << endl;
            Relation* unionized_relation = old_relation->unionize(old_relation, predicate_relations.front());
            //cout << endl;
            //cout << unionized_relation->toString() << endl;
            if(unionized_relation->getSize() > old_relation->getSize())
            {
                changed = true;
                //cout << "CHANGED" << endl;
            }
            // now the unionized relation is the new relation in the database
            // so we need to replace the old relation with the new one
            old_relation->replaceRelation(unionized_relation);
        }
        ++count;
    }
    cout << endl;
    cout << "Schemes populated after " << count << " passes through the Rules." << endl;
    cout << endl;
}

deque<Relation*> Interpreter::evaluatePredicates(Rules* rule)
{
    deque<Relation*> predicate_relations;
    for(auto predicate : rule->getPredicateList())
    {
        Relation* relation = database->findRelation(predicate->getName());
        vector<string> parameters = predicate->getParameterList();
        vector<unsigned int> columns_to_keep; //project
        vector<string> newAttributes; //rename
        map<string, unsigned int> seen;
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
        relation = relation->project(columns_to_keep);
        relation = relation->rename(newAttributes);
        predicate_relations.push_back(relation);
    }
    return predicate_relations;
}