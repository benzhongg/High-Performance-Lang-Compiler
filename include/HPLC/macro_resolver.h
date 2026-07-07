#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "lexer.h"

class MacroResolverBase
{
public:
  virtual std::string resolve(std::string source_code) = 0;
  virtual TokenVector resolve(TokenVector source_code_tokens) = 0;
};

using MacroResolverVector = std::vector<MacroResolverBase*>;

class DefineMacroResolverStringApproach : public MacroResolverBase
{
private:
  std::unordered_map<std::string, std::string> m_macroTable {};

protected:
  std::vector<std::string> split(std::string source_code)
  {
    std::vector<std::string> result {};
    std::stringstream        sstream {source_code};

    std::string line {};
    while (std::getline(sstream, line))
    {
      result.push_back(line);
    }

    return result;
  }

  void addMacroToTable(std::string source_code_line)
  {
    std::vector<std::string> split_lines {};
    std::istringstream       iss {source_code_line};
    std::string              word {};
    while (std::getline(iss, word, ' '))
    {
      split_lines.push_back(word);
    }

    switch (split_lines.size())
    {
    case 1:
      break;
    case 2:
      break;
    case 3:
      m_macroTable[split_lines[1]] = split_lines[2];
      break;
    }
  }

  std::string process(std::string source_code_line)
  {
    std::string result {""};

    if (startsWithDefineMacro(source_code_line))
    {
      addMacroToTable(source_code_line);
    }
    else
    {
      result += applyMacros(source_code_line);
    }

    return result;
  }

  bool startsWithDefineMacro(std::string source_code_line)
  {
    // this string target is ugly
    return source_code_line.starts_with("#define ");
  }

  std::string applyMacros(std::string source_code_line)
  {
    for (auto macro : m_macroTable)
    {
      std::string target_macro = macro.first;
      size_t      pos {0};

      while ((pos = source_code_line.find(target_macro, pos)) != std::string::npos)
      {
        source_code_line.replace(pos, target_macro.length(), macro.second);
        pos = macro.second.length();
      }
    }
    return source_code_line;
  }

public:
  std::string resolve(std::string source_code) override
  {
    std::string              result {""};
    std::vector<std::string> lines_vector {split(source_code)};

    for (auto line : lines_vector)
    {
      result += process(line);
    }

    return result;
  }

  TokenVector resolve(TokenVector source_code_tokens) override {}
};

struct TokenHasher {
    std::size_t operator()(const Token& t) const noexcept {
        return std::hash<int>{}(t.type) ^ (std::hash<std::string>{}(t.lexeme) << 1);
    }
};

class DefineMacroResolverTokenApproach : public MacroResolverBase
{
private:

  std::unordered_map<Token, Token, TokenHasher> m_macroTable {};

protected:
  void process(TokenVector& target_token_line)
  {
    if (target_token_line[0].type == DefineMacro)
    {
      addToMacroTable(target_token_line);
    }
    else 
    {
      applyMacros(target_token_line);
    }
  }

  void addToMacroTable(TokenVector& target_token_line)
  {
    int size = target_token_line.size();
    switch (size)
    {
      // we should probably throw errors instead of letting it pass in the future
      case (1):
      case (2):
        target_token_line.clear();
        break;
      case (3):
      case (4):
        if (target_token_line[1].type == TokenType::Identifier && target_token_line[2].type == TokenType::Number)
        {
          m_macroTable[target_token_line[1]] = target_token_line[2];
        }
        break;
    }
    target_token_line.clear();
  }

  bool tokensMatch(Token target1, Token target2)
  {
    return target1.type == target2.type && target1.lexeme == target2.lexeme;
  }
  
  void applyMacros(TokenVector& target_token_line)
  {
    for (Token& token : target_token_line)
    {
      for (auto macro : m_macroTable)
      {
        if (tokensMatch(token, macro.first))
        {
          token = macro.second;
        }
      }
    }
  }


public:
  std::string resolve(std::string source_code) override {}

  TokenVector resolve(TokenVector source_code_tokens) override
  {
    //iterate over every token in the input TokenVector
    TokenVector resultVector {};
    TokenVector line {};    
    for (auto token : source_code_tokens)
    {
      line.push_back(token);
      if (token.type == TokenType::NewLine)
      {
        process(line);
        resultVector.insert(resultVector.end(), line.begin(), line.end());
        line.clear();
      }
    }      

    return resultVector;
  }
};