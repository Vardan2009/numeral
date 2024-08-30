#pragma once
#include <string>
#include <iostream>
#include <memory>

namespace parser {

    typedef enum {
        BINOP,
        LITERAL,
        VARIABLE
    } node_t;

    class Node {
    public:
        node_t type;
        virtual void print(int indent) const = 0;
        virtual ~Node() = default;
    };

    class BinOpNode : public Node {
    public:
        std::shared_ptr<parser::Node> left, right;
        char operation;

        BinOpNode(std::shared_ptr<parser::Node> l, char op, std::shared_ptr<parser::Node> r)
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
