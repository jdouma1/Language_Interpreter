// Language Interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "tokenizer.h"

int main() {
    //std::cout << "Hello World!" << std::endl;
    //Token t = Token(Token::tokenType::OP, "+");
    //std::cout << "My token:\n" << t << std::endl;

    Tokenizer t = Tokenizer();
    std::string line;
    std::cout << "Welcome! Press \'e\' to exit" << std::endl;
    while (true) {
        std::getline(std::cin, line);
        if (line == "e") {
            std::cout << "Goodbye" << std::endl;
            break;
        }
        else { t.parseLine(line); }
    }

    return 0;
}
