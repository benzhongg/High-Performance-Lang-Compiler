#include "HPLC/ast_builder.h"

#include <cstring>
#include <stdexcept>

namespace
{
SourceSpan spanFor(TSNode node, const SourceCode& sourceCode)
{
  const TSPoint start = ts_node_start_point(node);
  const TSPoint end = ts_node_end_point(node);
  return {sourceCode.name, ts_node_start_byte(node), ts_node_end_byte(node), start.row, start.column, end.row, end.column};
}

std::string textFor(TSNode node, const SourceCode& sourceCode)
{
  if (ts_node_is_null(node))
    throw std::runtime_error("missing syntax node");
  return sourceCode.contents.substr(ts_node_start_byte(node), ts_node_end_byte(node) - ts_node_start_byte(node));
}

TSNode field(TSNode node, const char* name)
{
  return ts_node_child_by_field_name(node, name, static_cast<uint32_t>(std::strlen(name)));
}

std::shared_ptr<ExpressionNode> buildExpression(TSNode node, const SourceCode& sourceCode)
{
  const std::string type = ts_node_type(node);
  if (type == "identifier")
  {
    auto result = std::make_shared<IdentifierExprNode>();
    result->nodeType = NodeType::IdentifierExpr;
    result->span = spanFor(node, sourceCode);
    result->name = textFor(node, sourceCode);
    return result;
  }
  if (type == "number_literal" || type == "string_literal")
  {
    auto result = std::make_shared<LiteralExprNode>();
    result->nodeType = NodeType::LiteralExpr;
    result->span = spanFor(node, sourceCode);
    result->value = textFor(node, sourceCode);
    result->isString = type == "string_literal";
    if (result->isString && result->value.size() >= 2)
      result->value = result->value.substr(1, result->value.size() - 2);
    return result;
  }
  if (type == "binary_expression")
  {
    auto result = std::make_shared<BinaryExprNode>();
    result->nodeType = NodeType::BinaryExpr;
    result->span = spanFor(node, sourceCode);
    result->left = buildExpression(field(node, "left"), sourceCode);
    result->right = buildExpression(field(node, "right"), sourceCode);
    const std::string op = textFor(field(node, "operator"), sourceCode);
    result->operatorType = op == "+" ? OperatorType::Plus : op == "-" ? OperatorType::Minus
                                                                      : op == "*" ? OperatorType::Multiply
                                                                                  : OperatorType::Divide;
    return result;
  }
  throw std::runtime_error("unsupported expression node: " + type);
}
}

std::shared_ptr<ProgramNode> ASTBuilder::build(const ParseResult& parseResult, const SourceCode& sourceCode,
                                               std::vector<Diagnostic>& diagnostics) const
{
  auto program = std::make_shared<ProgramNode>();
  program->nodeType = NodeType::Program;
  TSNode root = ts_tree_root_node(parseResult.tree.get());
  program->span = spanFor(root, sourceCode);

  for (uint32_t index = 0; index < ts_node_child_count(root); ++index)
  {
    TSNode node = ts_node_child(root, index);
    const std::string type = ts_node_type(node);
    try
    {
      if (type == "assignment")
      {
        auto declaration = std::make_shared<VariableDeclNode>();
        declaration->nodeType = NodeType::VariableDecl;
        declaration->span = spanFor(node, sourceCode);
        declaration->variableType = textFor(field(node, "type"), sourceCode) == "int" ? VariableType::Int : VariableType::String;
        declaration->name = textFor(field(node, "operand"), sourceCode);
        declaration->value = buildExpression(field(node, "value"), sourceCode);
        program->statements.push_back(declaration);
      }
      else if (type == "print")
      {
        auto print = std::make_shared<PrintNode>();
        print->nodeType = NodeType::Print;
        print->span = spanFor(node, sourceCode);
        print->argument = buildExpression(field(node, "argument"), sourceCode);
        program->statements.push_back(print);
      }
      else if (type == "preprocessor")
      {
        auto define = std::make_shared<DefineNode>();
        define->nodeType = NodeType::Define;
        define->span = spanFor(node, sourceCode);
        define->name = textFor(field(node, "macro"), sourceCode);
        define->value = textFor(field(node, "value"), sourceCode);
        program->statements.push_back(define);
      }
      else
        diagnostics.push_back({"unsupported syntax node: " + type, spanFor(node, sourceCode)});
    }
    catch (const std::exception& error)
    {
      diagnostics.push_back({error.what(), spanFor(node, sourceCode)});
    }
  }
  return program;
}
