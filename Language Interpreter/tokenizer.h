// tokenizer.h : This file contains methods which advance through input to create language tokens

#include "token.h"
#include "illegalCharError.h"
#include <vector>
#include <cctype>
#pragma once

class Tokenizer {
public:
    Tokenizer(std::string text);
    void advance();
    Token createNumber();
    void createTokens();
    std::vector<Token> getTokens() { return tokenList; }
private:
    std::string text;
    int pos;
    std::string currStr;
    std::vector<Token> tokenList;
};
