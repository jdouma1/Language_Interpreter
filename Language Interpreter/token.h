//Token.h : This file contains methods which create and return language token members

#include <iostream>
#include <string>
#pragma once

class Token {
public:
    enum class TokenType {
        PLUS,
        MINUS,
        MUL,
        DIV,
        LPAREN,
        RPAREN,
        INT,
        FLOAT,
        ERR
    };
    Token(TokenType tokenType = TokenType::ERR, std::string value = "-1") {
        this->tokenType = tokenType;
        this->value = value;
    }
    // Returns a string representation of the token type
    std::string getTokenTypeToString();
    std::string getTokenValue() { return value; }
    // Prints the token type and the value held
    std::string toString() { return(getTokenTypeToString() + ":" + value); }
private:
    TokenType tokenType;
    std::string value;
};
