#include "HPLC/preprocessor.h"
#include <gtest/gtest.h>

TEST(PreprocessorModule, PreprocessingDefineMacroStringApproach) 
{
    std::string example_program = "#define hello 5\nint x = hello; \nint y = hello; \nstring s = \"hello world\"; \nint z = hello + hello;";
    PreprocessorBase* preprocessor {new HPLCPreprocessor};
    std::string processedOutputTest {preprocessor->preprocess(example_program)};
    ASSERT_EQ(processedOutputTest, "int x = 5; int y = 5; string s = \"5 world\"; int z = 5 + 5;");
}

TEST(PreprocessorModule, PreprocessingDefineMacroTokenApproach)
{
    Token token1 {TokenType:: DefineMacro, "#define", 0 , 0, "helloworld.hplc"};
    Token token2 {TokenType:: Identifier, "hello", 0 , 0, "helloworld.hplc"};
    Token token3 {TokenType:: Number, "5", 0 , 0, "helloworld.hplc"};
    Token tokenNL {TokenType:: NewLine, "\n", 0, 0, "helloworld.hplc"};
    Token token4 {TokenType:: KeywordInt, "int", 0 , 0, "helloworld.hplc"};
    Token token5 {TokenType:: Identifier, "x", 0 , 0, "helloworld.hplc"};
    Token token6 {TokenType:: Identifier, "hello", 0 , 0, "helloworld.hplc"};
    Token token7 {TokenType:: KeywordString, "string", 0, 0, "helloworld.hplc"};
    // this impl still allows macro identifiers and true identifiers to pass through, need to think of error handling in this case
    Token token8 {TokenType:: Identifier, "abc", 0, 0, "helloworld.hplc"};
    Token token9 {TokenType:: String, "hello", 0, 0, "helloworld.hplc"};

    TokenVector example_source_code_tokens {token1, token2, token3, tokenNL, token4, token5, token6, tokenNL, token7, token8, token9, tokenNL};

    PreprocessorBase* preprocessor {new HPLCPreprocessorToken};

    example_source_code_tokens = preprocessor->preprocessTokens(example_source_code_tokens);

    TokenVector expected_output {token4, token5, token3, tokenNL, token7, token8, token9, tokenNL};

    ASSERT_EQ(example_source_code_tokens, expected_output);
}