#include "tokenizer.h"

/*
 * Constructor which initializes the members:
 *     - "text" to line read in "Language Interpreter.cpp", 
 *     - "pos" to store current position in input
 *     - "currStr" to store current character being read from input (is type:string and not type:char due to token values being various lengths)
 * and calls "advance()" to increment "pos" and "currStr" to first values in the "text"
 */ 
Tokenizer::Tokenizer(std::string text) {
    this->text = text;
    pos = -1;
    currStr = "";
    advance();
}

// Increments the current position in the text and updates the "currStr" to current character being read
void Tokenizer::advance() {
    pos += 1;

    if (pos < text.size()) {
        currStr = "";
        currStr += text.at(pos);
    }
    else {
        currStr = "";
    }
}

// Reads numeral input to decipher whether the token is an integer or float type and returns the appropriate token
Token Tokenizer::createNumber() {
    std::string numStr = "";
    int dotCount = 0;

    // While the input is not empty (reached the end), and is a digit or decimal point
    while (currStr != "" && (std::isdigit(currStr.at(0)) || currStr == ".")) {
        if (currStr == ".") {
            // If one decimal point has already been used, the number is no longer a valid float representation, return an error token
            if (dotCount == 1) {
                numStr += currStr;
                return(Token(Token::TokenType::ERR, numStr));
            }
            dotCount += 1;
        }
        numStr += currStr;
        advance();
    }
    if (dotCount == 0) {
        return(Token(Token::TokenType::INT, numStr));
    }
    return(Token(Token::TokenType::FLOAT, numStr));
}

// Advances through the "text" to compare the input against the language grammar and syntax and create a list of tokens
void Tokenizer::createTokens() {
    while (currStr != "") {
        // Ignore whitespace
        if (std::isspace(currStr.at(0))) {
            advance();
        }
        else if (currStr == "+") {
            tokenList.push_back(Token(Token::TokenType::PLUS, currStr));
            advance();
        }
        else if (currStr == "-") {
            tokenList.push_back(Token(Token::TokenType::MINUS, currStr));
            advance();
        }
        else if (currStr == "*") {
            tokenList.push_back(Token(Token::TokenType::MUL, currStr));
            advance();
        }
        else if (currStr == "/") {
            tokenList.push_back(Token(Token::TokenType::DIV, currStr));
            advance();
        }
        else if (currStr == "(") {
            tokenList.push_back(Token(Token::TokenType::LPAREN, currStr));
            advance();
        }
        else if (currStr == ")") {
            tokenList.push_back(Token(Token::TokenType::RPAREN, currStr));
            advance();
        }
        else if (std::isdigit(currStr.at(0))) {
            tokenList.push_back(createNumber());

            // If an invalid number was provided, "tokenType" must be "ERR". Print an error message and return from reading input
            if (tokenList.back().getTokenTypeToString() == "ERR") {
                Error e = Error("Invalid Float", tokenList.back().getTokenValue());
                std::cout << e.toString() << std::endl;
                return;
            }
            advance();
        }
        // Character is not recognized in the language syntax. Print an error message and return from reading input
        else {
            std::string str = ("\"" + currStr + "\"");
            advance();
            IllegalCharError e = IllegalCharError(str);
            std::cout << e.toString() << std::endl;
            return;
        }
    }
    // After reaching the end of the input, print the list of tokens
    for (Token t : tokenList) {
        std::cout << t.toString() << std::endl;
    }
}
