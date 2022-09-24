#include "BlockCommentAutomaton.h"
//TODO: BLOCKCOMMENT... Maybe try loading up the characters into a string as you go then when it hits the error state
//send that entire string to Undefined?
void BlockCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead = 1;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S1(const std::string& input) {
    if(input[index] == '|')
    {
        inputRead++;
        index++;
        S2(input);
    }
    else
    {
        Serr();
    }
}

void BlockCommentAutomaton::S2(const std::string& input) {
    if(input[index] == '|')
    {
        inputRead++;
        index++;
        S3(input);
    }
    else if(input[index] != '|' &&  (unsigned int)index!= input.size()-1)
    {
        inputRead++;
        index++;
        S2(input);
    }
    else if((unsigned int)index == input.size()-1)
    {
        Serr();
    } //FIXME might need to add an else if statement saying if you see a # then go to an error state
    else
    {
        Serr();
    }
}

void BlockCommentAutomaton::S3(const std::string& input) {
    if(input[index] == '#')
    {
        inputRead++;
        index++;
        S4(input);
    }
    else if(input[index] == '|')
    {
        inputRead++;
        index++;
        S2(input);
    }
    else if(input[index] != '|')
    {
        S2(input);
    }
    else
    {
        Serr();
    }
}

void BlockCommentAutomaton::S4(const std::string& input) {
    return;
}