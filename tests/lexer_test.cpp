#include <gtest/gtest.h>
#include "HPLC/lexer.h"

TEST(LexerModule, TokenizeMethod) 
{
    std::string program_string {"int x = 5 \n int y = 10 \n"};
    TokenVector result_vector {};
    HPLCLexer test_lexer(program_string);
    result_vector = test_lexer.tokenize();
    SUCCEED();
}
