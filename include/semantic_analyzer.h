#pragma once
#include "parser.h"

class SemanticAnalyzerBase
{

public:
    virtual SyntaxTree analyze(SyntaxTree targetAST) = 0;

};
