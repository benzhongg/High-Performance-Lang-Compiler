#include "HPLC/preprocessor.h"
#include "HPLC/ast_builder.h"
#include "HPLC/parser.h"
#include <iostream>

int main(int argc, char* argv[])
{
  // step 0 file reader module and source code obj construction
  FileReaderBase* file_reader {new StreamFileReader()};
  if (!file_reader->openFile("data/simple_example_0.hplc"))
  {
    // TODO: temp solution return to this
    std::cout << "invalid file path" << std::endl;
    return 0;
  }
  SourceCode source_code = file_reader->readAll();

  // step 1 preprocessing module
  PreprocessorBase* preprocessor {new HPLCPreprocessor()};
  preprocessor->preprocess(source_code);
  std::cout << source_code.contents;

  HPLCParser parser;
  ParseResult parse_result {parser.parse(source_code)};
  ASTBuilder ast_builder;
  std::vector<Diagnostic> diagnostics {parse_result.diagnostics};
  auto program {ast_builder.build(parse_result, source_code, diagnostics)};
  for (const auto& diagnostic : diagnostics)
  {
    std::cerr << diagnostic.message << " at " << diagnostic.span.line + 1 << ':' << diagnostic.span.column + 1
              << std::endl;
  }

  if (!diagnostics.empty())
    return 1;

  std::cout << "parsed " << program->statements.size() << " statements" << std::endl;

}