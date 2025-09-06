// Language Interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Parser.h"

bool isOnlyWhitespace(std::string text) {
    if (text.empty()) return true;
    for (char c : text) {
        if (!std::isspace(c)) return false;
    }
    return true;
}

int main() {
    std::string text;
    std::cout << "Welcome! Enter \'\\e\' to exit" << std::endl;
    Tokenizer t = Tokenizer();
    Parser p = Parser();
    Node* ast = nullptr;

    while (true) {
        std::getline(std::cin, text);
        if (text == "\\e") {
            std::cout << "Goodbye..." << std::endl;
            break;
        }
        else if (!isOnlyWhitespace(text)) {
            t = Tokenizer(text);
            t.createTokens();
            p = Parser(t.getTokens());
            ast = p.parseTokens();
            std::cout << "Printing AST: ";
            ast->recursivePrintNodes(ast);
            std::cout << std::endl;
            //ast->deleteNodes(ast);
        }
        else {
            std::cout << "Please enter input that is not plain whitespace nor empty" << std::endl;
        }
    }
    delete ast;
    ast = nullptr;

    return 0;
}
