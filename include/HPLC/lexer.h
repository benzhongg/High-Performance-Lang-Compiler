#pragma once
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

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

inline std::map<std::string, TokenType> ReservedWords {{"int", TokenType::KeywordInt},
                                                       {"return", TokenType::KeywordReturn}};

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

  bool operator==(const Token& other) const = default;
};

using TokenVector = std::vector<Token>;

class LexerBase
{
public:
  virtual TokenVector tokenize() = 0;
};

using word = std::string;

class HPLCLexer : public LexerBase
{
private:
  int               m_line {1};
  int               m_column {0};
  // TODO: later file name implementation
  std::string       m_fileName {"helloworld.hplc"};
  TokenVector       m_resultVector {};
  std::stringstream m_fileStream {};

protected:
  const word getWord()
  {
    char ch;

    if (!m_fileStream.get(ch))
    {
      return "\0";
    }

    // If it's a newline, return it immediately so tokenize() can increment m_line
    if (ch == '\n')
    {
      return "\n";
    }

    // Skip horizontal whitespace (spaces, tabs) but track columns
    while (ch == ' ' || ch == '\t')
    {
      if (ch == ' ')
        m_column++;
      else if (ch == '\t')
        m_column += 4; // Or whatever your tab width is

      if (!m_fileStream.get(ch))
      {
        return "\0";
      }
      if (ch == '\n')
      {
        return "\n";
      }
    }

    // Now build the actual token word
    word result_word {};
    result_word += ch;

    // Keep reading characters until we hit a delimiter (space, newline, or operator)
    // Note: You may want to customize what separates a "word" based on your language syntax
    while (m_fileStream.peek() != EOF)
    {
      char next = m_fileStream.peek();

      // Break if we hit a delimiter
      if (next == ' ' || next == '\t' || next == '\n' || next == '=' || next == '+' || next == ';' || next == '(' ||
          next == ')' || next == '{' || next == '}')
      {
        break;
      }

      m_fileStream.get(ch);
      result_word += ch;
    }

    return result_word;
  }

  bool isNumber(word word)
  {
    return std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isdigit(c); });
  }

  bool isAlpha(word word)
  {
    return std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isalpha(c); });
  }

  bool isStringLiteral(word word) { return (*word.begin() == '\"' && *word.end() == '\"'); }

  Token generateToken(word input_word)
  {

    auto createToken = [this](TokenType input_type, Lexeme word)
    { return Token(input_type, word, m_column, m_line, m_fileName); };

    TokenType current_token_type {};
    Token     result_token {};

    if (input_word == "\n")
    {
      result_token = createToken(TokenType::NewLine, input_word);
      m_line++;
      m_column = 0;
    }

    if (isNumber(input_word))
    {
      result_token = createToken(TokenType::Number, input_word);
    }

    else if (isStringLiteral(input_word))
    {
      result_token = createToken(TokenType::String, input_word);
    }

    else if (isAlpha(input_word))
    {
      if (input_word == "int")
      {
        result_token = createToken(TokenType::KeywordInt, input_word);
      }
      else if (input_word == "return")
      {
        result_token = createToken(TokenType::KeywordReturn, input_word);
      }
      else if (input_word == "string")
      {
        result_token = createToken(TokenType::KeywordString, input_word);
      }
      else
      {
        result_token = createToken(TokenType::Identifier, input_word);
      }
    }
    else if (input_word.length() == 1)
    {
      if (input_word == "=")
      {
        result_token = createToken(TokenType::Assign, input_word);
      }
      else if (input_word == "+")
      {
        result_token = createToken(TokenType::Plus, input_word);
      }
      else if (input_word == "*")
      {
        result_token = createToken(TokenType::Star, input_word);
      }
      else if (input_word == "/")
      {
        result_token = createToken(TokenType::Slash, input_word);
      }
      else if (input_word == ";")
      {
        result_token = createToken(TokenType::Semicolon, input_word);
      }
      else if (input_word == "(")
      {
        result_token = createToken(TokenType::LeftParanthesis, input_word);
      }
      else if (input_word == ")")
      {
        result_token = createToken(TokenType::RightParanthesis, input_word);
      }
      else if (input_word == "{")
      {
        result_token = createToken(TokenType::LeftCurlyBrace, input_word);
      }
      else if (input_word == "}")
      {
        result_token = createToken(TokenType::RightCurlyBrace, input_word);
      }
      else if (input_word == ",")
      {
        result_token = createToken(TokenType::Comma, input_word);
      }
    }
    m_column += input_word.length();
    return result_token;
  }

public:
  HPLCLexer(std::string source_code) { m_fileStream.str(source_code); }

  TokenVector tokenize() override
  {
    word current_word {};

    while ((current_word = getWord()) != "\0")
    {
      m_resultVector.push_back(generateToken(current_word));
    }
    return m_resultVector;
  }
};