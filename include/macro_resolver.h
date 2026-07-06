#pragma once
#include <string>
#include <vector>
class MacroResolverBase
{
public:
  virtual std::string resolve(std::string source_code) = 0;
};

using MacroResolverVector = std::vector<MacroResolverBase*>;

class DefineMacroResolver : public MacroResolverBase
{
public:
  std::string resolve(std::string source_code) override
  {
  }
};



