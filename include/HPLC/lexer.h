#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

enum TokenType
{
  // keyword tokens
  KeywordInt, //int
  KeywordString, //string
  KeywordReturn,  //return

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
  virtual TokenVector tokenize(std::string source_code) = 0;
};

using word = std::string;

class HPLCLexer : public LexerBase
{
private:
  int m_line { 0 };
  int m_column { 0 };
  // TODO: later
  std::string m_fileName {""};
  TokenVector m_resultVector {};

protected:
  
  word getWord() const;
  bool  isNumber(word word);
  bool  isAlpha(word word);
  Token getToken(word word);

public:
  TokenVector tokenize(std::string source_code) override
  {
    auto createToken=[] (TokenType token_type,word current_word, HPLCLexer* lexer)
    {
      lexer->m_resultVector.push_back(Token(token_type, current_word, lexer->m_column, lexer->m_line, lexer->m_fileName));
    };

    while(true)
    {
      word current_word = getWord();
      if (current_word == "\0") { break; }
      if (current_word == "\n") { m_line++; m_column = 0; continue; }

      //visitor design pattern, pass tokenizer to lambda function
      if (isNumber(current_word))
      {
        createToken(TokenType::Number, current_word, this);
      }
      
      if (isStringLiteral(current_word)) { }
      
      else if (isAlpha(current_word))
      {
        TokenType current_token_type { };

        if (current_word == "int") { current_token_type = TokenType::KeywordInt; }
        else if (current_word == "return") { current_token_type = TokenType::KeywordReturn; }
        else if (current_word == "string") { current_token_type = TokenType::KeywordString; }
        else if (current_word == "=") { current_token_type = TokenType::Assign; }
        else if (current_word == "+") { current_token_type = TokenType::Plus; }
        else if (current_word == "*") { current_token_type = TokenType::Star; }
        else if (current_word == "/") { current_token_type = TokenType::Slash; }
        else if (current_word == ";") { current_token_type = TokenType::Semicolon; }
        else if (current_word == "(") { current_token_type = TokenType::LeftParanthesis; }
        else if (current_word == ")") { current_token_type = TokenType::RightParanthesis; }
        else if (current_word == "{") { current_token_type = TokenType::LeftCurlyBrace; }
        else if (current_word == "}") { current_token_type = TokenType::RightCurlyBrace; }
        else if (current_word == ",") { current_token_type = TokenType::Comma; }
        else if (current_word == ",") { current_token_type = TokenType::Comma; }

        createToken(current_token_type, current_word, this);
      }
    }
    
    return m_resultVector;
  }
};