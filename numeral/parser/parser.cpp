#include "parser.h"

std::shared_ptr<parser::Node> parser::Parser::expr() {
    std::shared_ptr<parser::Node> node = term();

    // Handle addition and subtraction
    while (ptr < tokens.size() && (peek()->type == lexer::PLUS || peek()->type == lexer::MINUS)) {
        std::shared_ptr<lexer::Token> op = advance();  // Move token ownership for op
        std::shared_ptr<parser::Node> right = term();  // Parse the right side
        node = std::make_shared<BinOpNode>(node, op->type, right);
    }

    return node;
}

std::shared_ptr<parser::Node> parser::Parser::term() {
    std::shared_ptr<parser::Node> node = factor();  // Start by parsing a factor
    
    // Handle multiplication, division, exponentiation
    while (ptr < tokens.size() && (peek()->type == lexer::MUL || peek()->type == lexer::DIV || peek()->type == lexer::CARET || peek()->type == lexer::ASSIGN || peek()->type == lexer::LPAREN)) {
        if (peek()->type == lexer::LPAREN) { // if the next token is a left parenthasis (for multipliations like 5(2 + 3) or (1 + 1)(2 + 2))
            std::shared_ptr<parser::Node> right = factor(); // get the right side (which is a factor)
            node = std::make_shared<BinOpNode>(node, lexer::MUL, right); // create a multiplication node
        } else {
            std::shared_ptr<lexer::Token> op = advance(); // get the operator token
            std::shared_ptr<parser::Node> right = op->type == lexer::ASSIGN ? expr() : factor();  // Parse the right side as a factor
            node = std::make_shared<BinOpNode>(node, op->type, right); // create a node with its operation and sides
        }
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
    case lexer::PLUS:
    case lexer::MINUS:
        advance(); // Move to next token
        return std::make_shared<UnaryOpNode>(t->type, factor()); // create a unary operator with the operator and the factor after it
    case lexer::LPAREN:
        consume(lexer::LPAREN);  // Consume the '(' token
        std::shared_ptr<parser::Node> node = expr();  // Parse inner expression
        consume(lexer::RPAREN);  // Consume the ')' token
        return node;  // Return the expression node
    }

    // If no valid token was found, output error and terminate
    throw std::runtime_error("Invalid factor");
}

// return current token
std::shared_ptr<lexer::Token> parser::Parser::peek() {
    if (ptr >= tokens.size()) {
        throw std::runtime_error("Unexpected end of input");
    }
    return tokens[ptr];
}

// return current token and advance
std::shared_ptr<lexer::Token> parser::Parser::advance() {
    if (ptr >= tokens.size()) {
        throw std::runtime_error("Unexpected end of input");
    }
    return tokens[ptr++];
}

// these 3 functions are for expected tokens
// basically check the token, and if it's the expected one, advance, else throw an error

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
