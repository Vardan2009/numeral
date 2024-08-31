#include "numeral.h"

void processInput(const std::string& input) {
    // Create a lexer and tokenize the input
    std::vector<std::shared_ptr<lexer::Token>> tokens;

    try {
        lexer::Lexer lexer(input);
        tokens = lexer.tokenize();
    } catch (std::runtime_error e) {
        std::cerr << "[lexer] " << e.what() << std::endl;
        return;
    }

    // If there are no tokens, do nothing
    if (tokens.empty()) return;

    // Create a parser and parse the expression
    std::shared_ptr<parser::Node> root = nullptr;
    try {
        parser::Parser parser(tokens);
        root = parser.expr();
    }
    catch (std::runtime_error e) {
        std::cerr << "[parser] " << e.what() << std::endl;
        return;
    }

    // Create an interpreter and execute the syntax tree
    try {
        execution::Interpreter interpreter;
        std::cout << interpreter.node(root) << std::endl;
    } catch (std::runtime_error e) {
        std::cerr << "[interpreter] " << e.what() << std::endl;
        return;
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
