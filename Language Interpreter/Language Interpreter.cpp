// Language Interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Parser.h"

int main() {
    std::string text;
    std::cout << "Welcome! Enter \'\\e\' to exit" << std::endl;

    while (true) {
        std::getline(std::cin, text);
        if (text == "\\e") {
            std::cout << "Goodbye..." << std::endl;
            break;
        }
        else {
            Tokenizer t = Tokenizer(text);
            t.createTokens();
            Parser p = Parser(t.getTokens());
            Node *ast = p.parseTokens();
            std::cout << ast->toString() << std::endl;
            //ast->deleteNodes(ast);
            delete ast;
            ast = nullptr;
        }
    }

    return 0;
}
