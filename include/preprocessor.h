#pragma once
#include "file_handling/file_reader.h"
#include <map>
#include <string>

class PreprocessorBase
{
public:
  virtual std::string preprocess(std::string source_code) = 0;
};