#include "UDStringAutomaton.h"
#include <iostream>

using namespace std;

void UDStringAutomaton::S0(const std::string& input) {
    //cout << "S0: " << input[index] << endl;
    if (input[index] == '\'')
    {
        inputRead = 1;
        index++;
        //cout << "index: " << index << endl;
        //cout << "S0 --> I read a single quote in UDString" << endl;
        S1(input);
    }
    else {
        Serr();
    }
}

void UDStringAutomaton::S1(const std::string &input) {
    //cout << "S1: " << input[index] << endl;
    if((unsigned int)index <= input.size()-1 && input[index] != '\'')
    {
        //cout << "S1 --> I did not read a single quote in UDString" << ": " << input[index] << " @ index: " << index << endl;
        if(input[index] == '\n')
        {
            ++newLines;
        }
        inputRead++;
        index++;
        //cout << "index: " << index << endl;
        S1(input);
    }
    else if(input[index] == '\'')
    {
        //cout << "I have read a single quote in S1" << endl;
        inputRead++;
        index++;
        //cout << "index: " << index << endl;
        S2(input);
    }
    else if((unsigned int)index >= input.size()-1)
    {
        //cout << "I have reached the end of the file" << endl;
        //inputRead++;
        //index++;
        //cout << "index: " << index << endl;
        S3(input);
    }
    else {
        Serr();
    }
}

void UDStringAutomaton::S2(const std:: string &input) {
    //cout << "S2: " << input[index] << endl;
    if(input[index] == '\'')
    {
        //cout << "I read a single quote in S2" << endl;
        inputRead++;
        //cout << "index: " << index << endl;
        index++;
        //cout << "in S2, here is the index: " << index << endl;
        S3(input);
    }
    else
    {
        //cout << "UDS: Error state reached" << endl;
        Serr();
    }
}

void UDStringAutomaton::S3(const std:: string &input) {
    //cout << "S3: " << input[index] << endl;
    if((unsigned int)index <= input.size()-1)
    {
        //cout << "I have not reached EOF, sending input to S1: " << index << endl;
        //inputRead++;
        //index++;
        //cout << "index: " << index << endl;
        S1(input);
    }
    else
    {
        //cout << "UDS: Accepted Undefined string" << endl;
        return;
    }
}
