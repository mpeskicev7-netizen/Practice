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
        explicit Lexer(const std::string& input);

        Token nextToken() {
            SkipSpace();

            if (pos_ >= input_.size()) {
                return {TokenType::End, "", line_, column_};
            }
            return {TokenType::End, "", line_, column_};
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