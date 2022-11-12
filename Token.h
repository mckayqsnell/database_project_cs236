#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    LINECOMMENT,
    EndOfFile,
    ID,
    BLOCKCOMMENT,
    STRING,
    UD_STRING,
    UD_BLOCK_C,
    UNDEFINED
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    TokenType token_type;
    string output;
    int lineNumber;
    string typeToString();

public:
    Token(TokenType type, string description, int line);
    string toString();
    TokenType getType();
    string getOutput();
};

#endif // TOKEN_H

