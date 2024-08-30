#pragma once
#include <vector>
#include "node.h"
#include "../lexer/lexer.h"

namespace parser {
	class Parser {
	private:
		std::vector<lexer::Token*> tokens;
		int ptr = 0;
		lexer::Token* peek();
		lexer::Token* advance();
		void consume(lexer::token_t, std::string);
		void consume(lexer::token_t, double);
		void consume(lexer::token_t);
	public:
		Parser(std::vector<lexer::Token*> t) {
			tokens = t;
			ptr = 0;
		}
		Node* expr();
		Node* term();
		Node* factor();
	};
}