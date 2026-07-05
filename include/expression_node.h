#pragma once
#include "lexer.h"

enum NodeType
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

struct PreFixExpression : public ExpressionNode
{
};

struct PostFixExpression : public ExpressionNode
{
};

struct AddressOfNode : public ExpressionNode
{
};

struct DereferenceNode : public ExpressionNode
{
};

struct SizeOfNode : public ExpressionNode
{
};
