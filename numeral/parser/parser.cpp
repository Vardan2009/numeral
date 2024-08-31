#include "parser.h"

std::shared_ptr<parser::Node> parser::Parser::expr() {
    std::shared_ptr<parser::Node> node = term();

    // Handle addition and subtraction
    while (ptr < tokens.size() && (peek()->type == lexer::PLUS || peek()->type == lexer::MINUS)) {
        std::shared_ptr<lexer::Token> op = advance();  // Move token ownership for op
        std::shared_ptr<parser::Node> right = term();  // Parse the right side
        node = std::make_shared<BinOpNode>(node, op->value_str[0], right);
    }

    return node;
}

std::shared_ptr<parser::Node> parser::Parser::term() {
    std::shared_ptr<parser::Node> node = factor();  // Start by parsing a factor

    // Handle multiplication, division, and exponentiation
    while (ptr < tokens.size() && (peek()->type == lexer::MUL || peek()->type == lexer::DIV || peek()->type == lexer::CARET)) {
        std::shared_ptr<lexer::Token> op = advance();  // Move token ownership for op
        std::shared_ptr<parser::Node> right = factor();  // Parse the right side as a factor
        node = std::make_shared<BinOpNode>(node, op->value_str[0], right);
    }

    return node;
}

std::shared_ptr<parser::Node> parser::Parser::factor() {
    std::shared_ptr<lexer::Token> t = peek();  // Peek at the current token (no ownership transfer)

    switch (t->type) {
    case lexer::NUMBER:
        advance();  // Move to next token
        return std::make_shared<LiteralNode>(t->value);  // Return a literal node with value
    case lexer::IDENTIFIER:
        advance();  // Move to next token
        return std::make_shared<VariableNode>(t->value_str);  // Return a variable node
    case lexer::LPAREN:
        consume(lexer::LPAREN);  // Consume the '(' token
        std::shared_ptr<parser::Node> node = expr();  // Parse inner expression
        consume(lexer::RPAREN);  // Consume the ')' token
        return node;  // Return the expression node
    }

    // If no valid token was found, output error and terminate
    throw std::runtime_error("Invalid factor");
}

std::shared_ptr<lexer::Token> parser::Parser::peek() {
    if (ptr >= tokens.size()) {
        throw std::runtime_error("Unexpected end of input");
    }
    return tokens[ptr];
}

std::shared_ptr<lexer::Token> parser::Parser::advance() {
    if (ptr >= tokens.size()) {
        throw std::runtime_error("Unexpected end of input");
    }
    return tokens[ptr++];
}

void parser::Parser::consume(lexer::token_t t, const std::string v) {
    std::shared_ptr<lexer::Token> token = peek();  // Peek at current token without moving it
    if (token->type == t && token->value_str == v) {
        advance();  // Consume the token if it matches
    }
    else {
        throw std::runtime_error("Unexpected token, expected " + v);
    }
}

void parser::Parser::consume(lexer::token_t t, double v) {
    std::shared_ptr<lexer::Token> token = peek();  // Peek at current token without moving it
    if (token->type == t && token->value == v) {
        advance();  // Consume the token if it matches
    }
    else {
        throw std::runtime_error("Unexpected token, expected " + std::to_string(v));
    }
}

void parser::Parser::consume(lexer::token_t t) {
    std::shared_ptr<lexer::Token> token = peek();  // Peek at current token without moving it
    if (token->type == t) {
        advance();  // Consume the token if it matches
    }
    else {
        throw std::runtime_error("Unexpected token, expected type " + std::to_string(t));
    }
}
