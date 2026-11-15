#pragma once

#include "lexer.hpp"
#include "json_value.hpp" 
#include <vector>
#include <string>
#include <stdexcept>

class Parser {
private:
    std::vector<Token> tok_;
    size_t pos_;

public:
    explicit Parser(std::vector<Token> tokens);

    const Token& Peek() const;
    const Token& Advance();
    const Token& Consume(TokenType expected);

    JsonValue ParseValue();
    JsonValue ParseArray();
    JsonValue ParseObject();
};