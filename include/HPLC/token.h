#pragma once
#include <unordered_map>
#include <string>
#include "HPLC/source_code.h"
#include <vector>
#include <iostream>
#include <cctype>
#include <algorithm>

enum TokenType
{
  // keyword tokens
  KeywordInt,    // int
  KeywordString, // string
  KeywordReturn, // return

  // literals
  Identifier,
  Number,
  String,

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

  NewLine,
  EndOfFile
};

inline std::unordered_map<std::string, TokenType> ReservedWords {{"int", TokenType::KeywordInt},
                                                       {"return", TokenType::KeywordReturn}};

using Lexeme   = std::string;

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

  bool operator==(const Token& other) const = default;
};

using TokenVector = std::vector<Token>;