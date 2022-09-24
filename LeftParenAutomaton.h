#ifndef PROJECT1_LEFTPAREN_H
#define PROJECT1_LEFTPAREN_H

#include "Automaton.h"

class LeftParenAutomaton : public Automaton
{
public:
    LeftParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT1_LEFTPAREN_H
