#include "Parser.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
//TODO: ask dad about github branches and how they work. Can I upload this to a different branch so that I can
//maintain version control? So if I change anything in past projects on accident I can always have the original stored there.

Parser::Parser(vector<Token*> tokens_)
{
    this->pass = false;
    this->tokens = tokens_;
    this->position = 0;
    this->numSchemes = 0;

    for(unsigned int i = 0; i < this->tokens.size(); i++)
    {
        //Erase/ignore line comments
        if(this->tokens.at(i)->getType() == TokenType::LINECOMMENT)
        {
            this->tokens.erase(this->tokens.begin()+i);
        }
        //Erase/ignore block comments
        if(this->tokens.at(i)->getType() == TokenType::BLOCKCOMMENT)
        {
            this->tokens.erase(this->tokens.begin()+i);
        }
        //cout << tokens.at(i)->toString() << endl;
    }
    //cout <<"Total Tokens = " << tokens.size();

}

Parser::~Parser()
{

}

string Parser::toString()
{
    stringstream ss;
    for(unsigned int i = 0; i < schemesList.size(); ++i)
    {
        ss << schemesList.at(i)->toString() << endl;
    }
    return ss.str();
}

void Parser::parse()
{
    if(parseDatalogProgram()) //TODO: try and catch it just doesn't know how to deal with it
    {
        cout << "Successful! last token was: " << tokens.at(position)->toString() << endl;
        cout << toString();
    }
}

bool Parser::parseDatalogProgram()
{
    try {
        if(tokens.at(position)->getType() == TokenType::SCHEMES)
        {
            ++position;
            if(tokens.at(position)->getType() == TokenType::COLON)
            {
                ++position;
                parseScheme();
                parseSchemeList();
                if(tokens.at(position)->getType() == TokenType::FACTS)
                {
                    ++position;
                    if(tokens.at(position)->getType() == TokenType::COLON)
                    {
                        ++position;
                        parseFactList();
                        if(tokens.at(position)->getType() == TokenType::RULES)
                        {
                            ++position;
                            if(tokens.at(position)->getType() == TokenType::COLON)
                            {
                                ++position;
                                parseRuleList();
                                if(tokens.at(position)->getType() == TokenType::QUERIES)
                                {
                                    ++position;
                                    if(tokens.at(position)->getType() == TokenType::COLON)
                                    {
                                        ++position;
                                        parseQuery();
                                        //cout << "Current token is: " << tokens.at(position)->toString() << endl;
                                        parseQueryList();
                                        if(tokens.at(position)->getType() == TokenType::EndOfFile)
                                        {
                                            pass = true;
                                            return pass;
                                        }
                                        else
                                        {
                                            throw tokens.at(position);
                                        }
                                    }
                                    else
                                    {
                                        throw tokens.at(position);
                                    }
                                }
                                else
                                {
                                    throw tokens.at(position);
                                }
                            }
                            else
                            {
                                throw tokens.at(position);
                            }
                        }
                        else
                        {
                            throw tokens.at(position);
                        }
                    }
                }
                else
                {
                    throw tokens.at(position);
                }
            }
            else
            {
                throw tokens.at(position);
            }
        }
        else
        {
            throw tokens.at(position);
        }
        cout << "Successful! last token was: " << tokens.at(position)->toString() << endl;
        cout << toString();
    }
    catch (Token* error)
    {
        pass = false;
        cout << "Failure!" << endl;
        cout << "\t" << error->toString() << endl;
        return pass;
    }

    return false;
}

void Parser::parseScheme()
{
    Schemes* schemes = new Schemes();

    if(tokens.at(position)->getType() == TokenType::ID)
    {
        //cout << "token at posistion: " << position << " is a " << tokens.at(position)->toString() << endl;
        ++position;

        if(tokens.at(position)->getType() == TokenType::LEFT_PAREN)
        {
            ++position;

            if(tokens.at(position)->getType() == TokenType::ID)
            {
                ++position;
                parseIDList();
                if(tokens.at(position)->getType() == TokenType::RIGHT_PAREN)
                {
                    ++numSchemes;
                    ++position;
                }
                else
                {
                    throw tokens.at(position);
                }
            }
            else
            {
                throw tokens.at(position);
            }
        }
        else
        {
            throw tokens.at(position);
        }
    }
    else
    {
        throw tokens.at(position);
    }
    schemes->setNumSchemes(numSchemes);
    schemesList.push_back(schemes);
}

void Parser::parseIDList()
{
    //cout << "in ParseIDList" << endl;
    if(tokens.at(position)->getType() == TokenType::COMMA)
    {
        ++position;
        if(tokens.at(position)->getType() == TokenType::ID)
        {
            ++position;
            parseIDList();
        }
        else
        {
            throw tokens.at(position);
        }
    }
    else
    {
        return;
    }
}

void Parser::parseSchemeList()
{

    parseScheme();
    if(tokens.at(position)->getType() == TokenType::ID)
    {
        parseSchemeList();
    }
    else
    {
        return;
    }
}

void Parser::parseFactList()
{
    parseFact();
    if(tokens.at(position)->getType() == TokenType::ID)
    {
        parseFactList();
    }
    else
    {
        return;
    }
}

void Parser::parseFact()
{
    if(tokens.at(position)->getType() == TokenType::ID)
    {
        ++position;
        if(tokens.at(position)->getType() == TokenType::LEFT_PAREN)
        {
            ++position;
            if(tokens.at(position)->getType() == TokenType::STRING)
            {
                ++position;
                parseStringList();
                //cout << tokens.at(position)->toString() << endl;
                if(tokens.at(position)->getType() == TokenType::RIGHT_PAREN)
                {
                    ++position;
                    if(tokens.at(position)->getType() == TokenType::PERIOD)
                    {
                        ++position;
                        return;
                    }
                    else
                    {
                        throw tokens.at(position);
                    }
                }
                else
                {
                    throw tokens.at(position);
                }
            }
            else
            {
                throw tokens.at(position);
            }
        }
        else
        {
            throw tokens.at(position);
        }
    }
    else
    {
        throw tokens.at(position);
    }
}
void Parser::parseStringList()
{
    if(tokens.at(position)->getType() == TokenType::COMMA)
    {
        ++position;
        if(tokens.at(position)->getType() == TokenType::STRING)
        {
            ++position;
            parseStringList();
        }
        else
        {
            throw tokens.at(position);
        }
    }
    else
    {
        return;
    }
}

void Parser::parseRuleList()
{
    parseRule();
    if(tokens.at(position)->getType() == TokenType::ID)
    {
        parseRuleList();
    }
    else
    {
        return;
    }
}

void Parser::parseRule()
{
    parseHeadPredicate();
    if(tokens.at(position)->getType() == TokenType::COLON_DASH)
    {
        ++position;
        parsePredicate();
        parsePredicateList();
        if(tokens.at(position)->getType() == TokenType::PERIOD)
        {
            ++position;
            return;
        }
        else
        {
            throw tokens.at(position);
        }
    }
    else
    {
        throw tokens.at(position);
    }
}

void Parser::parsePredicateList()
{
    if(tokens.at(position)->getType() == TokenType::COMMA)
    {
        ++position;
        parsePredicate();
        parsePredicateList();
        return;
    }
    else
    {
        return;
    }
}

void Parser::parseHeadPredicate()
{
    if(tokens.at(position)->getType() == TokenType::ID)
    {
        ++position;
        if(tokens.at(position)->getType() == TokenType::LEFT_PAREN)
        {
            ++position;
            if(tokens.at(position)->getType() == TokenType::ID)
            {
                ++position;
                parseIDList();
                if(tokens.at(position)->getType() == TokenType::RIGHT_PAREN)
                {
                    ++position;
                    return;
                }
                else
                {
                    throw tokens.at(position);
                }
            }
            else
            {
                throw tokens.at(position);
            }
        }
        else
        {
            throw tokens.at(position);
        }
    }
    else
    {
        throw tokens.at(position);
    }
}

void Parser::parsePredicate()
{
    if(tokens.at(position)->getType() == TokenType::ID)
    {
        ++position;
        if(tokens.at(position)->getType() == TokenType::LEFT_PAREN)
        {
            ++position;
            parseParameter();
            parseParameterList();
            if(tokens.at(position)->getType() == TokenType::RIGHT_PAREN)
            {
                ++position;
                return;
            }
            else
            {
                throw tokens.at(position);
            }

        }
        else
        {
            throw tokens.at(position);
        }
    }
    else
    {
        throw tokens.at(position);
    }
}

void Parser::parseParameter()
{
    if(tokens.at(position)->getType() == TokenType::STRING)
    {
        ++position;
        return;
    }
    else if(tokens.at(position)->getType() == TokenType::ID)
    {
        ++position;
        return;
    }
    else
    {
        throw tokens.at(position);
    }
}

void Parser::parseParameterList()
{
    if(tokens.at(position)->getType() == TokenType::COMMA)
    {
        ++position;
        parseParameter();
        //cout << "parseParameterList-->" << "Current token is: " << tokens.at(position) << endl;
        parseParameterList();// might need to put this in an if ID

        return;
    }
    else
    {
       return;
    }
}

void Parser::parseQuery()
{
    parsePredicate();
    if(tokens.at(position)->getType() == TokenType::Q_MARK)
    {
        position++;
        return;
    }
    else
    {
        throw tokens.at(position);
    }
}

void Parser::parseQueryList()
{
    if(tokens.at(position)->getType() == TokenType::ID)
    {
        parseQuery();
        if(tokens.at(position)->getType() == TokenType::ID)
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
