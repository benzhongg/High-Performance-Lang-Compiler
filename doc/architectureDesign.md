# Custom Lang Compiler
- Given a source .hplc file produce a valid program file for execution
<br>
- What is the .hplc file?
    - contains source instructions that match the simple instruction set from our HighPerf Interpreter project
<br>
- What is a valid program file?
    - an exectuable file -> bytecode

## 1. Preprocess
- locate macros
- resolve compiler definitions   
- reads input .hplc file
- produces ResolvedSourceCode
<br>
- What does the ResolvedSourceCode look like?
    - text

## 2. Lexer
- validate syntax in ResolvedSourceCode
- then generate token tree from ResolvedSourceCode
<br>
- What is the syntax?
    - accepted HPLC keywords(types + operators)
<br>
- What is a token tree?
    - tree representation of program flow
    - control flow graph?

## 3. Parse Token
- generates AST tree from token tree
- understand and validate code logic (everything)
    - ex: obj accessing, type checking, bounds checking
<br>  
- What does correct code logic look like?
    - correct code syntax with valid parameters and operators 
<br>
- What is an AST tree?
    - a specialized token tree representing validated code statements and logic 

## 4. Optimizer
- resolve simple code logic and skipped code logic 
- prunes AST tree
- generates another AST tree?

## 5. CodeGenerator
- produces bytecode instructions from AST
- valid bytecode instructions written to a program output file
<br>
- What do bytecode instructions look like?
    - hexadecimal
<br>
- What is the program output file?
    - undecided?