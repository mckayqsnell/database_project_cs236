#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

using namespace std;

class Lexer
{
private:
    vector<Automaton*> automata;
    vector<Token*> tokens;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);

    // TODO: add other public methods here
    // TODO: add totalTokens method
};

#endif // LEXER_H

