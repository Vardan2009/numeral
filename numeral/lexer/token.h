#pragma once

namespace lexer {
	typedef enum {
		IDENTIFIER,
		NUMBER,
		RPAREN,
		LPAREN,
		PLUS,
		MINUS,
		DIV,
		MUL,
		CARET,
		ASSIGN
	} token_t;

	class Token {
	public:
		token_t type;
		double value = 0;
		std::string value_str;
		Token(token_t t, double v) {
			type = t;
			value = v;
		}
		Token(token_t t, std::string vs) {
			type = t;
			value_str = vs;
		}
		Token(token_t t) {
			type = t;
		}
	};
}