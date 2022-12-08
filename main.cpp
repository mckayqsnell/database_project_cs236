#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    // check command line arguments
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // open file
    string fileName = argv[1];
    ifstream input(fileName);
    if (!input.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
        return 1;
    }

    char ch; // if it gets mad for being slow trying changing this to s stringstream instead
    string inputString;
    while (input.get(ch))
    {
        inputString += ch;
    }

    //cout << "FiletoString: " << inputString << endl;

    //Project 1
    lexer->Run(inputString);

    //Project 2
    Parser* parser = new Parser(lexer->getTokens());
    parser->parse();

    //Project 3
    Interpreter* interpreter = new Interpreter(parser->getDatabase(), parser->getQueries(), parser->getRules());
    //Project 4
    //interpreter->evaluateRules();
    //Project 5
    interpreter->rulesOptimization();
    //Project 3
    interpreter->evaluateQueries();

    delete lexer;
    delete parser;
    delete interpreter;

    return 0;
}