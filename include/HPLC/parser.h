#pragma once
#include "ast_node.h"
#include "lexer.h"

using SyntaxTree = ProgramNode;

class ParserBase
{
public:
  virtual SyntaxTree parse(const TokenVector& targetVector) = 0;
};

class HPLCParser : public ParserBase
{
public:
  Syntaxtree parse(const TokenVector& targetVector) override
  { 
    bool is_variable_decl { false };

    TokenVector variable_decl_tokens {};
    VariableDeclNode tempNode {};

    for (auto& token : targetVector)
    {
      //this means the code is planning on decl a var
      if (token.type == TokenType::KeywordInt)
      {
        is_variable_decl = true;
        tempNode.type = Int; 
        // identifer present
        // assign present
        // number present
        // then semicolon
      }
      else if (token.type == TokenType::Identifier)
      {
        if (is_variable_decl)
        {
          tempNode.operand = token.lexeme;
        }
      }
      else if (token.type == TokenType::Number)
      {
        if (is_variable_decl)
        {
          temp.value = std::stoi(token.lexeme);
        }
        
      }
      else if (token.type == TokenType::Semicolon)
      {
        is  
        is_variable_decl = false;
      }
    }
  } 
}