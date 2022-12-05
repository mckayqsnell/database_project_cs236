#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H
#include "Lexer.h"
#include "Token.h"
#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Predicate.h"
#include "Queries.h"
#include <vector>
#include <set>

// Project 3 includes...
#include "Database.h"
#include "Relation.h"

class Parser {

private:
    bool pass;
    vector<Token*> tokensToParse;
    vector<Schemes*> schemesList;
    vector<Facts*> factList;
    vector<Queries*> queryList;
    vector<Rules*> rulesList;
    vector<Predicate*> predicateList;
    set<string> domain;
    int position;
    int numSchemes;
    int numFacts;
    int numQueries;
    int numRules;

    //Project 3
    Database* database;

public:
    explicit Parser(vector<Token*> tokens_);
    ~Parser();
    string toString();
    void parse();
    bool parseDatalogProgram();
    void parseScheme();
    void parseSchemeList();
    void parseIDList(Stuff *stuff);
    void parseFactList();
    void parseFact();
    void parseStringList(Stuff *stuff);
    void parseRuleList();
    void parseRule();
    Predicate* parseHeadPredicate();
    void parsePredicate(Stuff *stuff);
    void parsePredicateList(Rules *rule);
    void parseParameter(Stuff *stuff);
    void parseParameterList(Stuff *stuff);
    void parseQuery();
    void parseQueryList();
    void setDomain(vector<string> string_list);
    set<string> getDomain();

    //project 3
    Database* getDatabase();
    vector<Queries*> getQueries();

    //project 4
    vector<Rules*> getRules();
};


#endif //PROJECT1_PARSER_H
