#pragma once
#include "instruction.h"
#include <cstdint>

class ByteCodeGeneratorBase
{
public:
  virtual void generateUINT32(InstructionVector targetInstructionVector, std::string& targetFileName) = 0;
  virtual void generateINT32(InstructionVector targetInstructionVector, std::string& targetFileName)  = 0;
};