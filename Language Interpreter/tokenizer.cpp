#include "tokenizer.h"

Tokenizer::Tokenizer(std::string text) {
    this->text = text;
    pos = -1;
    currStr = "";
    advance();
}

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

Token Tokenizer::createNumber() {
    std::string numStr = "";
    int dotCount = 0;

    while (currStr != "" && (std::isdigit(currStr.at(0)) || currStr == ".")) {
        if (currStr == ".") {
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

void Tokenizer::createTokens() {
    while (currStr != "") {
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
            if (tokenList.back().getTokenTypeToString() == "ERR") {
                Error e = Error("Invalid Float", tokenList.back().getTokenValue());
                std::cout << e.toString() << std::endl;
                return;
            }
            advance();
        }
        else {
            std::string str = ("\"" + currStr + "\"");
            advance();
            IllegalCharError e = IllegalCharError(str);
            std::cout << e.toString() << std::endl;
            return;
        }
    }
    for (Token t : tokenList) {
        std::cout << t.toString() << std::endl;
    }
}
