// Language Interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "tokenizer.h"

int main() {
    std::string text;
    std::cout << "Welcome! Press \'exit\' to exit" << std::endl;

    while (true) {
        std::getline(std::cin, text);
        if (text == "exit") {
            std::cout << "Goodbye..." << std::endl;
            break;
        }
        else {
            Tokenizer t = Tokenizer(text);
            t.createTokens();
        }
    }

    return 0;
}
