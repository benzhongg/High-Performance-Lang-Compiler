#pragma once
#include "lexer.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

class MacroResolverBase
{
public:
  virtual void resolve(std::string& source_code) = 0;
};

using MacroResolverVector = std::vector<MacroResolverBase*>;

class DefineMacroResolver : public MacroResolverBase
{
public:
  void resolve(std::string& source_code) override;

protected:
  std::vector<std::string> splitLines(const std::string& source_code);

  void addMacroToTable(std::string& source_code_line);

  void process(std::string& source_code_line);

  bool startsWithDefineMacro(std::string& source_code_line);

  bool containsStringLiteral(const std::string& source_code_line, size_t pos);

  size_t positionOfNextDoubleQuote(const std::string& source_code_line, size_t pos);

  void applyMacro(std::string& source_code_line);

private:
  std::unordered_map<std::string, std::string> m_macroTable {};
  friend class TestDefineMacroResolver;
};