#include "Token.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    token_type = type;
    output = description;
    lineNumber = line;
}
string Token::toString()
{
    // cout << "in Token toString() function" << endl;
    stringstream ss;
    ss << "(" << typeToString() << "," << "\""<< output << "\"" << "," << lineNumber << ")";
    return ss.str();
}

string Token::typeToString()
{
    switch(token_type)
    {
        case TokenType::COLON: return "COLON";
        case TokenType::COLON_DASH: return "COLON_DASH";
        case TokenType::COMMA: return "COMMA";
        case TokenType::UNDEFINED: return "UNDEFINED";
        case TokenType::PERIOD: return "PERIOD";
        case TokenType::Q_MARK: return "Q_MARK";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::ADD: return "ADD";
        case TokenType::SCHEMES: return "SCHEMES";
        case TokenType::FACTS: return  "FACTS";
        case TokenType::RULES: return "RULES";
        case TokenType::QUERIES: return "QUERIES";
        case TokenType::LINECOMMENT: return "COMMENT";
        case TokenType::EndOfFile: return "EOF";
        case TokenType::ID: return "ID";
        case TokenType::BLOCKCOMMENT: return "COMMENT";
        case TokenType::STRING: return "STRING";
        case TokenType::UD_STRING: return  "UNDEFINED";
        case TokenType::UD_BLOCK_C: return "UNDEFINED";
    }
    return "Error"; // a string MUST be returned by the end
}

TokenType Token::getType()
{
    return token_type;
}

string Token::getOutput()
{
    return output;
}
