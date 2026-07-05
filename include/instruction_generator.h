#pragma once
#include "file_handling/file_reader.h"
#include "semantic_analyzer.h"
#include "instruction.h"

class InstructionGeneratorBase
{

public:
    virtual InstructionVector lower(SyntaxTree targetSyntaxTree) = 0;

};