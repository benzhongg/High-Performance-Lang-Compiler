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
  
  
  std::string example_program = "#define hello 5\nint x = hello; \nint y = hello; \nstring s = \"hello world\"; \nint y = hello + hello;";
  PreprocessorBase* preprocessor {new HPLCPreprocessor};
  std::string processedOutputTest {preprocessor->preprocess(example_program)};
  std::cout << processedOutputTest << std::endl;
  
  // //step 1 preprocessing module
  // FileReaderBase*   fileReader {nullptr};
  // PreprocessorBase* preprocessor {nullptr};
  // std::string       processedOutput {preprocessor->preprocess(fileReader->readAll())};
  
  // // step 2 lexer module
  // LexerBase*  lexer {nullptr};
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