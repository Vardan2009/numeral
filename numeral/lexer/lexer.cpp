#include "lexer.h"

std::vector<lexer::Token*> lexer::Lexer::tokenize() {
	std::vector <lexer::Token*> result;
	for (ptr = src.c_str(); *ptr != '\0'; ++ptr) {
		if (isdigit(*ptr)) {
			std::string str_val;
			bool dotted = false;
			for (; *ptr != '\0' && (isdigit(*ptr) || (*ptr == '.' && !dotted)); ++ptr) {
				if (*ptr == '.') dotted = true;
				str_val += *ptr;
			}
			result.push_back(new Token(NUMBER, std::stod(str_val.c_str())));
		} if (isalpha(*ptr)) {
			std::string str_val;
			for (; *ptr != '\0' && isalpha(*ptr); ++ptr) {
				str_val += *ptr;
			}
			result.push_back(new Token(IDENTIFIER, str_val));
		} else if (*ptr == '+') {
			result.push_back(new Token(PLUS, "+"));
		} else if (*ptr == '-') {
			result.push_back(new Token(MINUS, "-"));
		} else if (*ptr == '*') {
			result.push_back(new Token(MUL, "*"));
		} else if (*ptr == '/') {
			result.push_back(new Token(DIV, "/"));
		} else if (*ptr == '^') {
			result.push_back(new Token(CARET, "^"));
		} else if (*ptr == '(') {
			result.push_back(new Token(LPAREN));
		} else if (*ptr == ')') {
			result.push_back(new Token(RPAREN));
		} else if (isspace(*ptr)) {
			// ignore whitespace
		} else if (*ptr == '\0') break;
		else {
			std::cerr << "Invalid character -> `" << (int)(*ptr) << "` at" << ptr - src.c_str() << std::endl;
			exit(1);
		}
	}
	return result;
}
