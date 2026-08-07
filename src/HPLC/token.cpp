#include "HPLC/token.h"

void Token::print()
{
    std::cout << "TokenType: " << static_cast<int>(type) << " | Lexeme: " << lexeme << " | Column: " << column << " | Row: " << row
              << " | FileName: " << fileName << std::endl;
}