#include "execution.h"

double execution::Interpreter::node(std::shared_ptr<parser::Node> node) {
	switch (node->type) {
	case parser::BINOP:
		return binop_node(node);
	case parser::LITERAL:
		return literal_node(node);
	case parser::VARIABLE:
		return variable_node(node);
	default:
		throw std::runtime_error("Unknown node type!");
	}
}

double execution::Interpreter::binop_node(std::shared_ptr<parser::Node> baseptr) {
	std::shared_ptr<parser::BinOpNode> nodeptr = std::static_pointer_cast<parser::BinOpNode>(baseptr);
	switch (nodeptr->operation)
	{
	case '+':
		return node(nodeptr->left) + node(nodeptr->right);
	case '-':
		return node(nodeptr->left) - node(nodeptr->right);
	case '*':
		return node(nodeptr->left) * node(nodeptr->right);
	case '/':
		return node(nodeptr->left) / node(nodeptr->right);
	case '^':
		return std::pow(node(nodeptr->left), node(nodeptr->right));
	default:
		break;
	}
}

double execution::Interpreter::literal_node(std::shared_ptr<parser::Node> baseptr) {
	std::shared_ptr<parser::LiteralNode> nodeptr = std::static_pointer_cast<parser::LiteralNode>(baseptr);
	return nodeptr->value;
}

double execution::Interpreter::variable_node(std::shared_ptr<parser::Node> node) {
	throw std::runtime_error("variable undefined!");
}
