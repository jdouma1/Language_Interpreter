//token.h : This file contains methods which create and return language token members

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
    Token(TokenType tokenType = TokenType::ERR, std::string value = "") {
        this->tokenType = tokenType;
        this->value = value;
    }
    std::string getTokenTypeToString();
    std::string getTokenValue() { return value; }
    //Returns string representation of Token object
    std::string toString() { return(getTokenTypeToString() + ":" + value); }
private:
    TokenType tokenType;
    std::string value;
};
