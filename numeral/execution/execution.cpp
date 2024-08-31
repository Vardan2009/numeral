#include "execution.h"

double execution::Interpreter::node(std::shared_ptr<parser::Node> node) {
	switch (node->type) {
	case parser::BINOP:
		return binop_node(node);
	case parser::UNARYOP:
		return unaryop_node(node);
	case parser::LITERAL:
		return literal_node(node);
	case parser::VARIABLE:
		return variable_node(node);
	default:
		throw std::runtime_error("Unknown node type!");
	}
}

double execution::Interpreter::unaryop_node(std::shared_ptr<parser::Node> baseptr) {
	std::shared_ptr<parser::UnaryOpNode> nodeptr = std::static_pointer_cast<parser::UnaryOpNode>(baseptr);
	switch (nodeptr->operation)
	{
	case lexer::PLUS:
		return +node(nodeptr->right);
	case lexer::MINUS:
		return -node(nodeptr->right);
	default:
		throw std::runtime_error("Invalid unary operator " + nodeptr->operation);
		break;
	}
}

double execution::Interpreter::binop_node(std::shared_ptr<parser::Node> baseptr) {
	std::shared_ptr<parser::BinOpNode> nodeptr = std::static_pointer_cast<parser::BinOpNode>(baseptr);
	switch (nodeptr->operation)
	{
	case lexer::PLUS :
		return node(nodeptr->left) + node(nodeptr->right);
	case lexer::MINUS:
		return node(nodeptr->left) - node(nodeptr->right);
	case lexer::MUL:
		return node(nodeptr->left) * node(nodeptr->right);
	case lexer::DIV:
		return node(nodeptr->left) / node(nodeptr->right);
	case lexer::CARET:
		return std::pow(node(nodeptr->left), node(nodeptr->right));
	case lexer::ASSIGN: {
		if (nodeptr->left->type != parser::VARIABLE)
			throw std::runtime_error("Lvalue of assignment should be identifier");

		std::string varname = (std::static_pointer_cast<parser::VariableNode>(nodeptr->left))->name;
		double result = node(nodeptr->right);
		variables[varname] = result;
		return result;
	}
	default:
		throw std::runtime_error("Invalid binary operator " + std::to_string(nodeptr->operation));
		break;
	}
}

double execution::Interpreter::literal_node(std::shared_ptr<parser::Node> baseptr) {
	std::shared_ptr<parser::LiteralNode> nodeptr = std::static_pointer_cast<parser::LiteralNode>(baseptr);
	return nodeptr->value;
}

double execution::Interpreter::variable_node(std::shared_ptr<parser::Node> nodeptr) {
	std::string varname = (std::static_pointer_cast<parser::VariableNode>(nodeptr))->name;
	return variables[varname];
}
