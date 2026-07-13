#pragma once
#include "HPLC/source_code.h"
#include "HPLC/token.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

class LexerBase
{
public:
  // const word ref since we're only reading the input
  virtual TokenVector tokenize(const SourceCode& input_source_code) = 0;
};

using word = std::string;

class HPLCLexer : public LexerBase
{
private:
  int               m_line {1};
  int               m_column {0};
  std::string       m_fileName {""};
  TokenVector       m_resultVector {};
  std::stringstream m_stringStream {};

protected:
  const word getWord()
  {
    char ch;

    if (!m_stringStream.get(ch))
    {
      return "\0";
    }

    if (ch == '\n')
    {
      return "\n";
    }

    if (ch == ';')
    {
      return ";";
    }

    while (ch == ' ' || ch == '\t')
    {
      if (ch == ' ')
        m_column++;
      else if (ch == '\t')
        m_column += 4;

      if (!m_stringStream.get(ch))
      {
        return "\0";
      }
      if (ch == '\n')
      {
        return "\n";
      }
    }

    word result_word {};
    result_word += ch;

    while (m_stringStream.peek() != EOF)
    {
      char next = m_stringStream.peek();

      if (next == ' ' || next == '\t' || next == '\n' || next == '=' || next == '+' || next == ';' || next == '(' ||
          next == ')' || next == '{' || next == '}')
      {
        break;
      }

      m_stringStream.get(ch);
      result_word += ch;
    }
    return result_word;
  }

  // const word ref since we're only reading the input
  bool isNumber(const word& word)
  {
    return std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isdigit(c); });
  }

  // const word ref since we're only reading the input
  bool isAlpha(const word& word)
  {
    if (std::isdigit(word[0]))
    {
      return false;
    }

    return true;
  }
  
  // const word ref since we're only reading the input
  bool isStringLiteral(const word& word) { return (word.front() == '\"' && word.back() == '\"'); }

  // const word ref since we're only reading the input
  Token generateToken(const word& input_word)
  {

    auto createToken = [this](TokenType input_type, Lexeme word)
    { return Token(input_type, word, m_column, m_line, m_fileName); };

    TokenType current_token_type {};
    Token     result_token {};

    if (input_word.length() == 1)
    {
      if (input_word == "\n")
      {
        result_token = createToken(TokenType::NewLine, input_word);
        m_line++;
        m_column = 0;
      }
      else if (input_word == "=")
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

    if (result_token.type != TokenType::Unknown)
    {
      m_column += input_word.length();
      return result_token;
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

    else
    {
      throw std::runtime_error("Unexpected character: " + input_word + " at line " + std::to_string(m_line) +
                               " at column " + std::to_string(m_column) + "\n");
    }

    m_column += input_word.length();
    
    return result_token;
  }

public:
  HPLCLexer() = default;
  // const word ref since we're only reading the input
  TokenVector tokenize(const SourceCode& source_code) override
  {
    m_stringStream.str(source_code.contents);
    m_fileName = source_code.name;

    word current_word {};

    while ((current_word = getWord()) != "\0")
    {
      try
      {
        m_resultVector.push_back(generateToken(current_word));
      }
      catch (std::exception& e)
      {
        std::cerr << "Compiler Error: " << e.what();
      }
    }

    return m_resultVector;
  }
};