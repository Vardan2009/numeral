add_executable (numeral "numeral.cpp" "numeral.h" "lexer/lexer.cpp" "lexer/lexer.h" "lexer/token.h" "parser/node.h" "parser/parser.h" "parser/parser.cpp" "execution/execution.h" "execution/execution.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET numeral PROPERTY CXX_STANDARD 20)
endif()