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

void Interpreter:: evaluateRules(vector<Rules*> rules_to_evaluate, set<int> sccs) // Fix this
{
    bool changed = true;
    int count = 0;
    while(changed)
    {
        changed = false;
        for(Rules* rule : rules_to_evaluate) // Changing this to operate off of a list of rules I give it from the parameter
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
        //if there is only one rule in the list, and it doesn't have a self loop, then we need to break out of the loop
        if(rules_to_evaluate.size() == 1)
        {
            if(!detectSelfLoop(rules_to_evaluate.at(0)))
            {
                changed = false;
            }
        }
        ++count;
    }
    //cout << endl;
    cout << count << " passes: ";
    for(int i : sccs)
    {
        cout << "R" << i;
        //place a comma if it isn't the last element
        if(i != *sccs.rbegin())
        {
            cout << ",";
        }
    }
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

//Project 5
void Interpreter::rulesOptimization()
{
    //Build the dependency graph and the reverse dependency graph
    graph = new Graph(rule_list.size());
    reverseGraph = new Graph(rule_list.size());
    for(unsigned int i = 0; i < rule_list.size(); i++)
    {
        for(Predicate* predicate : rule_list.at(i)->getPredicateList())
        {
            for(unsigned int j = 0; j < rule_list.size(); j++)
            {
                if(predicate->getName() == rule_list.at(j)->getHeadPredicate()->getName())
                {
                    graph->addEdge(i, j);
                    reverseGraph->addEdge(j, i);
                }
            }
        }
    }
    cout << "Dependency Graph" << endl;
    cout << graph->toString() << endl;
    cout << "Reverse Dependency Graph" << endl;
    cout << reverseGraph->toString() << endl << endl;

    //Run DFS-Forest (in regular numeric order) on the reverse dependency graph to get the post-order
    reverseGraph->dfs_Forest();
    vector<unsigned int> post_order = reverseGraph->getPostOrder();
    for(auto i : post_order)
    {
        cout << i;
        if(i != post_order.back())
        {
            cout << ","; // Guess this works
        }
    }
    cout << endl << endl;
    //Run DFS-Forest (in reverse post-order) on the forward dependency graph to find the strongly connected components
    graph->dfs_Forest_Reverse(post_order);
    vector<set<int>> strongly_connected_components = graph->getSCCs();
    cout << "Rule Evaluation" << endl;
    /*for(auto scc : strongly_connected_components)
    {
        cout << "SCC: ";
        for(auto i : scc)
        {
            cout <<"R"<< i;
            if(i != *scc.rbegin())
            {
                cout << ",";
            }
        }
        cout << endl;
    } */
    //Evaluate the rules in each component
    //Look up the rules in the rule list using the indices in the strongly connected components
    //and store them in a vector called rules_to_evaluate
    for(auto scc : strongly_connected_components)
    {
        vector<Rules*> rules_to_evaluate;
        for(auto i : scc)
        {
            rules_to_evaluate.push_back(rule_list.at(i));
        }
        cout << "SCC: ";
        for(auto i : scc)
        {
            cout <<"R"<< i;
            if(i != *scc.rbegin())
            {
                cout << ",";
            }
        }
        cout << endl;
        evaluateRules(rules_to_evaluate, scc);
    }
    cout << endl;
}

bool Interpreter::detectSelfLoop(Rules* rule) {
    for(Predicate* predicate : rule->getPredicateList())
    {
        if(predicate->getName() == rule->getHeadPredicate()->getName())
        {
            return true;
        }
    }
    return false;
}