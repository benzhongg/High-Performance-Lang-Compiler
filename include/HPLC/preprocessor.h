#pragma once
#include "file_handling/file_reader.h"
#include "macro_resolver.h"
#include <map>
#include <string>

class PreprocessorBase
{
public:
  virtual std::string preprocess(std::string source_code) = 0;
  virtual ~PreprocessorBase() {}
};

class HPLCPreprocessor : public PreprocessorBase
{
private:
  MacroResolverVector m_resolvers 
  {};

public:
  HPLCPreprocessor()
  {
    m_resolvers.push_back(new DefineMacroResolverStringApproach());
  }

  ~HPLCPreprocessor() { m_resolvers.clear(); }

  std::string preprocess(std::string source_code) override
  {
    for (auto resolver : m_resolvers)
    {
      source_code = resolver->resolve(source_code);
    }

    return source_code;
  }
};