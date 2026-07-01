#include <iostream>

int main()
{
	string processedOutput = preprocessor.process(.hplc filepath);

	TokenList tokenList = lexer.tokenize(processedOutput);

	AST astTree = parser.parse(tokenList);

	AST updatedAST = semantic.analyze(astTree);

	InstructionList instrList = IRGenerator.generate(updatedAST);

	InstructionList optimizedIList = optimizer.optimize(instrList);

	ByteCodeFile finalFileOutput = byteCodegenerator.generate(optimizedIList, filename Name);
}
