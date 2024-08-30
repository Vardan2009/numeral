#include "lexer.h"

std::vector<std::shared_ptr<lexer::Token>> lexer::Lexer::tokenize() {
	std::vector <std::shared_ptr<lexer::Token>> result;
	for (ptr = src.c_str(); *ptr != '\0'; ++ptr) {
		if (isdigit(*ptr)) {
			std::string str_val;
			bool dotted = false;
			for (; *ptr != '\0' && (isdigit(*ptr) || (*ptr == '.' && !dotted)); ++ptr) {
				if (*ptr == '.') dotted = true;
				str_val += *ptr;
			}
			result.push_back(std::make_shared<Token>(NUMBER, std::stod(str_val.c_str())));
		} if (isalpha(*ptr)) {
			std::string str_val;
			for (; *ptr != '\0' && isalpha(*ptr); ++ptr) {
				str_val += *ptr;
			}
			result.push_back(std::make_shared<Token>(IDENTIFIER, str_val));
		} else if (*ptr == '+') {
			result.push_back(std::make_shared<Token>(PLUS, "+"));
		} else if (*ptr == '-') {
			result.push_back(std::make_shared<Token>(MINUS, "-"));
		} else if (*ptr == '*') {
			result.push_back(std::make_shared<Token>(MUL, "*"));
		} else if (*ptr == '/') {
			result.push_back(std::make_shared<Token>(DIV, "/"));
		} else if (*ptr == '^') {
			result.push_back(std::make_shared<Token>(CARET, "^"));
		} else if (*ptr == '(') {
			result.push_back(std::make_shared<Token>(LPAREN));
		} else if (*ptr == ')') {
			result.push_back(std::make_shared<Token>(RPAREN));
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
