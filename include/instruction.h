#pragma once
#include "lexer.h"

enum InstructionType
{

};

struct InstructionBase
{
    InstructionType instructionType;
    int row;
    int column;
    FileName fileName;
};

using InstructionVector = std::vector<InstructionBase*>;