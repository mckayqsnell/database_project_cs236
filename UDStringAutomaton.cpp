#include "UDStringAutomaton.h"
void UDStringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead = 1;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void UDStringAutomaton::S1(const std::string &input) {
    if(input[index] != '\'' && (unsigned int)index != input.size()-1 )
    {
        inputRead++;
        index++;
        S1(input);
    }
    else if(index == input.size()-1)
    {
        S2(input);
    }
    else {
        Serr();
    }
}

void UDStringAutomaton::S2(const std:: string &input) {
    inputRead++;
}
