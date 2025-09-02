/* parser.h :
 * This file contains classes and methods which parse tokens and structure them to grammatical hierarchy.
 * This includes Node structures for numbers and Binary Operator Nodes to form an Abstract Syntax Tree.
 * GRAMMAR:
 * expression: (term (PLUS|MINUS) term) --> term BiOpNode term
 * term: (factor (MUL|DIV) factor) --> factor BiOpNode factor
 * factor: (INT|FLOAT) --> NumNode
 */


#include "Tokenizer.h"
#include <typeinfo>
#pragma once

// NumNode class used to create AST nodes for numbers
class NumNode {
public:
	NumNode(Token token = Token()) {
		this->token = token;
		if (token.getTokenTypeToString() == "INT") {
			isInt = true;
			intData = std::stoi(token.getTokenValue());
		}
		else {
			isFloat = true;
			floatData = std::stof(token.getTokenValue());
		}
	}
	std::string toString() { return token.toString(); }
private:
	Token token;
	int intData;
	float floatData;
	bool isInt = false;
	bool isFloat = false;
};

// BiOpNode class used to create AST nodes for Binary Operators (+|-|*|/)
class BiOpNode {
public:
	BiOpNode(NumNode leftNode = NumNode(), NumNode rightNode = NumNode(), Token opToken = Token()) {
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
	Parser(std::vector<Token> tokenList) { this->tokenList = tokenList;  size = tokenList.size(); advance(); }
	// Generates an AST representation after parsing list of tokens
	void parseTokens() {
		// TODO
	}
	// Generates the next token in list
	void advance() {
		tokenIndex++;
		if (tokenIndex < size) currToken = tokenList[tokenIndex];
		else {
			currToken = Token();
			tokenIndex = -1;
		}
	}
	NumNode factor() {
		// TODO
	}
private:
	std::vector<Token> tokenList;
	int size;
	int tokenIndex = -1;
	Token currToken;
};

