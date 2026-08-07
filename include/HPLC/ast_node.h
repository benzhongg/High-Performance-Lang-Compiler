#pragma once
#include "lexer.h"

enum NodeType
{
    Unknown,
    VariableDecl

};

struct ASTBase
{
    NodeType nodeType { NodeType::Unknown };
    FileName fileName { ""};
    int line { 0 };
    int col { 0 };
};

struct VariableDeclNode : public ASTBase
{
    VariableType varType = int;
    Operand targetOperand = a;
    TargetValue targetValue = 5;
};


enum OperatorType
{

};

struct NodeBase
{
};

struct ProgramNode : public NodeBase
{
};

struct ExpressionNode : public NodeBase
{
};

struct PrefixExpression : public ExpressionNode // ++x;
{
    OperatorType operatorType;
    Operator operator;
};

struct PostFixExpression : public ExpressionNode // x++;
{

};

struct AddressOfNode : public ExpressionNode
{
    OperatorType operatorType
};

struct DereferenceNode : public ExpressionNode
{
};

struct SizeOfNode : public ExpressionNode
{
};