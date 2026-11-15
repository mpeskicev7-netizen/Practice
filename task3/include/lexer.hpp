#pragma once

#include <string>
#include <vector>
#include <variant>
#include <cctype>
#include <stdexcept>

enum class TokenType {
    String,
    Number,
    True,
    False,
    LBrace,   // {
    RBrace,   // }
    LBracket, // [
    RBracket, // ]
    Comma,    // ,
    Colon,    // :
    Null,
    End
};

// Объявление функции (реализация будет в .cpp)
std::string ToString(TokenType t);

using TokenValue = std::variant<std::string, double>;

struct Token {
    TokenType type;
    TokenValue value;
    size_t line;
    size_t position;
};

class Lexer {
public:
    explicit Lexer(const std::string& input);
    Token nextToken();

private:
    size_t pos_;
    size_t line_;
    size_t column_;
    const std::string input_;

    void SkipSpace();
    Token ReadNumbers();
    Token ReadString();
    Token ReadKeywords();
};