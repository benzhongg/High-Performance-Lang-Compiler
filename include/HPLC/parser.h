#pragma once

#include "ast_node.h"
#include <memory>
#include <string>
#include <vector>

extern "C" {
#include <tree_sitter/api.h>
}

struct Diagnostic
{
  std::string message;
  SourceSpan span;
};

struct ParseResult
{
  std::shared_ptr<TSTree> tree;
  std::vector<Diagnostic> diagnostics;
  bool hasErrors() const { return !diagnostics.empty(); }
};

class HPLCParser
{
public:
  ParseResult parse(const SourceCode& sourceCode) const;
};
