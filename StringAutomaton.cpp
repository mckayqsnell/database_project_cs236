#include "StringAutomaton.h"
#include <iostream>

using namespace std;

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
    //cout << "String S1: " << input[index] << endl;
    if((unsigned int)index <= input.size()-1 && input[index] != '\'')
    {
        //cout << "String S1: I didn't read a single quote" << endl;
        if(input[index] == '\n')
        {
            ++newLines;
        }
        inputRead++;
        index++;
        S1(input);
    }
    else if(input[index] == '\'')
    {
        //cout << "String S1: I did read a single quote" << endl;
        inputRead++;
        index++;
        S2(input);
    }
    else if((unsigned int)index == input.size()-1 && input[index] != '\'')
    {
        //cout << "String S1: I have reached the end of the string" << endl;
        Serr();
    }
    else {
        Serr();
    }
}

void StringAutomaton::S2(const std::string& input) {
    //cout << "String S2: "<< input[index] << endl;
    if(input[index] != '\'')
    {
        //cout << "String S2: accepted string" << endl;
        //inputRead++;
        return;
    }
    else if(input[index] == '\'')
    {
        //cout << "String S2: read single quote" << endl;
       inputRead++;
       index++;
       S1(input);
    }
    else {
        Serr();
    }
    //else {
       //inputRead++;
    //}
}