#include "Parser.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Parser::Parser(vector<Token*> tokens_)
{
    this->pass = false;
    this->tokensToParse = tokens_;
    this->position = 0;
    this->numSchemes = 0;
    this->numFacts = 0;
    this->numQueries = 0;
    this->numRules = 0;

/*
    for(auto & i : tokensToParse)
    {
        cout << i->toString() << endl;
    }
*/

    auto it = tokensToParse.begin();
    while(it != tokensToParse.end())
    {
        if ((*it)->getType() == TokenType::LINECOMMENT)
        {
            it = tokensToParse.erase(it);
        }
        else if ((*it)->getType() == TokenType::BLOCKCOMMENT)
        {
            it = tokensToParse.erase(it);
        }
        else
        {
            ++it;
        }
    }

    //project 3
    database = new Database();
}

//Project 3
Database* Parser::getDatabase()
{
    return database;
}

vector<Queries*> Parser::getQueries()
{
    return queryList;
}

Parser::~Parser()
{
    for(auto & scheme : schemesList)
    {
        delete scheme;
    }

    for(auto & fact : factList)
    {
        delete fact;
    }

    for(auto & query : queryList)
    {
        delete query;
    }

    for(auto & rule : rulesList)
    {
        delete rule;
    }

    for(auto & predicate : predicateList)
    {
        delete predicate;
    }

    delete database; // project 3
}

string Parser::toString()
{
    stringstream ss;

    //Schemes
    ss << "Schemes(" << schemesList.size() << ")" << ":" << endl;
    for(auto & i : schemesList)
    {
        ss << "  " << i->toString();
    }

    //Facts
    ss << "Facts(" << factList.size() << ")" << ":" << endl;
    for(auto & i : factList)
    {
        ss << "  " << i->toString();
    }

    //Predicates
    ss << "Rules(" << rulesList.size() << ")" << ":" << endl;
    for(auto & i : rulesList)
    {
        ss << "  " << i->toString() << endl;
    }

    //Queries
    ss << "Queries(" << queryList.size() << ")" << ":" << endl;
    for(auto & i : queryList)
    {
        ss << "  " << i->toString();
    }

    //Domain
    ss << "Domain(" << domain.size() << ")" << ":" << endl;
    for(const auto & it : domain)
    {
        ss << "  " << it << endl;
    }

    return ss.str();
}

void Parser::setDomain(vector<string> string_list)
{
    for(auto & i : string_list)
    {
        domain.insert(i);
    }
}

set<string> Parser::getDomain()
{
    return domain;
}

void Parser::parse()
{
    //Project 2 print out
    if(parseDatalogProgram())
    {
        //cout << "Success!" << endl;
        //cout << toString();
    }

    //Project 3
    /*cout << endl;
    cout << "Database: " << endl;
    cout << database->toString(); */
}

bool Parser::parseDatalogProgram()
{
    try {
        if(tokensToParse.at(position)->getType() == TokenType::SCHEMES)
        {
            ++position;
            if(tokensToParse.at(position)->getType() == TokenType::COLON)
            {
                ++position;
                parseScheme();
                parseSchemeList();
                if(tokensToParse.at(position)->getType() == TokenType::FACTS)
                {
                    ++position;
                    if(tokensToParse.at(position)->getType() == TokenType::COLON)
                    {
                        ++position;
                        parseFactList();
                        if(tokensToParse.at(position)->getType() == TokenType::RULES)
                        {
                            ++position;
                            if(tokensToParse.at(position)->getType() == TokenType::COLON)
                            {
                                ++position;
                                parseRuleList();
                                if(tokensToParse.at(position)->getType() == TokenType::QUERIES)
                                {
                                    ++position;
                                    if(tokensToParse.at(position)->getType() == TokenType::COLON)
                                    {
                                        ++position;
                                        parseQuery();
                                        //cout << "Current token is: " << tokens.at(position)->toString() << endl;
                                        parseQueryList();
                                        if(tokensToParse.at(position)->getType() == TokenType::EndOfFile)
                                        {
                                            pass = true;
                                            return pass;
                                        }
                                        else
                                        {
                                            throw tokensToParse.at(position);
                                        }
                                    }
                                    else
                                    {
                                        throw tokensToParse.at(position);
                                    }
                                }
                                else
                                {
                                    throw tokensToParse.at(position);
                                }
                            }
                            else
                            {
                                throw tokensToParse.at(position);
                            }
                        }
                        else
                        {
                            throw tokensToParse.at(position);
                        }
                    }
                }
                else
                {
                    throw tokensToParse.at(position);
                }
            }
            else
            {
                throw tokensToParse.at(position);
            }
        }
        else
        {
            throw tokensToParse.at(position);
        }
    }
    catch (Token* error)
    {
        pass = false;
        cout << "Failure!" << endl;
        cout << "   " << error->toString() << endl;
        return pass;
    }

    return false; // this was just kinda thrown in to fix it. Does not affect anything.
}

void Parser::parseScheme()
{
    Schemes* schemes = new Schemes();
    Relation* relation = new Relation();

    if(tokensToParse.at(position)->getType() == TokenType::ID)
    {
        // put id in schemes name
        schemes->setName(tokensToParse.at(position)->getOutput());
        // put id in relation name
        relation->setName(tokensToParse.at(position)->getOutput());
        //cerr << "token at posistion: " << position << " is a " << tokens.at(position)->toString() << endl;
        ++position;

        if(tokensToParse.at(position)->getType() == TokenType::LEFT_PAREN)
        {
            ++position;

            if(tokensToParse.at(position)->getType() == TokenType::ID)
            {
                // put the ID in schemes
                //cerr << "Parsing " << tokensToParse.at(position)->getOutput() << endl;
                schemes->addID(tokensToParse.at(position)->getOutput());
                ++position;
                parseIDList(schemes);

                //Project 3
                Header header; //made this an object to make setHeader work.
                header.addAttributeList(schemes->getIDList());
                relation->setHeader(header);

                if(tokensToParse.at(position)->getType() == TokenType::RIGHT_PAREN)
                {
                    //Project 3
                    //cerr << "pushed back relation" << endl;
                    database->addRelation(relation->getName(), relation);
                    //cerr << "added relation to database" << endl;
                    // TODO: ask dad the point of mapping
                    //name to the relation when you already have the name of relation stored
                    // also ask about joan using name mapped to header. (the big box row).


                    ++numSchemes;
                    ++position;
                }
                else
                {
                    throw tokensToParse.at(position);
                }
            }
            else
            {
                throw tokensToParse.at(position);
            }
        }
        else
        {
            throw tokensToParse.at(position);
        }
    }
    else
    {
        throw tokensToParse.at(position);
    }
    schemes->setNumSchemes(numSchemes);
    schemesList.push_back(schemes);
}

void Parser::parseIDList(Stuff *stuff)
{
    //cout << "in ParseIDList" << endl;
    if(tokensToParse.at(position)->getType() == TokenType::COMMA)
    {
        ++position;
        if(tokensToParse.at(position)->getType() == TokenType::ID)
        {
            // put the id in stuff
            stuff->addID(tokensToParse.at(position)->getOutput());
            stuff->addParameter(tokensToParse.at(position)->getOutput());
            ++position;
            parseIDList(stuff);
        }
        else
        {
            throw tokensToParse.at(position);
        }
    }
    else
    {
        return;
    }
}

void Parser::parseSchemeList()
{
    if(tokensToParse.at(position)->getType() == TokenType::ID)
    {
        parseScheme();
        if(tokensToParse.at(position)->getType() == TokenType::ID)
        {
            parseSchemeList();
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }
}

void Parser::parseFactList()
{
    if(tokensToParse.at(position)->getType() == TokenType::ID)
    {
        parseFact();
        if(tokensToParse.at(position)->getType() == TokenType::ID)
        {
            parseFactList();
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }
}

void Parser::parseFact()
{
    Facts* fact = new Facts();
    if(tokensToParse.at(position)->getType() == TokenType::ID)
    {
        fact->setName(tokensToParse.at(position)->getOutput());
        //Project 3
        try {
            if(database->findRelation(fact->getName()) == nullptr)
            {
                string error = "Error: No scheme for fact " + fact->getName(); // can probably put this whole thing in a function call.
                throw error;
            }
        }
        catch (string error) {
            cout << error << endl;
            exit(1);
        }

        ++position;
        if(tokensToParse.at(position)->getType() == TokenType::LEFT_PAREN)
        {
            ++position;
            if(tokensToParse.at(position)->getType() == TokenType::STRING)
            {
                fact->addString(tokensToParse.at(position)->getOutput());
                ++position;
                parseStringList(fact);
                //Project 3
                Tuple tuple(fact->getStringList());
                database->findRelation(fact->getName())->addTuple(tuple);
                //cout << tokens.at(position)->toString() << endl;
                if(tokensToParse.at(position)->getType() == TokenType::RIGHT_PAREN)
                {
                    ++position;
                    if(tokensToParse.at(position)->getType() == TokenType::PERIOD)
                    {
                        setDomain(fact->getStringList());
                        ++position;
                        ++numFacts;
                    }
                    else
                    {
                        throw tokensToParse.at(position);
                    }
                }
                else
                {
                    throw tokensToParse.at(position);
                }
            }
            else
            {
                throw tokensToParse.at(position);
            }
        }
        else
        {
            throw tokensToParse.at(position);
        }
    }
    else
    {
        throw tokensToParse.at(position);
    }
    fact->setNumFacts(numFacts);
    factList.push_back(fact);
}

void Parser::parseStringList(Stuff *stuff)
{
    if(tokensToParse.at(position)->getType() == TokenType::COMMA)
    {
        ++position;
        if(tokensToParse.at(position)->getType() == TokenType::STRING)
        {
            stuff->addString(tokensToParse.at(position)->getOutput());
            ++position;
            parseStringList(stuff);
        }
        else
        {
            throw tokensToParse.at(position);
        }
    }
    else
    {
        return;
    }
}

void Parser::parseRuleList()
{
    if(tokensToParse.at(position)->getType() == TokenType::ID)
    {
        parseRule();
        if(tokensToParse.at(position)->getType() == TokenType::ID)
        {
            parseRuleList();
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }
}

void Parser::parseRule()
{
    Rules* rule = new Rules();
    rule->setHeadPredicate(parseHeadPredicate());

    if(tokensToParse.at(position)->getType() == TokenType::COLON_DASH)
    {
        ++position;
        // new Predicate
        Predicate* predicate = new Predicate();
        parsePredicate(predicate);
        predicateList.push_back(predicate);
        rule->addPredicate(predicate);

        parsePredicateList(rule);

        if(tokensToParse.at(position)->getType() == TokenType::PERIOD)
        {
            ++position;
            ++numRules;
        }
        else
        {
            throw tokensToParse.at(position);
        }
    }
    else
    {
        throw tokensToParse.at(position);
    }
    rule->setNumRules(numRules);
    rulesList.push_back(rule);
}

void Parser::parsePredicateList(Rules *rule)
{
    if(tokensToParse.at(position)->getType() == TokenType::COMMA)
    {
        ++position;
        // new Predicate
        Predicate* predicate = new Predicate();
        parsePredicate(predicate);
        predicateList.push_back(predicate);
        rule->addPredicate(predicate);

        // put that Predicate into the rule - can't do this right now
        parsePredicateList(rule);
        return;
    }
    else
    {
        return;
    }
}

Predicate* Parser::parseHeadPredicate()
{
    Predicate* predicate = new Predicate();

    if(tokensToParse.at(position)->getType() == TokenType::ID)
    {
        predicate->setName(tokensToParse.at(position)->getOutput());
        ++position;
        if(tokensToParse.at(position)->getType() == TokenType::LEFT_PAREN)
        {
            ++position;
            if(tokensToParse.at(position)->getType() == TokenType::ID)
            {
                predicate->addParameter(tokensToParse.at(position)->getOutput());
                ++position;
                parseIDList(predicate);
                if(tokensToParse.at(position)->getType() == TokenType::RIGHT_PAREN)
                {
                    ++position;
                }
                else
                {
                    throw tokensToParse.at(position);
                }
            }
            else
            {
                throw tokensToParse.at(position);
            }
        }
        else
        {
            throw tokensToParse.at(position);
        }
    }
    else
    {
        throw tokensToParse.at(position);
    }
    predicateList.push_back(predicate);
    return predicate;
}

void Parser::parsePredicate(Stuff *stuff)
{
    if(tokensToParse.at(position)->getType() == TokenType::ID)
    {
        stuff->setName(tokensToParse.at(position)->getOutput());
        ++position;
        if(tokensToParse.at(position)->getType() == TokenType::LEFT_PAREN)
        {
            ++position;
            parseParameter(stuff);
            parseParameterList(stuff);
            if(tokensToParse.at(position)->getType() == TokenType::RIGHT_PAREN)
            {
                ++position;
                return;
            }
            else
            {
                throw tokensToParse.at(position);
            }

        }
        else
        {
            throw tokensToParse.at(position);
        }
    }
    else
    {
        throw tokensToParse.at(position);
    }
}

void Parser::parseParameter(Stuff *stuff)
{
    if(tokensToParse.at(position)->getType() == TokenType::STRING)
    {
        stuff->addParameter(tokensToParse.at(position)->getOutput());
        ++position;
        return;
    }
    else if(tokensToParse.at(position)->getType() == TokenType::ID)
    {
        stuff->addParameter(tokensToParse.at(position)->getOutput());
        ++position;
        return;
    }
    else
    {
        throw tokensToParse.at(position);
    }
}

void Parser::parseParameterList(Stuff *stuff)
{
    if(tokensToParse.at(position)->getType() == TokenType::COMMA)
    {
        ++position;
        parseParameter(stuff);
        //cout << "parseParameterList-->" << "Current token is: " << tokens.at(position) << endl;
        parseParameterList(stuff);// might need to put this in an if ID

        return;
    }
    else
    {
       return;
    }
}

void Parser::parseQuery()
{
    Queries* queries = new Queries();
    parsePredicate(queries);
    if(tokensToParse.at(position)->getType() == TokenType::Q_MARK)
    {
        position++;
        numQueries++;
    }
    else
    {
        throw tokensToParse.at(position);
    }
    queries->setNumQueries(numQueries);
    queryList.push_back(queries);
    // Process the query
}

void Parser::parseQueryList()
{
    if(tokensToParse.at(position)->getType() == TokenType::ID)
    {
        parseQuery();
        if(tokensToParse.at(position)->getType() == TokenType::ID)
        {
            parseQueryList();
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }
}
