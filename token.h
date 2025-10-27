#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

struct Token { // Token structure to represent a lexical token
    string type;     // e.g. "ID", "INT", "PLUS", "ASSIGN", etc.
    string lexeme;   // actual text, e.g. "x", "5", "+"
    int position;    // character index or line number in the input
};

#endif // TOKEN_H
