#include "lexer.hpp"

std::string ToString(TokenType t) {
    switch(t) {
        case TokenType::String:   return "String";
        case TokenType::Number:   return "Number";
        case TokenType::True:     return "True";
        case TokenType::False:    return "False";
        case TokenType::LBrace:   return "LBrace";
        case TokenType::RBrace:   return "RBrace";
        case TokenType::LBracket: return "LBracket";
        case TokenType::RBracket: return "RBracket";
        case TokenType::Comma:    return "Comma";
        case TokenType::Colon:    return "Colon";
        case TokenType::Null:     return "Null";
        case TokenType::End:      return "End";
        default:
            throw std::runtime_error("Unknown TokenType");
    }
}

Lexer::Lexer(const std::string& input) 
    : pos_(0), line_(1), column_(1), input_(input) {}

Token Lexer::nextToken() {
    SkipSpace();

    if (pos_ >= input_.size()) {
        return {TokenType::End, "", line_, column_};
    }

    size_t token_line = line_;
    size_t token_column = column_;
    char y = input_[pos_];

    if (y == '{') {
        pos_++; column_++;
        return {TokenType::LBrace, "{", token_line, token_column};
    }
    if (y == '}') {
        pos_++; column_++;
        return {TokenType::RBrace, "}", token_line, token_column};
    }
    if (y == '[') {
        pos_++; column_++;
        return {TokenType::LBracket, "[", token_line, token_column};
    }
    if (y == ']') {
        pos_++; column_++;
        return {TokenType::RBracket, "]", token_line, token_column};
    }
    if (y == ',') {
        pos_++; column_++;
        return {TokenType::Comma, ",", token_line, token_column};
    }
    if (y == ':') {
        pos_++; column_++;
        return {TokenType::Colon, ":", token_line, token_column};
    }
    if (std::isdigit(y) || y == '-') {
        return ReadNumbers(); 
    }
    if (y == '"') {
        return ReadString();
    }
    if (y == 't' || y == 'T' || y == 'f' || y == 'F' || y == 'n' || y == 'N') {
        return ReadKeywords();
    }

    return {TokenType::End, "", token_line, token_column};
}

void Lexer::SkipSpace() {
    while(pos_ < input_.size() && std::isspace(input_[pos_])) {
        char x = input_[pos_];
        if (x == '\n') {
            line_++;
            column_ = 1;
        } else {
            column_++;
        }
        pos_++;
    }
}

Token Lexer::ReadNumbers() {
    size_t start = pos_;

    if (pos_ < input_.size() && input_[pos_] == '-') {
        pos_++; column_++;
    }

    char first = input_[pos_];
    if (!std::isdigit(first)) {
        throw std::runtime_error("Expected digit at position " + std::to_string(pos_));
    }

    pos_++; column_++;

    if (first == '0' && pos_ < input_.size() && std::isdigit(input_[pos_])) {
        std::string bad = input_.substr(start, 2); 
        throw std::runtime_error("Invalid number: leading zero not allowed in JSON (found '" + bad + "')");
    }

    while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
        pos_++; column_++;
    }

    if (pos_ < input_.size() && input_[pos_] == '.') {
        pos_++; column_++;
        while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
            pos_++; column_++;
        }
    }

    if (pos_ < input_.size() && (input_[pos_] == 'e' || input_[pos_] == 'E')) {
        pos_++; column_++;
        if (pos_ < input_.size() && (input_[pos_] == '+' || input_[pos_] == '-')) {
            pos_++; column_++;
        }
        while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
            pos_++; column_++;
        }
    }

    std::string text = input_.substr(start, pos_ - start);
    double value = std::stod(text);

    return {TokenType::Number, value, line_, column_};
}

Token Lexer::ReadString() {
    pos_++; column_++;
    std::string result;

    while(pos_ < input_.size() && input_[pos_] != '"') {
        char c = input_[pos_];

        if (c == '\\') {
            pos_++; column_++;
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
            else if (escaped == 'u') {
                result += "\\u";
                for (int i = 0; i < 4; i++) {
                    if (pos_ + 1 + i < input_.size() && std::isxdigit(input_[pos_ + 1 + i])) {
                        result += input_[pos_ + 1 + i];
                    } else {
                        throw std::runtime_error("Invalid escape sequence");
                    }
                }
                pos_ += 4; column_ += 4;
            } else {
                throw std::runtime_error("Invalid escape sequence: \\" + std::string(1, escaped));
            }
            pos_++; column_++;
        } else {
            result += c;
            pos_++; column_++;
        }
    }

    if (pos_ >= input_.size()) {
        throw std::runtime_error("Unexpected end of string");
    }

    pos_++; column_++;
    return {TokenType::String, result, line_, column_};
}

Token Lexer::ReadKeywords() {
    size_t start = pos_;

    while (pos_ < input_.size() && std::isalpha(input_[pos_])) {
        pos_++; column_++;
    }

    std::string word = input_.substr(start, pos_ - start);

    if (pos_ < input_.size() && std::isalnum(input_[pos_])) {
        throw std::runtime_error("Invalid keyword: " + word);
    }

    if (word == "true") {
        return {TokenType::True, word, line_, column_};
    }
    if (word == "false") {
        return {TokenType::False, word, line_, column_};
    }
    if (word == "null") {
        return {TokenType::Null, word, line_, column_};
    }

    throw std::runtime_error("Unknown keyword: " + word);
}