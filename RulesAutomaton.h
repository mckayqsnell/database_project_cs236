//
// Created by McKay Snell on 9/21/22.
//

#ifndef PROJECT1_RULES_H
#define PROJECT1_RULES_H


#include "Automaton.h"

class RulesAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);

public:
    RulesAutomaton() : Automaton(TokenType::RULES) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT1_RULES_H
