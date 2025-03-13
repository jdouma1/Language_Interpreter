#include "tokenizer.h"

Tokenizer::Tokenizer() {
    this->key.assign(R"(\b(if|else|for|while)\b)");
    this->id.assign("[_a-zA-Z][_a-zA-Z0-9]{0,30}");
    this->op.assign("[\-|\+|\*|\/|\(|\)]");
    this->constant.assign("[0-9]+");
}

//Function matches syntax defined below to create Abstract Syntax Tree (AST)
//Keywords: [if], [else], [for], [while]
//Identifiers: [a-zA-Z_]+
//Operators: [+], [-], [*], [/], [(], [)]
//Constants: [0-9]+

void Tokenizer::parseLine(std::string line) {
    //Create index [i] to traverse string input
    //Create string [tokenVal] to hold subset of list for tokenization
    int i = 0;
    std::string tokenVal = "";
    Token token;
    
    while (i < line.size()) {
        tokenVal.push_back(line.at(i));

        //String matches whitespace, ignore
        if (tokenVal == " ") {
            tokenVal = "";
        }
        //String matches identifier, continue iteration while matching
        //This logic block also checks if string matches keyword at various points, 
        else if (std::regex_match(tokenVal, this->id)) {
            while (std::regex_match(tokenVal, this->id)) {
                ++i;

                //String matched but index out of bounds, push token
                if (i >= line.size()) {
                    //String matches keyword exactly, push token
                    if (std::regex_match(tokenVal, this->key)) {
                        token = Token(Token::TokenType::KEY, tokenVal);
                        this->tokenList.push(token);
                        tokenVal = "";
                        continue;
                    }
                    token = Token(Token::TokenType::ID, tokenVal);
                    this->tokenList.push(token);
                    tokenVal = "";
                    continue;
                }
                tokenVal.push_back(line.at(i));
            }
            //Continue to next loop iteration
            if (tokenVal == "") {
                continue;
            }
            //String did not match
            //Reset iterator to last valid match instance
            //Remove last value of string that did not match token
            if (!std::regex_match(tokenVal, this->id)) {
                --i;
                tokenVal.pop_back();
            }
            //String matches keyword exactly, push token
            if (std::regex_match(tokenVal, this->key)) {
                token = Token(Token::TokenType::KEY, tokenVal);
                this->tokenList.push(token);
                tokenVal = "";
            }
            //Create token and push
            else {
                token = Token(Token::TokenType::ID, tokenVal);
                this->tokenList.push(token);
                tokenVal = "";
            }
        }
        //String matches operator, push token
        else if (std::regex_match(tokenVal, this->op)) {
            token = Token(Token::TokenType::OP, tokenVal);
            this->tokenList.push(token);
            tokenVal = "";
        }
        //String matches constant, continue iteration while matching
        else if (std::regex_match(tokenVal, this->constant)) {
            while (std::regex_match(tokenVal, this->constant)) {
                ++i;

                //String matched but index out of bounds, push token
                if (i >= line.size()) {
                    token = Token(Token::TokenType::CONSTANT, tokenVal);
                    this->tokenList.push(token);
                    tokenVal = "";
                    continue;
                }
                tokenVal.push_back(line.at(i));
            }
            //Continue to next loop iteration
            if (tokenVal == "") {
                continue;
            }
            //String did not match
            //Reset iterator to last valid match instance
            //Remove last value of string that did not match token
            if (!std::regex_match(tokenVal, this->constant) && tokenVal != "") {
                --i;
                tokenVal.pop_back();
            }
            //Create token and push
            token = Token(Token::TokenType::CONSTANT, tokenVal);
            this->tokenList.push(token);
            tokenVal = "";
        }
        //Input does not match recognized language syntax
        else {
            token = Token(Token::TokenType::ERR, tokenVal);
            this->tokenList.push(token);
            tokenVal = "";
        }
        ++i;
    }
    //Have reached end of input string and have stack of tokens
    std::cout << "PRINTING LIST OF TOKENS IN REVERSE\n" << std::endl;
    while (!this->tokenList.empty()) {
        std::cout << this->tokenList.top() << std::endl;
        this->tokenList.pop();
    }
}
