#include "HPLC/macro_resolver.h"

void DefineMacroResolver::resolve(std::string& source_code)
{
  std::string result;
  result.reserve(source_code.size());

  // TODO: refactor to use string view to avoid copying strings overhead
  std::vector<std::string> lines_vector {splitLines(source_code)};

  for (auto& line : lines_vector)
  {
    process(line);
    result += line;
    std::cout << line << std::endl;
  }

  source_code = result;
}

std::vector<std::string> DefineMacroResolver::splitLines(const std::string& source_code)
{
  std::vector<std::string> result {};
  std::stringstream        sstream {source_code};

  std::string line {""};
  while (std::getline(sstream, line))
  {
    result.push_back(line);
  }

  return result;
}

// pass by ref instead of pass by val
void DefineMacroResolver::addMacroToTable(std::string& source_code_line)
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
    return;
  case 2:
    return;
  case 3:
    m_macroTable[split_lines[1]] = split_lines[2];
    return;
  }

  std::unreachable();
}

// copy occuring at parameter passing
// copy occuring at function return
// and copy occurs inside from result = applyMacro
// improvement we've reduced it to 2 copies

// one copy at return
void DefineMacroResolver::process(std::string& source_code_line)
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
bool DefineMacroResolver::startsWithDefineMacro(std::string& source_code_line)
{
  return source_code_line.starts_with("#define ");
}

bool DefineMacroResolver::containsStringLiteral(const std::string& source_code_line, size_t pos)
{
  int quotation_count {0};
  for (size_t x = pos; x < source_code_line.length(); ++x)
  {
    if (source_code_line[x] == '\"')
    {
      ++quotation_count;
      if (quotation_count == 2)
      {
        return true;
      }
    }
  }

  return false;
}

size_t DefineMacroResolver::positionOfNextDoubleQuote(const std::string& source_code_line, size_t pos)
{
  return source_code_line.find("\"", pos);
}

void DefineMacroResolver::applyMacro(std::string& source_code_line)
{
  for (auto& macro : m_macroTable)
  {
    std::string macro_identifier = macro.first;
    std::string macro_value      = macro.second;
    size_t      pos {source_code_line.find(macro_identifier, 0)};

    if (pos == std::string::npos)
    {
      continue;
    }

    int start {0};
    int end {0};

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