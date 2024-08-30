#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "token.h"

namespace lexer {
	class Lexer {
		private:
			std::string src;
			const char* ptr;
		public:
			Lexer(std::string s) {
				src = s;
				ptr = s.c_str();
			}
			std::vector<Token*> tokenize();
	};
}