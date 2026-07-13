#pragma once
#include "lexer.h"

class MacroResolverBase
{
public:
  virtual void resolve(std::string& source_code) = 0;
};

using MacroResolverVector = std::vector<MacroResolverBase*>;

class DefineMacroResolver : public MacroResolverBase
{
private:
  std::unordered_map<std::string, std::string> m_macroTable {};
  friend class TestDefineMacroResolver;

protected:
  
  // we can make this const string ref since we're only reading and not modifying
  std::vector<std::string> splitLines(const std::string& source_code)
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

  // pass by ref instead of pass by val
  void addMacroToTable(std::string& source_code_line)
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

  // copy occuring at parameter passing
  // copy occuring at function return
  // and copy occurs inside from result = applyMacro
  // improvement we've reduced it to 2 copies
  
  // one copy at return
  void process(std::string& source_code_line)
  {
    if (startsWithDefineMacro(source_code_line))
    {
      addMacroToTable(source_code_line);
    }
    else
    {
      applyMacro(source_code_line);
      source_code_line += '\n';
    }
  }

  // refactored to pass by ref
    // saved memory allocation
    // saved copy constructor
    // saved obj destructor 
  bool startsWithDefineMacro(std::string& source_code_line)
  {
    return source_code_line.starts_with("#define ");
  }

  bool containsStringLiteral(std::string& source_code_line, size_t pos)
  {
    int quotation_count { 0 };
    for (size_t x = pos ; x < source_code_line.length() ; ++x)
    {
      if (source_code_line[x] == '\"')
      {
        ++quotation_count;
        if (quotation_count == 2) { return true; }
      }
    }

    return false;
  }

  size_t positionOfNextDoubleQuote(std::string& source_code_line, size_t pos)
  {
    return source_code_line.find("\"", pos);
  }

  void applyMacro(std::string& source_code_line)
  {
    for (auto& macro : m_macroTable)
    {
      std::string macro_identifier = macro.first;
      std::string macro_value = macro.second;
      size_t      pos {source_code_line.find(macro_identifier, 0)};
      
      if (pos == std::string::npos)
      {
        continue;
      }
      
      int start { 0 };
      int end { 0 };
      
      while ((pos = source_code_line.find(macro_identifier, pos)) != std::string::npos)
      {
        
        if (containsStringLiteral(source_code_line, start))
        {
          start = positionOfNextDoubleQuote(source_code_line, start);
          end   = positionOfNextDoubleQuote(source_code_line, start + 1);
        }
        
        bool is_within_quotes {false};
        is_within_quotes = (pos > start && pos < end) ? true : false;
        
        if (!is_within_quotes) 
        { 
          source_code_line.replace(pos, macro_identifier.length(), macro_value);
          pos += macro_value.length();
        }
        else
        {
          pos = end + 1;
        }

        start = pos;
      }
    }
  }

public:

  // originally there were 3 copy constructors happening, one at the function call, one inside function, and return 
  // a simple refactor will remove two copy constructor we can optimize this even further
  void resolve(std::string& source_code) override
  {
    std::string              result {""};
    std::vector<std::string> lines_vector {splitLines(source_code)};

    for (auto& line : lines_vector)
    {
      process(line);
      result += line;
      std::cout << line << std::endl;
    }
    
    source_code = result;
  }
};