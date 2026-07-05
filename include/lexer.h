#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>

enum TokenType
{    
    //keyword tokens
    KeywordInt, //int 
    KeywordReturn, //return
    
    //literals
    Identifier, 
    Number,

    //single character tokens
    Assign,
    Plus,
    Minus,
    Star,
    Slash,
    Semicolon,
    LeftParanthesis,
    RightParanthesis,
    LeftCurlyBrace,
    RightCurlyBrace,
    Comma,

    //EOF
    EndOfFile
};

inline std::map<std::string, TokenType> ReservedWords
{
    {"int", TokenType::KeywordInt},
    {"return", TokenType::KeywordReturn}
};

using Lexeme = std::string;
using FileName = std::string;

struct Token
{
    TokenType type {};
    Lexeme lexeme {};
    int column {}; 
    int row {};
    FileName fileName {};

    Token() = default;

    Token(TokenType t, Lexeme l, int c, int r, FileName fn) :
        type{t}, lexeme{l}, column{c}, row{r}, fileName{fn}{}
    
    void print()
    {
        std::cout << "TokenType: " << type << " | Lexeme: " << lexeme 
            << " | Column: " << column << " | Row: " << row 
            << " | FileName: " << fileName << std::endl; 
    }
};

using TokenVector = std::vector<Token>;


class LexerBase
{
public:
    virtual TokenVector tokenize(std::string source_code) = 0;
};