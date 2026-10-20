#pragma once

#include <string>
#include <vector>
#include <variant>

using namespace std;

enum class TokenType {
    String,
    Number,
    True,
    False,
    LBrace,  //{
    RBrace, //}
    LBracket, //[
    RBracket, // ]
    Comma, // ,
    Colon, // :
    Null,
    End
};

using TokenValue = variant<string, double>;

struct Token {
    TokenType type;
    TokenValue value;
    size_t line;
    size_t position;
};