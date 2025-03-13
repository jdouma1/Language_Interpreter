#include "token.h"
#include <regex>
#include <stack>
#pragma once

class Tokenizer {
public:
    Tokenizer();
    void parseLine(std::string line);
private:
    std::stack<Token> tokenList;
    std::regex key;
    std::regex id;
    std::regex op;
    std::regex constant;
};
