//
// Created by McKay Snell on 9/23/22.
//

#ifndef PROJECT1_UDBLOCKCOMMENT_H
#define PROJECT1_UDBLOCKCOMMENT_H


#include "Automaton.h"

class UDBlockCommentAutomaton : public Automaton
{
public:
    UDBlockCommentAutomaton() : Automaton(TokenType::UD_BLOCK_C) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);
};


#endif //PROJECT1_UDBLOCKCOMMENT_H
