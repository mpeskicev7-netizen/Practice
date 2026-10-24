#pragma once

#include <string>
#include <vector>
#include <variant>
#include <cctype>

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

using TokenValue = std::variant<std::string, double>;

struct Token {
    TokenType type;
    TokenValue value;
    size_t line;
    size_t position;
};

class Lexer {
    public:
        explicit Lexer(const std::string& input) : pos_(0), line_(1), column_(1), input_(input){

        }

        Token nextToken() {
            SkipSpace();

            if (pos_ >= input_.size()) {
                return {TokenType::End, "", line_, column_};
            }

            size_t token_line = line_;
            size_t token_column = column_;
            
            char y = input_[pos_];

            if (y == '{') {
                pos_++;
                column_++;
                return {TokenType::LBrace, "{", token_line, token_column};
            }

            if (y == '}') {
                pos_++;
                column_++;
                return {TokenType::RBrace, "}", token_line, token_column};
            }

            if (y == '[') {
                pos_++;
                column_++;
                return {TokenType::LBracket, "[", token_line, token_column};
            }

            if (y == ']') {
                pos_++;
                column_++;
                return {TokenType::RBracket, "]", token_line, token_column};
            }

            if (y == ',') {
                pos_++;
                column_++;
                return {TokenType::Comma, ",", token_line, token_column};
            }

            if (y == ':') {
                pos_++;
                column_++;
                return {TokenType::Colon, ":", token_line, token_column};
            }

            return {TokenType::End, "", token_line, token_column};
        }
    private:
        size_t pos_;
        size_t line_;
        size_t column_;
        const std::string input_;

        void SkipSpace() {
            while(pos_ < input_.size() && std::isspace(input_[pos_])) {
                char x = input_[pos_];

                if (x == '\n') {
                    line_++;
                    column_ = 1;
                }
                else {
                    column_++;
                }

                pos_++;
            }
        }
};