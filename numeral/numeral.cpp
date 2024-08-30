#include "numeral.h"

int main() {
	std::cout << "Numeral" << std::endl;
	while (true) {
		std::string input;
		std::cout << "@ ";
		std::getline(std::cin, input);
		std::vector<lexer::Token*> tokens = (new lexer::Lexer(input))->tokenize();
		if (tokens.size() == 0) continue;
		parser::Node* root = (new parser::Parser(tokens))->expr();
		root->print(0);
	}
	return 0;
}
