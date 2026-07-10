#include "HPLC/preprocessor.h"
#include "HPLC/lexer.h"

int main(int argc, char* argv[])
{
  // step 0 file reader module and source code obj construction
  FileReaderBase* file_reader {new StreamFileReader()};
  if (!file_reader->openFile("data/simple_example_1.hplc"))
  {
    // TODO: temp solution return to this
    std::cout << "invalid file path" << std::endl;
    return 0;
  }
  SourceCode source_code = file_reader->readAll();

  // step 1 preprocessing module
  PreprocessorBase* preprocessor {new HPLCPreprocessor()};
  SourceCode        preprocessed_source_code = preprocessor->preprocess(source_code);
  std::cout << preprocessed_source_code.contents;

  // step 2 lexer module
  LexerBase* lexer {new HPLCLexer()};
  TokenVector lexed_token_vector {lexer->tokenize(preprocessed_source_code)};
  for (auto& token : lexed_token_vector)
  {
    token.print();
  }
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