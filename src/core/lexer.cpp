#include "../../include/emotion/types.h"
#include "../../include/emotion/core.h"
#include <cctype>

namespace emotion {

class Lexer {
private:
    std::string input;
    size_t position;
    int currentLine;
    int currentColumn;
    
public:
    Lexer(const std::string& source) 
        : input(source), position(0), currentLine(1), currentColumn(1) {}
    
    Token getNextToken() {
        while (position < input.size() && isspace(input[position])) {
            if (input[position] == '\n') {
                currentLine++;
                currentColumn = 1;
            } else {
                currentColumn++;
            }
            position++;
        }
        
        if (position >= input.size()) {
            return Token(TokenType::END_OF_FILE, "", currentLine, currentColumn);
        }
        
        char current = input[position];
        
        if (isalpha(current) || current == '_') {
            std::string value;
            while (position < input.size() && (isalnum(input[position]) || input[position] == '_')) {
                value += input[position++];
                currentColumn++;
            }
            return Token(TokenType::IDENTIFIER, value, currentLine, currentColumn - value.length());
        }
        
        if (isdigit(current)) {
            std::string value;
            while (position < input.size() && isdigit(input[position])) {
                value += input[position++];
                currentColumn++;
            }
            return Token(TokenType::NUMBER, value, currentLine, currentColumn - value.length());
        }
        
        std::string op(1, current);
        position++;
        currentColumn++;
        return Token(TokenType::OPERATOR, op, currentLine, currentColumn - 1);
    }
};

}
