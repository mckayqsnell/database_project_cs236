//
// Created by McKay Snell on 9/21/22.
//

#ifndef PROJECT1_LINECOMMENTAUTOMATON_H
#define PROJECT1_LINECOMMENTAUTOMATON_H

#include "Automaton.h"

class LineCommentAutomaton : public Automaton
{
public:
    LineCommentAutomaton() : Automaton(TokenType::LINECOMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
};


#endif //PROJECT1_LINECOMMENTAUTOMATON_H
