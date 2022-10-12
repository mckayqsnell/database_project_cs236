#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QuestionMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "UndefinedAutomaton.h"
#include "LineCommentAutomaton.h"
#include "EndOfFileAutomaton.h"
#include "IDAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "StringAutomaton.h"
#include "UDStringAutomaton.h"
#include "UDBlockCommentAutomaton.h"
#include <iostream>

using namespace std;

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    /*for(auto item : automata)
    {
        delete item;
    }*/
    automata.clear(); //might need to delete with a for loop before clear????
}

void Lexer::CreateAutomata() {
    //this determines the order you run each automata. Might need to change this.
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QuestionMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new UDStringAutomaton());
    automata.push_back(new UDBlockCommentAutomaton());
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    while (input.size() > 0)
    {
        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);

        //handling white space between tokens
        int total_spaces = 0;
        while(isspace(input[total_spaces]))
        {
            if(input[total_spaces] == '\n')
            {
                ++lineNumber;
            }
            ++total_spaces;
        }
        input.erase(0,total_spaces);
        if(input.empty()) {
            break;
        }
        //cout << "deleting this many spaces: " << total_spaces << endl;

        for(unsigned int i = 0; i < automata.size(); ++i) //might give a clang tidy error???
        {
            int inputRead = automata.at(i)->Start(input);
            if(inputRead > maxRead)
            {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }

        if(maxRead > 0)
        {
            //cout << "I got a token --> ";
            string tk;
            for(int i = 0; i < maxRead; i++)
            {
               tk += input[i];
            }
            //cout << tk << " on line number: " << lineNumber << endl;
            Token* newToken = maxAutomaton->CreateToken(tk, lineNumber);
            //cout << newToken->toString() << endl;

            lineNumber += maxAutomaton->NewLinesRead();
            //cout << newToken->toString() << endl;
            tokens.push_back(newToken);
        }
        else
        {
            if(input[0] == '\n')
            {
                break;
            }

            maxRead = 1;
            string unDefinedString;
            unDefinedString = input[0];
            Automaton* unDefined = new UndefinedAutomaton();
            Token* unDefinedToken = unDefined->CreateToken(unDefinedString, lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(unDefinedToken);
        }

        input.erase(0,maxRead); //update input - remove those characters
    }
    Automaton* EOFAutomaton = automata.at(0);
    if(input.empty())
    {
        string eof = "";
        Automaton* EndOfFile = new EndOfFileAutomaton();
        Token* eof_token = EndOfFile->CreateToken(eof,lineNumber);
        lineNumber += EOFAutomaton->NewLinesRead();
        tokens.push_back(eof_token);
    }
    /*for(auto token: tokens)
    {
        cout << token->toString() << endl;
    }
    cout <<"Total Tokens = " << tokens.size(); */

}

vector<Token*> Lexer::getTokens() {
    return tokens;
}