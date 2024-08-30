#include "numeral.h"
#include <memory> // for smart pointers

void processInput(const std::string& input) {
    // Create a lexer and tokenize the input
    lexer::Lexer lexer(input);
    std::vector<std::shared_ptr<lexer::Token>> tokens = lexer.tokenize();

    // If there are no tokens, do nothing
    if (tokens.empty()) return;

    // Create a parser and parse the expression
    parser::Parser parser(tokens);
    std::shared_ptr<parser::Node> root = parser.expr();

    // If parsing is successful, print the structure
    if (root) {
        root->print(0);
    }
    else {
        std::cerr << "Parsing failed!" << std::endl;
    }
}

int main() {
    std::cout << "Numeral" << std::endl;

    while (true) {
        std::string input;
        std::cout << "@ ";
        std::getline(std::cin, input);
        // Check for exit condition
        if (input == "exit") break;
        // Process the input
        processInput(input);
    }

    return EXIT_SUCCESS;
}
