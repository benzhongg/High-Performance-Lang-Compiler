#include <iostream>
#include "HPLC/bytecode_generator.h"
#include "HPLC/file_handling/file_reader.h"
#include "HPLC/instruction_generator.h"
#include "HPLC/lexer.h"
#include "HPLC/macro_resolver.h"
#include "HPLC/optimization/optimizer.h"
#include "HPLC/parser.h"
#include "HPLC/preprocessor.h"
#include "HPLC/semantic_analyzer.h"

int main(int argc, char* argv[])
{
  std::string program_string {"int x = 5 \n int y = 10 \n"};
  TokenVector result_vector {};
  HPLCLexer test_lexer(program_string);
  result_vector = test_lexer.tokenize();
  for (auto token : result_vector)
  {
    token.print();
  }
  
  // //step 1 preprocessing module
  // FileReaderBase*   fileReader {nullptr};
  // PreprocessorBase* preprocessor {new HPLCPreprocessor()};
  // std::string       processedOutput {preprocessor->preprocess(fileReader->readAll())};
  
  // // step 2 lexer module 
  // LexerBase*  lexer {new HPLCLexer()};
  // TokenVector tokenVector {lexer->tokenize(processedOutput)};

  // // step 3 parser module
  // ParserBase* parser {nullptr};
  // SyntaxTree  syntaxTree {parser->parse(tokenVector)};

  // // step 4 semantic analysis module
  // SemanticAnalyzerBase* semanticAnalyzer {nullptr};
  // SyntaxTree            checkedSyntaxTree {semanticAnalyzer->analyze(syntaxTree)};

  // // step 5 instruction generation module
  // InstructionGeneratorBase* instructionGenerator {nullptr};
  // InstructionVector         instructionVector {instructionGenerator->generate(checkedSyntaxTree)};

  // // step 6 optimizer
  // OptimizerBase*    optimizer {nullptr};
  // InstructionVector optimizedInstructionVector {optimizer->optimize(instructionVector)};

  // // step 7 byteCodeGenerator
  // ByteCodeGeneratorBase* byteCodeGenerator {nullptr};
  // std::string            executableName {"exec"};
  // byteCodeGenerator->generate(optimizedInstructionVector, executableName);
}