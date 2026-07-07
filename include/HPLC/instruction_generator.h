#pragma once
#include "file_handling/file_reader.h"
#include "instruction.h"
#include "semantic_analyzer.h"

class InstructionGeneratorBase
{
public:
  virtual InstructionVector generate(SyntaxTree targetSyntaxTree) = 0;
};