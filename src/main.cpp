#include <iostream>
#include "preprocessor.h"
#include "file_handling/file_reader.h"
#include "macro_resolver.h"
#include "lexer.h"
#include "parser.h"
#include "semantic_analyzer.h"
#include "instruction_generator.h"
#include "optimization/optimizer.h"
#include "bytecode_generator.h"


int main(int argc, char* argv[])
{
	//step 1 preprocessing module
	FileReaderBase*   fileReader   	  { nullptr };
	PreprocessorBase* preprocessor 	  { nullptr };
	std::string 	  processedOutput { preprocessor->preprocess(fileReader->readAll()) };

	//step 2 lexer module
	LexerBase*  lexer 		{ nullptr };
	TokenVector tokenVector { lexer->tokenize(processedOutput) };

	//step 3 parser module
	ParserBase* parser 	   { nullptr };
	SyntaxTree  syntaxTree { parser->parse(tokenVector) };

	//step 4 semantic analysis module
	SemanticAnalyzerBase* semanticAnalyzer  { nullptr };
	SyntaxTree 			  checkedSyntaxTree { semanticAnalyzer->analyze(syntaxTree) };


	//step 5 instruction generation module
	InstructionGeneratorBase* instructionGenerator { nullptr };
	InstructionVector 		  instructionVector    { instructionGenerator->lower(checkedSyntaxTree) };

	//step 6 optimizer
	OptimizerBase*    optimizer 				 { nullptr };
	InstructionVector optimizedInstructionVector { optimizer->optimize(instructionVector) };

	//step 7 byteCodeGenerator
	ByteCodeGeneratorBase* byteCodeGenerator { nullptr };
	std::string executableName { };
	byteCodeGenerator->generateUINT32(optimizedInstructionVector, executableName);
}