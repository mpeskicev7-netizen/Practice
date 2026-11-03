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

            if (std::isdigit(y) || y == '-') {
                return ReadNumbers(); 
            }

            if (y == '"') {
                return ReadString();
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

        Token ReadNumbers() {
            size_t start = pos_;

            if (pos_ < input_.size() && input_[pos_] == '-') {
                pos_++;
                column_++;
            }

            char first = input_[pos_];

            if (!std::isdigit(first)) {
                throw std::runtime_error("Expected digit at position " + std::to_string(pos_));
            }

            pos_++;
            column_++;

            if (first == '0' && pos_ < input_.size() && std::isdigit(input_[pos_])) {
                std::string bad = input_.substr(start, 2); 
                throw std::runtime_error("Invalid number: leading zero not allowed in JSON (found '" + bad + "')");
            }

            while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
                pos_++;
                column_++;
            }

            if (pos_ < input_.size() && input_[pos_] == '.') {
                pos_++;
                column_++;

                while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
                    pos_++;
                    column_++;
                }
            }

            if (pos_ < input_.size() && (input_[pos_] == 'e' || input_[pos_] == 'E')) {
                pos_++;
                column_++;

                if (pos_ < input_.size() && (input_[pos_] == '+' || input_[pos_] == '-')) {
                    pos_++;
                    column_++;
                }

                while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
                    pos_++;
                    column_++;
                }
            }

            std::string text = input_.substr(start, pos_ - start);
            double value = std::stod(text);

            return {TokenType::Number, value, line_, column_};

        }

        Token ReadString() {
            pos_++;
            column_++;

            std::string result;

            while(pos_ < input_.size() && input_[pos_] != '"') {
                char c = input_[pos_];

                if (c == '\\') {
                    pos_++;
                    column_++;

                    if (pos_ >= input_.size()) {
                        throw std::runtime_error("Unexpected end of string after escape character");
                    }

                    char escaped = input_[pos_];

                    if (escaped == '"') result += '"';
                    else if (escaped == '\\') result += '\\';
                    else if (escaped == 'n') result += '\n';
                    else if (escaped == 't') result += '\t';
                    else if (escaped == 'r') result += '\r';
                    else if (escaped == 'b') result += '\b';
                    else if (escaped == 'f') result += '\f';
                    else if (escaped == '/') result += '/';
                    else {
                        throw std::runtime_error("Invalid escape sequence: \\" + std::string(1, escaped));
                    }

                    pos_++;
                    column_++;
                }
                else {
                    result += c;
                    pos_++;
                    column_++;
                }
            }

            if (pos_ >= input_.size()) {
                throw std::runtime_error("Unexpected end of string after escape character");
            }

            pos_++;
            column_++;

            return {TokenType::String, result, line_, column_};
        }
};