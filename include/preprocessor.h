#pragma once
#include <string>
#include "file_handling/file_reader.h"
#include <map>

class PreprocessorBase
{
public:
    
    virtual std::string preprocess(std::string source_code) = 0;
};