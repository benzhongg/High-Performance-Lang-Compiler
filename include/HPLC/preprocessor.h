#pragma once
#include "file_handling/file_reader.h"
#include "macro_resolver.h"
#include <map>
#include <string>

class PreprocessorBase
{
public:
  virtual std::string preprocess(std::string source_code) = 0;
  virtual TokenVector preprocessTokens(TokenVector source_code_tokens) = 0;
  virtual ~PreprocessorBase() {}
};

class HPLCPreprocessor : public PreprocessorBase

{
private:
  MacroResolverVector m_resolvers {};

public:
  HPLCPreprocessor() { m_resolvers.push_back(new DefineMacroResolverStringApproach()); }

  ~HPLCPreprocessor() { m_resolvers.clear(); }
  
  TokenVector preprocessTokens(TokenVector source_code_tokens) override {}


  std::string preprocess(std::string source_code) override
  {
    for (auto resolver : m_resolvers)
    {
      source_code = resolver->resolve(source_code);
    }

    return source_code;
  }
};

class HPLCPreprocessorToken : public PreprocessorBase
{
private:
  MacroResolverVector m_resolvers {};

public:
  HPLCPreprocessorToken() { m_resolvers.push_back(new DefineMacroResolverTokenApproach()); }

  std::string preprocess(std::string source_code) override {}

  TokenVector preprocessTokens(TokenVector source_code_tokens) override
  {
    TokenVector processedTokens {source_code_tokens};

    for (auto resolver : m_resolvers)
    {
      processedTokens = resolver->resolve(processedTokens);
    }

    return processedTokens;
  }
};