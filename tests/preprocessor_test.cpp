#include "HPLC/macro_resolver.h"
#include "HPLC/preprocessor.h"
#include <gtest/gtest.h>

TEST(PreprocessorModule, PreprocessingDefineMacro)
{
  std::string example_program =
      "#define hello 5\nint x = hello; \nint y = hello; \nstring s = \"hello world\"; \nint z = hello + hello;";
  PreprocessorBase* preprocessor {new HPLCPreprocessor};
  std::string       processedOutputTest {preprocessor->preprocess(example_program)};
  ASSERT_EQ(processedOutputTest, "int x = 5; int y = 5; string s = \"hello world\"; int z = 5 + 5;");
}

class TestDefineMacroResolver : public DefineMacroResolver
{
public:
  void addMacro(std::string macro_identifier, std::string macro_value) { m_macroTable[macro_identifier] = macro_value; }

  bool testApplyMacro(std::string source_code_line, std::string expected_output)
  {
    return this->applyMacro(source_code_line) == expected_output;
  }
};

TEST(PreprocessorModule, ApplyMacroDefine)
{
  TestDefineMacroResolver test_resolver;
  test_resolver.addMacro("hello", "5");

  std::string test_string_1            = "string s = \"hello world\"";
  std::string expected_output_string_1 = "string s = \"hello world\"";
  ASSERT_EQ(test_resolver.testApplyMacro(test_string_1, expected_output_string_1), true);

  std::string test_string_2            = "string s = \"hello world hello\"";
  std::string expected_output_string_2 = "string s = \"hello world hello\"";
  ASSERT_EQ(test_resolver.testApplyMacro(test_string_2, expected_output_string_2), true);

  std::string test_string_3            = "int y = hello + hello";
  std::string expected_output_string_3 = "int y = 5 + 5";
  ASSERT_EQ(test_resolver.testApplyMacro(test_string_3, expected_output_string_3), true);

  std::string test_string_4            = "int x = hello + \"hello\"";
  std::string expected_output_string_4 = "int x = 5 + \"hello\"";
  ASSERT_EQ(test_resolver.testApplyMacro(test_string_4, expected_output_string_4), true);

  std::string test_string_5            = "int x = hello + \"hello\" + hello";
  std::string expected_output_string_5 = "int x = 5 + \"hello\" + 5";
  ASSERT_EQ(test_resolver.testApplyMacro(test_string_5, expected_output_string_5), true);

  std::string test_string_6            = "int x = \"hello\" + \"hello\"";
  std::string expected_output_string_6 = "int x = \"hello\" + \"hello\"";
  ASSERT_EQ(test_resolver.testApplyMacro(test_string_6, expected_output_string_6), true);

  std::string test_string_7            = "int x = \"hello\" + hello + \"hello\"";
  std::string expected_output_string_7 = "int x = \"hello\" + 5 + \"hello\"";
  ASSERT_EQ(test_resolver.testApplyMacro(test_string_7, expected_output_string_7), true);
}