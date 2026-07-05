#pragma once
#include <string>

class MacroResolverBase
{
public:
  virtual std::string resolveMacros(std::string source_code) = 0;
};
