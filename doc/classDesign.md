# Abstract Class Design Layer

## 1. Preprocessor Module
### 1.a Classes
- FileReader
    - Take in filepath or an existing file stream
- MacroResolver
    - Approach #1
    - resolveMacros(FileReader reader1)
        - visitor pattern 
        - MacroResolver takes in FileReader
        - Based on visitor pattern, we can inject FileReader obj to a function named resolveMacros of the MacroReader class

    - Approach #2
    - preprocessor(FileReader, MacroResolver);
        - it's weak because we're having one class hold one function 
        - single responsibility

### 1.b Tests
- Preprocessor.process(validfile.hplc) -> success
- FileReader(validfile.hplc) -> success
- MacroResolver(FileReader(validfile.hplc)) -> string of text
- MacroResolver(FileReader)
- echo "#DEFINE Foo 5" >> example.hplc | MacroResolver(....) -> string of text should have a variable named foo = 5

## 2. Lexer Module

### 2.a Classes
- Struct Token
    - tokenType
        - enum TokenTypes
    - lexeme
    - column
    - row 
- class Scanner
    Input Approach
    - Scanner(string literal); //in memory
    
    API approach #1
    - tokenize() //returns full list of tokens, throws error on unidentified tok types
    
    API approach #2
    - getNextToken();

### 2.b Tests
example string = "int x = 0;"
approach 1
- tokenize() outputs [token1, token2, token3, token4, token 5]
approach 2
- nextToken() outputs resultToken{keyword_ident, 'int', 0, 0}

## 3. Parser Module
### 3.a Classes
- struct Node()
    - abstract node representations
    - addLeftOperand()
    - addInitializerValue()
- struct Tree 
class Noder
    - assemble(//list of nodes) 

### 3.b Tests
- assemble(Nodes) -> Tree


## 4. Semantic Analyzer
### 4.a Classes

- class Checker
    - run(Tree treeInput)

### 4.b Tests
- run(treeInput) -> no exception thrown

## 5. Instruction Generator
### 5.a Classes
- struct InstructionBase
- struct Instruction
    - grabNextNode(Tree TreeInput)
- class FileWriter
    - addNewLine()

### 5.b Tests
- InstructionBase.grabNextNode() -> turns Instruction into fully defined obj


## 6. Optimizations
### 6.a Classes
- struct BasicBlocks

- struct ControlFlowGraphs

- class Optimizer()
    - deadCodeElimination()
    - constantFolding()
    - constantAndCopyPropogation()

### 6.a Tests
- deadCodeElimination(File) -> removes unused branches of code
- constantlFolding() -> int minute = 1 * 60 -> turns into int minute = 60;
- constantAndCopyPropogation() -> x = 5; y = x + 5; -> turns into x = 5; y = 5 + 5;

## 7. ByteCode Generator
### 7.a Classes
- class Translator 
- class FileWriter

### 7.b Tests
-
