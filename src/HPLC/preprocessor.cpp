#include "HPLC/preprocessor.h"

HPLCPreprocessor::HPLCPreprocessor() { m_resolvers.push_back(new DefineMacroResolver()); }

HPLCPreprocessor::~HPLCPreprocessor() { m_resolvers.clear(); }

void HPLCPreprocessor::preprocess(SourceCode& source_code)
{
  for (auto resolver : m_resolvers)
  {
    resolver->resolve(source_code.contents);
  }
}