#pragma once
#include "HPLC/source_code.h"
#include "HPLC/token.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

using word = std::string;

class LexerBase
{
public:
  // const word ref since we're only reading the input
  virtual TokenVector tokenize(const SourceCode& input_source_code) = 0;
};

class HPLCLexer : public LexerBase
{
public:
  HPLCLexer() = default;
  TokenVector tokenize(const SourceCode& source_code) override;

private:
  int               m_line {1};
  int               m_column {0};
  std::string       m_fileName {""};
  TokenVector       m_resultVector;
  std::stringstream m_stringStream;

protected:
  const word getWord();

  bool isNumber(const word& word);

  bool isAlpha(const word& word);

  bool isStringLiteral(const word& word);

  Token generateToken(const word& input_word);
};