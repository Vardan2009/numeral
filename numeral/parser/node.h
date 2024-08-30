#pragma once
#include <string>
#include <iostream>

namespace parser {
	typedef enum {
		BINOP,
		LITERAL,
		VARIABLE
	} node_t;

	class Node {
	public:
		node_t type;
		virtual void print(int) = 0;
	};

	class BinOpNode : public Node {
	public:
		Node *left, *right;
		char operation;
		BinOpNode(Node *l, char op, Node *r) {
			left = l;
			operation = op;
			right = r;
			type = BINOP;
		}
		void print(int indent) {
			for (int i = 0; i < indent; i++) std::cout << "--";
			std::cout << ' ' << operation << std::endl;
			left->print(indent + 1);
			right->print(indent + 1);
		}
	};

	class LiteralNode : public Node {
	public:
		double value;
		LiteralNode(double v) {
			value = v;
			type = LITERAL;
		}
		void print(int indent) {
			for (int i = 0; i < indent; i++) std::cout << "--";
			std::cout << ' ' << value << std::endl;
		}
	};

	class VariableNode : public Node {
	public:
		std::string name;
		VariableNode(std::string n) {
			name = n;
		}
		void print(int indent) {
			for (int i = 0; i < indent; i++) std::cout << "--";
			std::cout << ' ' << name << std::endl;
		}
	};
}