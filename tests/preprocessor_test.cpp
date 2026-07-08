#include "HPLC/preprocessor.h"
#include <gtest/gtest.h>

TEST(PreprocessorModule, PreprocessingDefineMacroStringApproach) 
{
    std::string example_program = "#define hello 5\nint x = hello; \nint y = hello; \nstring s = \"hello world\"; \nint z = hello + hello;";
    PreprocessorBase* preprocessor {new HPLCPreprocessor};
    std::string processedOutputTest {preprocessor->preprocess(example_program)};
    ASSERT_EQ(processedOutputTest, "int x = 5; int y = 5; string s = \"5 world\"; int z = 5 + 5;");
}

TEST(PreprocessorModule, ApplyMacro)
{
    std::string example_program = 
        " #define hello 5\nstring s = \"abc hello world\";";
}