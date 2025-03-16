#include "token.h"

std::string Token::getTokenTypeToString() {
    switch (tokenType) {
    case TokenType::PLUS:
        return("PLUS");
    case TokenType::MINUS:
        return("MINUS");
    case TokenType::MUL:
        return("MULTIPLY");
    case TokenType::DIV:
        return("DIVIDE");
    case TokenType::LPAREN:
        return("LPAREN");
    case TokenType::RPAREN:
        return("RPAREN");
    case TokenType::INT:
        return("INTEGER");
    case TokenType::FLOAT:
        return("FLOAT");
    case TokenType::ERR:
        return("ERR");
    default:
        return("UNKNOWN");
    }
}