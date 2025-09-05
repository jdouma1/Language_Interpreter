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
	std::string toString() {
		if (leftNode == nullptr && rightNode == nullptr) return token.toString();
		//else if (leftNode == nullptr && rightNode != nullptr) return token.toString() + rightNode->toString();
		//else if (leftNode != nullptr && rightNode == nullptr) return leftNode->toString() + token.toString();
		return '(' + leftNode->toString() + ' ' + token.toString() + ' ' + rightNode->toString() + ')';
	}

	Node *leftNode;
	Token token;
	Node *rightNode;
private:
};

// Parser class used to analyze token input and generate an Abstract Syntax Tree for interpretation
class Parser {
public:
	Parser(std::vector<Token> tokenList) { this->tokenList = tokenList;  size = tokenList.size(); advance(); }

	// Generates an AST representation after parsing list of tokens
	Node *parseTokens() {
		return new Node(expr());
	}

	// Generates the next token in list
	bool advance() {
		tokenIndex++;
		if (tokenIndex < size) {
			currToken = tokenList[tokenIndex];
			return true;
		}
		else return false;
	}

	// Generates a factor (INT|FLOAT)
	Node *factor() {
		Token t = currToken;
		std::string tokenType = t.getTokenTypeToString();
		if (tokenType == "INT" || tokenType == "FLOAT") {
			advance();
			Node* node = new Node(t);
			return node;
		}
		Node* node = new Node(Token());
		return node;
	}
	// Generates a term FACTOR ((MUL|DIV) FACTOR)*
	Node *term() {
		Node *node = biOp(factor(), std::vector<std::string>{"MUL", "DIV"});
		return node;
	}
	// Generates an expression TERM ((PLUS|MINUS) TERM)*
	Node *expr() {
		Node* node = biOp(term(), std::vector<std::string>{"PLUS", "MINUS"});
		return node;
	}
	Node *biOp(Node *node, std::vector<std::string> ops) {
		Node *left = node;

		while (std::find(ops.begin(), ops.end(), currToken.getTokenTypeToString()) != ops.end()) {
			Token opToken = currToken;
			if (advance()) Node* right = node;
			left = new Node(left, opToken, nullptr);
		}
		return left;
	}
private:
	std::vector<Token> tokenList;
	int size;
	int tokenIndex = -1;
	Token currToken;
};

