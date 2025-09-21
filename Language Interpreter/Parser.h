/* Parser.h :
 * This file contains classes and methods which parse tokens and structure them to grammatical hierarchy.
 * This includes Node structures for numbers and Binary Operator Nodes to form an Abstract Syntax Tree.
 * GRAMMAR:
 * expression: term ((PLUS|MINUS) term)* --> term BiOpNode term
 * term: factor ((MUL|DIV) factor)* --> factor BiOpNode factor
 * factor: (INT|FLOAT) --> NumNode
 */

#include "Tokenizer.h"
#include <functional>
#pragma once

// NumNode class used to create AST nodes for numbers
class NumNode {
public:
	NumNode(Token token = Token()) {
		this->token = token;
	}
	std::string toString() { return token.toString(); }
private:
	Token token;
};

// BiOpNode class used to create AST nodes for Binary Operators (+|-|*|/)
class Node {
public:
	// Constructor for a leaf node
	Node(Token token) {
		this->leftNode = nullptr;
		this->token = token;
		this->rightNode = nullptr;
	}
	// Constructor for a default empty node or an inner node
	Node(Node *leftNode = nullptr, Token token = Token(), Node *rightNode = nullptr) {
		this->leftNode = leftNode;
		this->token = token;
		this->rightNode = rightNode;
	}
	// Frees memory by recursively deleting nodes
	void deleteNodes(Node* node) {
		if (node == nullptr) return;
		deleteNodes(node->leftNode);
		deleteNodes(node->rightNode);
		delete node;
	}
	void recursivePrintNodes(Node *node) {
		if (node == nullptr) {
			return;
		}
		recursivePrintNodes(node->leftNode);
		std::cout << token.toString() << " ";

		recursivePrintNodes(node->rightNode);
	}
	Node* leftNode;
	Token token;
	Node* rightNode;
private:
};

// Parser class used to analyze token input and generate an Abstract Syntax Tree for interpretation
class Parser {
public:
	Parser(std::vector<Token> tokenList = {}) { this->tokenList = tokenList;  size = tokenList.size(); advance(); }

	// Generates the next token in list
	bool advance() {
		tokenIndex++;
		if (tokenIndex < size) {
			currToken = tokenList[tokenIndex];
			return true;
		}
		else return false;
	}

	// Generates an AST representation after parsing list of tokens
	Node *parseTokens() {
		return expr();
	}

	// Generates an expression TERM ((PLUS|MINUS) TERM)*
	Node* expr() {
		Node* left = term();
		std::string tokenType = currToken.getTokenTypeToString();

		Node* node = nullptr;
		while (tokenType == "PLUS" || tokenType == "MINUS") {
			Token opToken = currToken;
			advance();
			Node* right = term();
			left = new Node(left, opToken, right);
			tokenType = currToken.getTokenTypeToString();
		}
		return left;
	}

	// Generates a term FACTOR ((MUL|DIV) FACTOR)*
	Node *term() {
		Node* left = factor();
		std::string tokenType = currToken.getTokenTypeToString();

		Node *node = nullptr;
		while (tokenType == "MUL" || tokenType == "DIV") {
			Token opToken = currToken;
			advance();
			Node* right = factor();
			node = new Node(left, opToken, right);
			tokenType = currToken.getTokenTypeToString();
		}
		return left;
	}

	// Generates a factor (INT|FLOAT)
	Node* factor() {
		Token t = currToken;
		std::string tokenType = currToken.getTokenTypeToString();
		if (tokenType == "INT" || tokenType == "FLOAT") {
			advance();
			std::cout << "CREATED FACTOR: " << t.toString() << std::endl;
			return new Node(t);
		}
		else if (tokenType != "ERR") {
			std::cout << "IMPROPER SYNTAX. CHARACTER NOT RECOGNIZED" << std::endl;
			syntaxError = true;
		}
		else {
			std::cout << "IMPROPER GRAMMAR. MUST HAVE [INT|FLOAT (OPERATOR) INT|FLOAT]";
			grammarError = true;
		}
		return new Node(Token());
	}
private:
	std::vector<Token> tokenList;
	int size;
	int tokenIndex = -1;
	Token currToken;
	bool syntaxError = false;
	bool grammarError = false;
};

