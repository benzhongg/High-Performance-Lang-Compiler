#pragma once
#include "file_handling/file_reader.h"
#include "macro_resolver.h"
#include <map>
#include <string>
#include "source_code.h"

class PreprocessorBase
{
public:
  virtual void preprocess(SourceCode& input_source_code) = 0;
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

  //removed pass by val
  //turned return type to void
  //removed copy constructor of a result string in function def
  void preprocess(SourceCode& source_code) override
  {
    for (auto resolver : m_resolvers)
    {
      resolver->resolve(source_code.contents);
    }
  }
};