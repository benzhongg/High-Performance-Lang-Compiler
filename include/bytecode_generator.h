#pragma once
#include "instruction.h"
#include <cstdint>

class ByteCodeGeneratorBase
{
public:
  virtual void generate(InstructionVector targetInstructionVector, std::string& targetFileName) = 0;
};