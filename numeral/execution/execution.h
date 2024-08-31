#pragma once
#include <memory>
#include <map>
#include "../parser/node.h"
#include "../lexer/token.h"

namespace execution {
	class Interpreter {
	private:
		std::map<std::string, double> variables;
	public:
		double node(std::shared_ptr<parser::Node> node);
		double unaryop_node(std::shared_ptr<parser::Node> baseptr);
		double binop_node(std::shared_ptr<parser::Node> node);
		double literal_node(std::shared_ptr<parser::Node> node);
		double variable_node(std::shared_ptr<parser::Node> node);
	};
}