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
- echo "#DEFINE Foo 5" >> example.hplc | MacroResolver(....) -> string of text should have a variable named foo = 5

## 2. Lexer Module

### 2.a Classes
- Struct Token
    - tokenType
        - enum TokenTypes
    - lexeme
    - column
    - row
    - filename

- class Lexer()
    - Lexer();
    - tokenize(string literal)

### 2.b Tests
example string = "int x = 0;"
- tokenize() outputs [token1, token2, token3, token4, token 5]

## 3. Parser Module
### 3.a Classes
```text
- struct NodeBase 
    {
        nodeType,
        col,
        row,
        filename
    }
We are not implementing all NodeTypes

- struct ProgramNode : public NodeBase
// represents a list of base nodes
    {
        List<Node>
    }

- struct ExpressionNode : public NodeBase
    {

    }

// "a == b" is a binary expression, "1 + 2" as well, "a > b"
- struct BinaryExpression : ExpressionNode
    {
        operatorType operator; //+, - , /, * 
        ExpressionNode leftOperand;
        ExpresssionNode rightOperand;         
    } 

- struct PostFixExpression : ExpressionNode
    {
        operatorType operator;
        IdentifierExpression Identifier;        
    }

- struct AddressOfNode : ExpressionNode
    {
        ExpressionNode operand;
    }

- struct DereferenceNode : ExpressionNode
    {
        ExpressionNode operand;
    }

- struct SizeOfNode : ExpressionNode
    {
        ExpressionNode operand;
    }
```

### 3.b Tests
- parse(tokenList input) -> ProgramNode

## 4. Semantic Analyzer
### 4.a Classes
- class Semantic
    - analyze(Tree treeInput)

### 4.b Tests
- analyze(ProgramNode) -> no exception thrown
- analyze("int x = "helloworld") -> exception thrown

## 5. Instruction Generator
### 5.a Classes
- class InstructionGenerator
    - lower(ProgramNode)
- class FileWriter
- struct Instructions (same as Instruction Set from Interpreter)


### 5.b Tests
- InstructionGenerator(ProgramNode) -> output instruction file


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
- class ByteCodeGenerator 
    - lower(InstructionFile)
- class FileWriter

### 7.b Tests
- lower(InstructionFile input) -> executable
