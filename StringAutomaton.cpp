#include "StringAutomaton.h"
// TODO:NEED ERROR STATE. IF IT HITS END OF STRING THATS A FAIL STATE.
void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead = 1;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
void StringAutomaton::S1(const std::string& input) {
    if(index == input.size()-1)
    {
        if(input[index] != '\'')
        {
            Serr();
        }
    }
    else if(input[index] != '\'' )
    {
        inputRead++;
        index++;
        S1(input);
    }
    else if(input[index] == '\'')
    {
        inputRead++;
        index++;
        S2(input); //FIXME might need to increment inputRead and index
    }
    else {
        Serr();
    }
}

void StringAutomaton::S2(const std::string& input) {
    if(input[index] == '\'')
    {
       inputRead++;
       index++;
       S1(input);
    }
    //else {
       // inputRead++;
    //}
}