#pragma once
#include <memory>
#include "../parser/node.h"

namespace execution {
	class Interpreter {
	public:
		double node(std::shared_ptr<parser::Node> node);
		double binop_node(std::shared_ptr<parser::Node> node);
		double literal_node(std::shared_ptr<parser::Node> node);
		double variable_node(std::shared_ptr<parser::Node> node);
	};
}