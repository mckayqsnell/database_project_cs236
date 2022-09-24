#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead = 1;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {
    if(isalpha(input[index]) || isdigit(input[index]))
    {
        inputRead++;
        index++;
        S1(input);
    }
    else if(!(isalpha(input[index]) && isdigit(input[index])))
    {
        return;
    }
    else
    {
        Serr();
    }
}