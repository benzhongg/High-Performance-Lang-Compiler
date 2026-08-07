#include "HPLC/lexer.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

TokenVector HPLCLexer::tokenize(const SourceCode& source_code)
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

const word HPLCLexer::getWord()
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

bool HPLCLexer::isNumber(const word& word)
{
  return std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isdigit(c); });
}

bool HPLCLexer::isAlpha(const word& word)
{
  if (std::isdigit(word[0]))
  {
    return false;
  }

  return true;
}

bool HPLCLexer::isStringLiteral(const word& word) { return (word.front() == '\"' && word.back() == '\"'); }

Token HPLCLexer::generateToken(const word& input_word)
{
  using enum TokenType;

  auto createToken = [this](TokenType input_type, Lexeme word)
  { return Token(input_type, word, m_column, m_line, m_fileName); };

  TokenType current_token_type {};
  Token     result_token {};

  if (input_word.length() == 1)
  {
    if (input_word == "\n")
    {
      result_token = createToken(NewLine, input_word);
      m_line++;
      m_column = 0;
    }
    else if (input_word == "=")
    {
      result_token = createToken(Assign, input_word);
    }
    else if (input_word == "+")
    {
      result_token = createToken(Plus, input_word);
    }
    else if (input_word == "*")
    {
      result_token = createToken(Star, input_word);
    }
    else if (input_word == "/")
    {
      result_token = createToken(Slash, input_word);
    }
    else if (input_word == ";")
    {
      result_token = createToken(Semicolon, input_word);
    }
    else if (input_word == "(")
    {
      result_token = createToken(LeftParanthesis, input_word);
    }
    else if (input_word == ")")
    {
      result_token = createToken(RightParanthesis, input_word);
    }
    else if (input_word == "{")
    {
      result_token = createToken(LeftCurlyBrace, input_word);
    }
    else if (input_word == "}")
    {
      result_token = createToken(RightCurlyBrace, input_word);
    }
    else if (input_word == ",")
    {
      result_token = createToken(Comma, input_word);
    }
  }

  if (result_token.type != Unknown)
  {
    m_column += input_word.length();
    return result_token;
  }

  if (isNumber(input_word))
  {
    result_token = createToken(Number, input_word);
  }

  else if (isStringLiteral(input_word))
  {
    result_token = createToken(String, input_word);
  }

  else if (isAlpha(input_word))
  {
    if (input_word == "int")
    {
      result_token = createToken(KeywordInt, input_word);
    }
    else if (input_word == "return")
    {
      result_token = createToken(KeywordReturn, input_word);
    }
    else if (input_word == "string")
    {
      result_token = createToken(KeywordString, input_word);
    }
    else
    {
      result_token = createToken(Identifier, input_word);
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