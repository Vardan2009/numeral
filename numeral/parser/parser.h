#pragma once
#include <vector>
#include "node.h"
#include "../lexer/lexer.h"
#include "../lexer/token.h"

namespace parser {
	class Parser {
	private:
		std::vector<std::shared_ptr<lexer::Token>> tokens;
		int ptr = 0;
		std::shared_ptr<lexer::Token> peek();
		std::shared_ptr<lexer::Token> advance();
		void consume(lexer::token_t, const std::string);
		void consume(lexer::token_t, double);
		void consume(lexer::token_t);
	public:
		Parser(std::vector<std::shared_ptr<lexer::Token>> t) {
			tokens = t;
			ptr = 0;
		}
		std::shared_ptr<parser::Node> expr();
		std::shared_ptr<parser::Node> term();
		std::shared_ptr<parser::Node> factor();
	};
}