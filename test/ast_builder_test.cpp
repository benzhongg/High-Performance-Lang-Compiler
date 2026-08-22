#include "HPLC/ast_builder.h"
#include <gtest/gtest.h>

TEST(ASTBuilderTest, BuildsDeclarationsAndExpressions)
{
  SourceCode source {"example.hplc", "int answer = 1 + 2\nprint(answer)"};
  HPLCParser parser;
  ParseResult parsed = parser.parse(source);
  ASSERT_TRUE(parsed.diagnostics.empty());

  std::vector<Diagnostic> diagnostics;
  auto program = ASTBuilder {}.build(parsed, source, diagnostics);
  ASSERT_TRUE(diagnostics.empty());
  ASSERT_EQ(program->statements.size(), 2);

  auto declaration = std::dynamic_pointer_cast<VariableDeclNode>(program->statements[0]);
  ASSERT_NE(declaration, nullptr);
  EXPECT_EQ(declaration->name, "answer");
  EXPECT_EQ(declaration->variableType, VariableType::Int);
  EXPECT_EQ(declaration->span.line, 0);
  EXPECT_EQ(declaration->span.column, 0);

  auto expression = std::dynamic_pointer_cast<BinaryExprNode>(declaration->value);
  ASSERT_NE(expression, nullptr);
  EXPECT_EQ(expression->operatorType, OperatorType::Plus);
  EXPECT_EQ(expression->span.startByte, 13);
  EXPECT_EQ(expression->span.endByte, 18);
}

TEST(ASTBuilderTest, ReportsSyntaxErrorsWithSourceSpan)
{
  SourceCode source {"broken.hplc", "int ="};
  ParseResult parsed = HPLCParser {}.parse(source);
  ASSERT_FALSE(parsed.diagnostics.empty());
  EXPECT_EQ(parsed.diagnostics.front().span.fileName, "broken.hplc");
  EXPECT_EQ(parsed.diagnostics.front().span.line, 0);
}