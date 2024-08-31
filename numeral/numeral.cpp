#include "numeral.h"

// create an instance of the interpreter
// we need one instance to preserve the variables between each command
execution::Interpreter interpreter;

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

    /*
    for (std::shared_ptr<lexer::Token> t : tokens) {
        std::cout << "TOKEN(" << t->type << ", " << t->value << ", " << t->value_str << ")" << std::endl;
    }
    */

    // If there are no tokens, do nothing
    if (tokens.empty()) return;

    // Create a parser and parse the expression
    std::shared_ptr<parser::Node> root = nullptr;
    try {
        parser::Parser parser(tokens);
        root = parser.expr();
        root->print(0);
    }
    catch (std::runtime_error e) {
        std::cerr << "[parser] " << e.what() << std::endl;
        return;
    }

    // execute the syntax tree using the instance of the interpreter created at the beginning
    try {
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
