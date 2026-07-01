# Custom Lang Compiler

```text
    -----------------
    │  .HPLC File   │
    -----------------
            |
            ▼
┌────────────────────────┐                          
│     Preprocessor       │              
└────────────────────────┘
            |
            ▼
    ┌─────────────────┐          ┌─────────────────┐          ┌────────────────────────────┐
    │      Lexer      │─────────>│     Parser      │─────────>│      Semantic Analyzer     │
    └─────────────────┘          └─────────────────┘          └────────────────────────────┘ 
                                      ┌──────────────────────────────────┘
                                      ▼
                           ┌─────────────────────────┐                          
                           │  Instruction Generator  │              
                           └─────────────────────────┘          
                                      │
                                      ▼
                            ┌────────────────────────┐                          
                            │  Optimization Pass #1  │              
                            └────────────────────────┘
                                      │
                                      ▼
                            ┌────────────────────────┐                          
                            │  Optimization Pass #2  │              
                            └────────────────────────┘
                                      │
                                      ▼
                            ┌────────────────────────┐                          
                            │  Optimization Pass #3  │              
                            └────────────────────────┘
                          ┌────────────┘
                          ▼
        ┌───────────────────────────────────┐
        │         ByteCode Generator        │
        └───────────────────────────────────┘
                          │
                          ▼
                 ----------------
                 |  Executable  │
                 ----------------
```

## 1. Preprocessor
### 1.a Introduction
- The preprocessor will read source a .hlpc file and resolve macros.

### 1.b Responsiblities + Jobs + Behavior
- input is an .hplc file
- resolve preprocessor codes
- output is string (ResolvedSourceCode)

## 2. Lexer
### 2.a Introduction
- The lexer is responsible for lexical analysis. It's sole responsiblity is to break the source code into chunks of tokens. 
- Incorrectly written code will be caught at the stage if the text doesn't fit any existing token.
- Takes in preprocessor output. 
- Sends its own output to parser. 

### 2.b Responsibilities + Jobs + Behavior
- Input is ResolvedSourceCode
- tokenizes code one token at a time
- Output is a token list 
<br>
- What are tokens?
- Tokens are chunks of source code.
- Token lists are list of tokens.
```text
- Struct Token
    {
        type,
        lexeme,
        column,
        row
    }
```

## 3. Parser
### 3.a Introduction
- The parser performs syntax analysis. It will validate token relationships based on a set of grammar rules. And in the process develop a syntax tree. 
- It will throw errors upon encountering missing required tokens or extra tokens.
- One example is missing a paranthesis or having an extra one, another example if comparison parameter checking. 

### 3.b Responsibilities + Job + Behavior
- Input is a token list
- Check syntax
- Output is an Abstract Syntax Tree

## 4. Semantic Analyzer
### 4.a Introduction
- The Semantic Analyzer checks the code logic - types, meaning, and rules of the code.
- It will find any errors in semantics but not technical computational errors.

### 4.b Responsiblities + Job + Behavior
- Input is an abstract syntax tree
- decorates and verifies the syntax tree
- Output is an abstract syntax tree


## 5. Instruction Generator 
### 5.a Introduction
- The Instruction Generator is responsible for translating the validated AST into an abstract custom assembly like language. 

### 5.b Responsibilities + Jobs + Behavior
- Input is AST
- Output is assembly-like IR text 


## 6. Optimizer
### 6.a Introduction
- Optimizations take place over the IR representation of the code. Example Dead Code elimination

### 6.b Responsibilities + Jobs + Behavior
- Input is IR
- Output is IR

## 7. ByteCodeGenerator

### 7.a Introduction
- generates a bytecode program file from the IR list  

### 7.b Responsiblities + Jobs + Responsibilities
- Input is IR
- Output is executable program file and 