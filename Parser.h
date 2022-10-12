#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H
#include "Lexer.h"
#include "Token.h"
#include "Schemes.h"
#include <vector>

class Parser {

private:
    bool pass;
    vector<Token*> tokens;
    vector<Schemes*> schemesList;
    int position;
    int numSchemes;

public:
    Parser(vector<Token*> tokens_);
    ~Parser();
    string toString();
    void parse();
    bool parseDatalogProgram();
    void parseScheme();
    void parseSchemeList();
    void parseIDList();
    void parseFactList();
    void parseFact();
    void parseStringList();
    void parseRuleList();
    void parseRule();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameter();
    void parseParameterList();
    void parseQuery();
    void parseQueryList();
};


#endif //PROJECT1_PARSER_H
