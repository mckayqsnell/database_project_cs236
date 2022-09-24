//
// Created by McKay Snell on 9/21/22.
//

#ifndef PROJECT1_FACTSAUTOMATON_H
#define PROJECT1_FACTSAUTOMATON_H

//
// Created by McKay Snell on 9/21/22.
//

#include "Automaton.h"

class FactsAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);

public:
    FactsAutomaton() : Automaton(TokenType::FACTS) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT1_FACTSAUTOMATON_H
