#ifndef PROJECT1_QUESTIONMARKAUTOMATON_H
#define PROJECT1_QUESTIONMARKAUTOMATON_H


#include "Automaton.h"

class QuestionMarkAutomaton : public Automaton
{
public:
    QuestionMarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT1_QUESTIONMARKAUTOMATON_H
