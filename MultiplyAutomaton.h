//
// Created by McKay Snell on 9/21/22.
//

#ifndef PROJECT1_MULTIPLYAUTOMATON_H
#define PROJECT1_MULTIPLYAUTOMATON_H


#include "Automaton.h"

class MultiplyAutomaton : public Automaton
{
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT1_MULTIPLYAUTOMATON_H
