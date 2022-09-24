//
// Created by McKay Snell on 9/21/22.
//

#ifndef PROJECT1_UNDEFINEDAUTOMATON_H
#define PROJECT1_UNDEFINEDAUTOMATON_H


#include "Automaton.h"

class UndefinedAutomaton : public Automaton
{
public:
    UndefinedAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT1_UNDEFINEDAUTOMATON_H
