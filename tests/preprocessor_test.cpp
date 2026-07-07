#include "HPLC/preprocessor.h"
#include <gtest/gtest.h>

TEST(PreprocessorModule, separatingInputFileLineByLine) 
{
    std::ios_base::sync_with_stdio(false);
    std::string example_program = "#define hello 5\nint x = hello;";
    PreprocessorBase* preprocessor {new HPLCPreprocessor};
    std::string processedOutputTest {preprocessor->preprocess(example_program)};
    std::cout << processedOutputTest << std::endl;
    // ASSERT_EQ(processedOutputTest, "int x = 5;");
}