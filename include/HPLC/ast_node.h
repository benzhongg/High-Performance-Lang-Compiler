#pragma once
#include "lexer.h"
#include <memory>

enum class NodeType
{
  Unknown,
  // program structure
  Program,
  DefineStmt,
  VariableDecl,
  // Expressions
  BinaryExpr,
  IdentifierExpr,
  LiteralExpr,
};

enum class OperatorType
{
  Assign,
  Plus,
  Minus,
  Multiply,
  Divide
};

enum class VariableType
{
  Unknown,
  Int,
  String
};

struct ASTBase
{
  NodeType nodeType {NodeType::Unknown};
  FileName fileName;
  int      line {0};
  int      col {0};
};

struct ExpressionNode : ASTBase
{
};

struct ProgramNode : ASTBase
{
  using ASTNodeVector = std::vector<std::shared_ptr<ASTBase>>;
  ASTNodeVector astVector;

  ProgramNode(ASTNodeVector astVector_input, FileName fileName_input) : astVector(astVector_input)
  {
    nodeType = NodeType::Program;
    fileName = fileName_input;
    line     = 0;
    col      = 0;
  };
};

struct VariableDeclNode : ASTBase
{
  using TargetValue = std::shared_ptr<ExpressionNode>;
  using Operand     = std::string;

  VariableType varType;
  Operand      targetOperand;
  TargetValue  targetExpr;

  VariableDeclNode(VariableType varType_input, Operand operand_input, TargetValue expr_input, int line_input,
                   int col_input, FileName fileName_input)
  {
    nodeType      = NodeType::VariableDecl;
    varType       = varType_input;
    targetOperand = operand_input;
    targetExpr    = expr_input;
    line          = line_input;
    col           = col_input;
    fileName      = fileName_input;
  }
};

struct BinaryExprNode : ExpressionNode
{
  using TargetValue = std::shared_ptr<ExpressionNode>;
  TargetValue  tValue1;
  OperatorType opType;
  TargetValue  tValue2;

  BinaryExprNode(TargetValue expr1_input, OperatorType opType_input, TargetValue expr2_input, int line_input,
                 int col_input, FileName fileName_input)
  {
    nodeType = NodeType::BinaryExpr;
    tValue1  = expr1_input;
    opType   = opType_input;
    tValue2  = expr2_input;
    line     = line_input;
    col      = col_input;
    fileName = fileName_input;
  };
};
struct IdentifierExprNode : ExpressionNode
{
  std::string rawIdentifier;
  IdentifierExprNode(std::string identifier_input, int line_input, int col_input, FileName fileName_input)
  {
    nodeType      = NodeType::IdentifierExpr;
    line          = line_input;
    col           = col_input;
    fileName      = fileName_input;
    rawIdentifier = identifier_input;
  };
};
struct LiteralExprNode : ExpressionNode
{
  std::string rawLiteral;
  LiteralExprNode(std::string rawLiteral_input, int line_input, int col_input, FileName fileName_input)
  {
    nodeType   = NodeType::LiteralExpr;
    line       = line_input;
    col        = col_input;
    fileName   = fileName_input;
    rawLiteral = rawLiteral_input;
  };
};