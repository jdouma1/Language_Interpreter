#include <iostream>
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
    Token(TokenType tokenType = TokenType::ERR, std::string token = "") {
        this->tokenType = tokenType;
        this->value = token;
    }
    std::string getTokenTypeToString();
    std::string getTokenValue() {
        return value;
    }
    std::string toString() {
        return(getTokenTypeToString() + ": " + value);
    }
private:
    TokenType tokenType;
    std::string value;
};
