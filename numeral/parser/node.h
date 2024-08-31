#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "../lexer/token.h"

namespace parser {

    typedef enum {
        NONE,
        BINOP,
        UNARYOP,
        LITERAL,
        VARIABLE
    } node_t;

    class Node {
    public:
        node_t type = NONE;
        virtual void print(int indent) const = 0;
        virtual ~Node() = default;
    };

    class BinOpNode : public Node {
    public:
        std::shared_ptr<parser::Node> left, right;
        lexer::token_t operation;

        BinOpNode(std::shared_ptr<parser::Node> l, lexer::token_t op, std::shared_ptr<parser::Node> r)
            : left(l), operation(op), right(r) {
            type = BINOP;
        }

        void print(int indent) const override {
            for (int i = 0; i < indent; i++) std::cout << "--";
            std::cout << ' ' << operation << std::endl;
            left->print(indent + 1);
            right->print(indent + 1);
        }
    };

    class UnaryOpNode : public Node {
    public:
        std::shared_ptr<parser::Node> right;
        lexer::token_t operation;

        UnaryOpNode(lexer::token_t op, std::shared_ptr<parser::Node> r)
            : operation(op), right(r) {
            type = UNARYOP;
        }

        void print(int indent) const override {
            for (int i = 0; i < indent; i++) std::cout << "--";
            std::cout << ' ' << operation << std::endl;
            right->print(indent + 1);
        }
    };

    class LiteralNode : public Node {
    public:
        double value;

        LiteralNode(double v) : value(v) {
            type = LITERAL;
        }

        void print(int indent) const override {
            for (int i = 0; i < indent; i++) std::cout << "--";
            std::cout << ' ' << value << std::endl;
        }
    };

    class VariableNode : public Node {
    public:
        std::string name;

        VariableNode(const std::string& n) : name(n) {
            type = VARIABLE;
        }

        void print(int indent) const override {
            for (int i = 0; i < indent; i++) std::cout << "--";
            std::cout << ' ' << name << std::endl;
        }
    };

}
