#include "HPLC/token.h"
#include <format>

std::string prepareLexeme(const std::string& lexeme)
{
    // non-printables now won't affect output formatting
    if (lexeme == "\n") { return "\\n"; };
    return lexeme;
}

void Token::print()
{
    std::cout << std::format("TokenType: {:<3} | Lexeme: {:<6} | Column {:<3} | Row: {:<3} | FileName: {}\n",
                static_cast<int>(type), prepareLexeme(lexeme), column, row, fileName);
}