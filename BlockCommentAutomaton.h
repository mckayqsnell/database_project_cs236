//
// Created by McKay Snell on 9/22/22.
//
#ifndef PROJECT1_BLOCKCOMMENTAUTOMATON_H
#define PROJECT1_BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton
{
public:
    BlockCommentAutomaton() : Automaton(TokenType::BLOCKCOMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);
};


#endif //PROJECT1_BLOCKCOMMENTAUTOMATON_H
