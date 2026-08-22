#pragma once

#include "ast_node.h"
#include "parser.h"

class ASTBuilder
{
public:
  std::shared_ptr<ProgramNode> build(const ParseResult& parseResult, const SourceCode& sourceCode,
                                     std::vector<Diagnostic>& diagnostics) const;
};
