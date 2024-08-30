#include "parser.h"

parser::Node* parser::Parser::expr() {
	Node* node = term();

	while (ptr < tokens.size() && (peek()->type == lexer::PLUS || peek()->type == lexer::MINUS)) {
		lexer::Token* op = advance();
		Node* right = term();
		node = new BinOpNode(node, op->value_str[0], right);
	}

	return node;
}

parser::Node* parser::Parser::term() {
	Node* node = factor();

	while (ptr < tokens.size() && (peek()->type == lexer::MUL || peek()->type == lexer::DIV || peek()->type == lexer::CARET)) {
		lexer::Token* op = advance();
		Node* right = term();
		node = new BinOpNode(node, op->value_str[0], right);
	}
	return node;
}

parser::Node* parser::Parser::factor() {
	lexer::Token* t = peek();
	switch (t->type)
	{
	case lexer::NUMBER:
		advance();
		return new LiteralNode(t->value);
	case lexer::IDENTIFIER:
		advance();
		return new VariableNode(t->value_str);
	case lexer::LPAREN:
		consume(lexer::LPAREN);
		Node* node = expr();
		consume(lexer::RPAREN);
		return node;
	}
	std::cerr << "Invalid factor" << std::endl;
	exit(1);
}

lexer::Token* parser::Parser::peek() {
	if (ptr >= tokens.size()) {
		std::cerr << "Unexpected end of input" << std::endl;
		exit(1);
	}
	return tokens[ptr];
}

lexer::Token* parser::Parser::advance() {
	return tokens[ptr++];
}

void parser::Parser::consume(lexer::token_t t, std::string v) {
	if (peek()->type == t && peek()->value_str == v) advance();
	else {
		std::cerr << "Unexpected token, expected " << v << std::endl;
		exit(1);
	}
}

void parser::Parser::consume(lexer::token_t t, double v) {
	if (peek()->type == t && peek()->value == v) advance();
	else {
		std::cerr << "Unexpected token, expected " << v << std::endl;
		exit(1);
	}
}

void parser::Parser::consume(lexer::token_t t) {
	if (peek()->type == t) advance();
	else {
		std::cerr << "Unexpected token, expected " << t << std::endl;
		exit(1);
	}
}