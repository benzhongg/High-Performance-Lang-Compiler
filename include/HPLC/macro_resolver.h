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
};

using MacroResolverVector = std::vector<MacroResolverBase*>;

class DefineMacroResolverStringApproach : public MacroResolverBase
{
private:
  std::unordered_map<std::string, std::string> m_macroTable {};

protected:
  std::vector<std::string> splitLines(std::string source_code)
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

  // TODO: refactor for double quotation 
  //       implement test cases by injecting different lines
  std::string applyMacros(std::string source_code_line)
  {
    // rename target_macro to macro_key
    for (auto& macro : m_macroTable)
    {
      std::string target_macro = macro.first;
      size_t      pos {0};
      pos = source_code_line.find(target_macro, pos);
      if (pos == std::string::npos)
      {
        continue;
      }

      //TODO: think about name
      if (isString(source_code_line))
      {
        int start = findStartOfString(source_code_line);
        int end = findEndOfString(source_code_line);
        
        while ((pos = source_code_line.find(target_macro, pos)) != std::string::npos)
        {
          if (pos > start && pos < end) { continue; }
          source_code_line.replace(pos, target_macro.length(), macro.second);
          pos = macro.second.length();
        }
      }
    }
    return source_code_line;
  }

public:
  std::string resolve(std::string source_code) override
  {
    std::string              result {""};
    std::vector<std::string> lines_vector {splitLines(source_code)};

    for (auto line : lines_vector)
    {
      result += process(line);
    }

    return result;
  }
};