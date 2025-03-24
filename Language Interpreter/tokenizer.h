/* tokenizer.h : This file contains:
 * The Tokenizer class which contains methods that advance through input to create language tokens.
 * The Position class which keeps track of line and column numbers for tracking error locations.
 * Error base class and IllegalCharError subclass for generating syntax errors.
 */

#include "token.h"
#include <vector>
#include <cctype>
#pragma once

// Position class used to keep track of line and column numbers to pinpoint error location from files
class Position {
public:
    // Intitializes Position class with the current index, line number, and column number
    Position(int index = -1, int line = 0, int col = -1) {
        this->index = index;
        this->line = line;
        this->col = col;
    }
    void advance(char currChar);
    int getIndex() { return index; }
    int getLine() { return line; }
    int getCol() { return col; }
    Position getPositionCopy() { return Position(index, line, col); }
private:
    int index;
    int line;
    int col;
};

// This file contains methods which create and return the program's logical error messages
class Error {
public:
    Error(Position start = Position(-1, 0, -1), Position end = Position(-1, 0, -1), std::string errorName = "None", std::string details = "N/A") {
        this->posStart = start;
        this->posEnd = end;
        this->errorName = errorName;
        this->details = details;
    }
    std::string toString() {
        std::string lineStart = std::to_string(posStart.getLine());
        std::string colStart = std::to_string(posStart.getCol());
        std::string lineEnd = std::to_string(posEnd.getLine());
        std::string colEnd = std::to_string(posEnd.getCol());

        std::string start = "Start: [Line:" + lineStart + ", Column:" + colStart + "]\n";
        std::string end = "End: [Line:" + lineEnd + ", Column:" + colEnd + "]\n";

        return(start + end + "ERROR: " + errorName + "\nDETAILS: " + details + "\n");
    }
private:
    Position posStart;
    Position posEnd;
    std::string errorName;
    std::string details;
};

// This class subclasses the Error class to create specific error messages regarding illegal character usage
class IllegalCharError : Error {
public:
    IllegalCharError(Position start = Position(-1, 0, -1), Position end = Position(-1, 0, -1), std::string details = "Undefined illegal character details") : Error(start, end, "Illegal Character", details) {}
    std::string toString() {
        return(Error::toString());
    }
private:
};

// Tokenizer class used to advance through input and create tokens
class Tokenizer {
public:
    Tokenizer(std::string text);
    void advance();
    Token createNumber();
    void createTokens();
    std::vector<Token> getTokens() { return tokenList; }
    void printTokens();
private:
    std::string text;
    Position pos;
    char currChar;
    std::vector<Token> tokenList;
};
