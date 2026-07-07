#pragma once
#include "expression_node.h"
#include "lexer.h"

using SyntaxTree = ProgramNode;

class ParserBase
{
public:
  virtual SyntaxTree parse(TokenVector targetVector) = 0;
};