#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

enum TokenType
{
  // keyword tokens
  KeywordInt, 
  KeywordReturn,

  // literals
  Identifier,
  Number,

  // single character tokens
  Assign,
  Plus,
  Minus,
  Star,
  Slash,
  Semicolon,
  LeftParanthesis,
  RightParanthesis,
  LeftCurlyBrace,
  RightCurlyBrace,
  Comma,

  EndOfFile
};

inline std::map<std::string, TokenType> ReservedWords {{"int", TokenType::KeywordInt},{"return", TokenType::KeywordReturn}};

using Lexeme   = std::string;
using FileName = std::string;

struct Token
{
  TokenType type {};
  Lexeme    lexeme {};
  int       column {};
  int       row {};
  FileName  fileName {};

  Token() = default;

  Token(TokenType t, Lexeme l, int c, int r, FileName fn) : type {t}, lexeme {l}, column {c}, row {r}, fileName {fn} {}

  void print()
  {
    std::cout << "TokenType: " << type << " | Lexeme: " << lexeme << " | Column: " << column << " | Row: " << row
              << " | FileName: " << fileName << std::endl;
  }
};

using TokenVector = std::vector<Token>;

class LexerBase
{
public:
  virtual TokenVector tokenize(std::string source_code) = 0;
};


using word = std::string;

class HPLCLexer : public LexerBase
{
private:
protected:
  bool  isNumber(word word);
  bool  isAlpha(word word);
  Token getToken(word word);

public:
  TokenVector tokenize(std::string source_code) override
  {
    // approach #1 divide into words then getToken(word)
    // aprooach #2 divide into lines then divide into words then getToken(word)
  }
};