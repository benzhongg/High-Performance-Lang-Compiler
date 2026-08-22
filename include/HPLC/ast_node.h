#pragma once

#include "source_code.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

enum class NodeType { Program, VariableDecl, Define, Print, BinaryExpr, IdentifierExpr, LiteralExpr };
enum class OperatorType { Plus, Minus, Multiply, Divide };
enum class VariableType { Int, String };

struct SourceSpan
{
  FileName fileName;
  uint32_t startByte {0};
  uint32_t endByte {0};
  uint32_t line {0};
  uint32_t column {0};
  uint32_t endLine {0};
  uint32_t endColumn {0};
};

struct ASTVisitor;
struct ASTNode
{
  NodeType nodeType;
  SourceSpan span;
  virtual ~ASTNode() = default;
  virtual void accept(ASTVisitor& visitor) = 0;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

struct ProgramNode;
struct VariableDeclNode;
struct DefineNode;
struct PrintNode;
struct BinaryExprNode;
struct IdentifierExprNode;
struct LiteralExprNode;

struct ASTVisitor
{
  virtual ~ASTVisitor() = default;
  virtual void visit(ProgramNode&) = 0;
  virtual void visit(VariableDeclNode&) = 0;
  virtual void visit(DefineNode&) = 0;
  virtual void visit(PrintNode&) = 0;
  virtual void visit(BinaryExprNode&) = 0;
  virtual void visit(IdentifierExprNode&) = 0;
  virtual void visit(LiteralExprNode&) = 0;
};

struct ExpressionNode : ASTNode {};

struct ProgramNode final : ASTNode
{
  std::vector<ASTNodePtr> statements;
  void accept(ASTVisitor& visitor) override { visitor.visit(*this); }
};

struct VariableDeclNode final : ASTNode
{
  VariableType variableType;
  std::string name;
  std::shared_ptr<ExpressionNode> value;
  void accept(ASTVisitor& visitor) override { visitor.visit(*this); }
};

struct DefineNode final : ASTNode
{
  std::string name;
  std::string value;
  void accept(ASTVisitor& visitor) override { visitor.visit(*this); }
};

struct PrintNode final : ASTNode
{
  std::shared_ptr<ExpressionNode> argument;
  void accept(ASTVisitor& visitor) override { visitor.visit(*this); }
};

struct BinaryExprNode final : ExpressionNode
{
  std::shared_ptr<ExpressionNode> left;
  OperatorType operatorType;
  std::shared_ptr<ExpressionNode> right;
  void accept(ASTVisitor& visitor) override { visitor.visit(*this); }
};

struct IdentifierExprNode final : ExpressionNode
{
  std::string name;
  void accept(ASTVisitor& visitor) override { visitor.visit(*this); }
};

struct LiteralExprNode final : ExpressionNode
{
  std::string value;
  bool isString {false};
  void accept(ASTVisitor& visitor) override { visitor.visit(*this); }
};
