#include "LineCommentAutomaton.h"

void LineCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead = 1;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void LineCommentAutomaton::S1(const std::string& input) {
    if(input[index] != '\n' && input[index] != '|')
    {
        inputRead++;
        index++;
        S1(input);
    }
    else if(input[index] == '\n')
    {
       return;
    }
    else
    {
        Serr();
    }
}