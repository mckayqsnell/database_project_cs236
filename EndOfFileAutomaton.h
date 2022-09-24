//
// Created by McKay Snell on 9/22/22.
//

#ifndef PROJECT1_ENDOFFILEAUTOMATON_H
#define PROJECT1_ENDOFFILEAUTOMATON_H


#include "Automaton.h"

class EndOfFileAutomaton : public Automaton
{
public:
    EndOfFileAutomaton() : Automaton(TokenType::EndOfFile) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT1_ENDOFFILEAUTOMATON_H
