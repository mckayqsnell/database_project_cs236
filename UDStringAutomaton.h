//
// Created by McKay Snell on 9/22/22.
//

#ifndef PROJECT1_UDSTRINGAUTOMATON_H
#define PROJECT1_UDSTRINGAUTOMATON_H


#include "Automaton.h"

class UDStringAutomaton : public Automaton
{
public:
    UDStringAutomaton() : Automaton(TokenType::UD_STRING) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
};


#endif //PROJECT1_UDSTRINGAUTOMATON_H
