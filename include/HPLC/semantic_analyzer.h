#pragma once
#include "ast_node.h"

class SemanticAnalyzerBase
{
public:
  virtual std::shared_ptr<ProgramNode> analyze(std::shared_ptr<ProgramNode> targetAST) = 0;
};
