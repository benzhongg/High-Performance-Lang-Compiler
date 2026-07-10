#pragma once
#include "file_handling/file_reader.h"
#include "macro_resolver.h"
#include <map>
#include <string>
#include "source_code.h"

class PreprocessorBase
{
public:
  virtual SourceCode preprocess(SourceCode input_source_code) = 0;
  virtual ~PreprocessorBase() {}
};

class HPLCPreprocessor : public PreprocessorBase

{
private:
  MacroResolverVector m_resolvers {};

public:
  HPLCPreprocessor() 
  { 
    m_resolvers.push_back(new DefineMacroResolver()); 
  }

  ~HPLCPreprocessor() { m_resolvers.clear(); }

  SourceCode preprocess(SourceCode source_code) override
  {
    SourceCode result_source_code = source_code;

    for (auto resolver : m_resolvers)
    {
      result_source_code.contents = resolver->resolve(result_source_code.contents);
    }

    return result_source_code;
  }
};