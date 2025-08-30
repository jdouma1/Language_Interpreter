/* parser.h :
 * This file contains classes and methods which parse tokens and structure them to grammatical hierarchy.
 * This includes Node structures for numbers and Binary Operator Nodes to form an Abstract Syntax Tree.
 * GRAMMAR:
 * expression: (term (PLUS|MINUS) term)
 * term: (factor (MUL|DIV) factor)
 * factor: (INT|FLOAT)
 */


#include "Tokenizer.h"
#include <typeinfo>
#pragma once

// NumNode class used to create AST nodes for numbers
class NumNode {
public:
	NumNode(int token = -1) { this->intToken = token; isInt = true; }
	NumNode(float token = -1) { this->floatToken = token; isFloat = true; }
	std::string toString() { if (isInt) return std::to_string(intToken); return std::to_string(floatToken); }
private:
	int intToken;
	float floatToken;
	bool isInt = false;
	bool isFloat = false;
};

// BiOpNode class used to create AST nodes for Binary Operators (+|-|*|/)
class BiOpNode {
public:
	BiOpNode(NumNode leftNode = NumNode(-1), NumNode rightNode = NumNode(-1), Token opToken = Token(Token::TokenType::ERR, "?")) {
		this->leftNode = leftNode;
		this->rightNode = rightNode;
		this->opToken = opToken;
	}
	std::string toString() { return leftNode.toString() + opToken.toString() + rightNode.toString(); }
private:
	NumNode leftNode;
	NumNode rightNode;
	Token opToken;
};

// Parser class used to analyze token input and generate an Abstract Syntax Tree for interpretation
class Parser {
public:
private:
};

