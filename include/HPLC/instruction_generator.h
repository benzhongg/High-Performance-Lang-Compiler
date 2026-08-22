#pragma once
#include "file_handling/file_reader.h"
#include "instruction.h"
#include "semantic_analyzer.h"

class InstructionGeneratorBase
{
public:
  virtual InstructionVector generate(std::shared_ptr<ProgramNode> program) = 0;
};