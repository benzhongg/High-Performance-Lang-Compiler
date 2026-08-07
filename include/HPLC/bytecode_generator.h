#pragma once
#include <cstdint>
#include "instruction.h"

class ByteCodeGeneratorBase
{
public:
  virtual void generate(InstructionVector targetInstructionVector, std::string& targetFileName) = 0;
};