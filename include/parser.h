#pragma once
#include "lexer.h"
#include "expression_node.h"

using SyntaxTree = ProgramNode;

class ParserBase
{   
    public:
        virtual SyntaxTree parse(TokenVector targetVector) = 0; 
};