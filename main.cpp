#include "Lexer.h"
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

    char ch; //could use a string stream instead? Dylan mentioned it could be inefficent with a big file? we'll see?
    string inputString;
    while (input.get(ch))
    {
        inputString += ch;
    }

    cout << "FiletoString: " << inputString << endl;
    lexer->Run(inputString);

    delete lexer;

    return 0;
}