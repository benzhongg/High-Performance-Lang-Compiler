#pragma once
#include "file_handling/file_reader.h"
#include "macro_resolver.h"
#include "source_code.h"
#include <map>
#include <string>

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
  HPLCPreprocessor();

  ~HPLCPreprocessor();

  void preprocess(SourceCode& source_code) override;
};