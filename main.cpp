#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
using namespace std;

struct Token {
    string type;
    string lexeme;
    int position;
};

bool isSingleLetterID(const string& lexeme) {
    return lexeme.size() == 1 && islower(lexeme[0]);
}

vector<Token> tokenize(const string& input, vector<Token>& invalidTokens) {
    vector<Token> tokens;
    int i = 0;
    int n = input.length();

    while (i < n) {
        char ch = input[i];

        // Skip whitespace
        if (isspace(ch)) {
            i++;
            continue;
        }

        int start = i;

        // Identifiers (single-letter lowercase)
        if (isalpha(ch)) {
            string lexeme;
            while (i < n && isalpha(input[i])) {
                lexeme += input[i++];
            }

            if (isSingleLetterID(lexeme))
                tokens.push_back({"ID", lexeme, start});
            else
                invalidTokens.push_back({"INVALID_ID", lexeme, start});

            continue;
        }

        // Integers (multi-digit allowed)
        if (isdigit(ch)) {
            string num;
            while (i < n && isdigit(input[i])) {
                num += input[i++];
            }
            tokens.push_back({"INT", num, start});
            continue;
        }

        // Operators / Symbols
        switch (ch) {
            case '+': tokens.push_back({"PLUS", "+", i++}); break;
            case '-': tokens.push_back({"MINUS", "-", i++}); break;
            case '*': tokens.push_back({"MULT", "*", i++}); break;
            case '/': tokens.push_back({"DIV", "/", i++}); break;
            case '=': tokens.push_back({"ASSIGN", "=", i++}); break;
            case '(': tokens.push_back({"LPAREN", "(", i++}); break;
            case ')': tokens.push_back({"RPAREN", ")", i++}); break;
            case ';': tokens.push_back({"SEMI", ";", i++}); break;
            default: {
                string invalidLexeme(1, ch);
                i++;
                // capture consecutive invalid characters
                while (i < n && !isspace(input[i]) && !isalnum(input[i]) &&
                       input[i] != '+' && input[i] != '-' && input[i] != '*' &&
                       input[i] != '/' && input[i] != '=' &&
                       input[i] != '(' && input[i] != ')' && input[i] != ';') {
                    invalidLexeme += input[i++];
                }
                invalidTokens.push_back({"INVALID_CHAR", invalidLexeme, start});
                break;
            }
        }
    }
    return tokens;
}

void printTokens(const vector<Token>& tokens) {
    cout << "\n=== TOKEN TABLE ===\n";
    cout << left << setw(15) << "Type" << setw(15) << "Lexeme" << "Position\n";
    cout << string(40, '-') << endl;
    for (const auto& t : tokens) {
        cout << left << setw(15) << t.type << setw(15) << t.lexeme << t.position << endl;
    }
}

void printInvalids(const vector<Token>& invalidTokens) {
    cout << "\n=== INVALID TOKENS ===\n";
    if (invalidTokens.empty()) {
        cout << "None\n";
    } else {
        for (const auto& inv : invalidTokens) {
            cout << "LexicalError at position " << inv.position
                 << ": invalid token '" << inv.lexeme << "'\n";
        }
    }
}

void printSummary(const vector<Token>& tokens) {
    cout << "\n=== TOKEN COUNT SUMMARY ===\n";
    int idCount = 0, intCount = 0, opCount = 0, symCount = 0;

    for (const auto& t : tokens) {
        if (t.type == "ID") idCount++;
        else if (t.type == "INT") intCount++;
        else if (t.type == "PLUS" || t.type == "MINUS" || t.type == "MULT" || t.type == "DIV")
            opCount++;
        else
            symCount++;
    }

    cout << "Total Tokens: " << tokens.size() << endl;
    cout << "Identifiers : " << idCount << endl;
    cout << "Integers    : " << intCount << endl;
    cout << "Operators   : " << opCount << endl;
    cout << "Symbols     : " << symCount << endl;
}

int main() {
    vector<string> tests = {
        "x = (3 + 5) * 2;",
        "ab = 3$;",
        "y=12+z;",
        "A = 2;",
        "m = (4 + ) * 3;"
    };

    for (const auto& src : tests) {
        cout << "\n=============================================\n";
        cout << "Input: " << src << "\n";

        vector<Token> invalidTokens;
        vector<Token> tokens = tokenize(src, invalidTokens);

        printTokens(tokens);
        printInvalids(invalidTokens);
        printSummary(tokens);
    }

    return 0;
}
