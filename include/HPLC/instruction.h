#pragma once
#include "source_code.h"
#include <vector>

enum InstructionType
{

};

struct InstructionBase
{
  InstructionType instructionType;
  int             row;
  int             column;
  FileName        fileName;
};

using InstructionVector = std::vector<InstructionBase*>;