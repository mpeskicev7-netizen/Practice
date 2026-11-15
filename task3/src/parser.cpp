#include "parser.hpp"

Parser::Parser(std::vector<Token> tokens) 
    : tok_(std::move(tokens)), pos_(0) {}

const Token& Parser::Peek() const {
    if (pos_ >= tok_.size()) {
        throw std::runtime_error("Error, the position is larger than the size");
    }
    return tok_[pos_];
}

const Token& Parser::Advance() {
    if (pos_ >= tok_.size()) {
        throw std::runtime_error("Error, the position is larger than the size");
    }
    return tok_[pos_++];
}

const Token& Parser::Consume(TokenType expected) {
    std::string msg = "Expected " + ToString(expected) + 
                      ", but got " + ToString(Peek().type) + 
                      " at line " + std::to_string(Peek().line) + 
                      ", column " + std::to_string(Peek().position);

    if (Peek().type == expected) {
        return Advance();
    } else {
        throw std::runtime_error(msg);
    }
}

JsonValue Parser::ParseValue() {
    const Token& t = Peek();

    switch(t.type) {
        case TokenType::True:
            Consume(TokenType::True);
            return JsonValue(true);
        case TokenType::False:
            Consume(TokenType::False);
            return JsonValue(false);
        case TokenType::Null:
            Consume(TokenType::Null);
            return JsonValue(nullptr);
        case TokenType::Number:
            Consume(TokenType::Number);
            return JsonValue(std::get<double>(t.value));
        case TokenType::String:
            Consume(TokenType::String);
            return JsonValue(std::get<std::string>(t.value));
        case TokenType::LBracket:
            return ParseArray();
        case TokenType::LBrace:
            return ParseObject();
        default:
            throw std::runtime_error("Unexpected token " + ToString(t.type) + 
                                     " at line " + std::to_string(t.line) + 
                                     ", column " + std::to_string(t.position));
    }
}

JsonValue Parser::ParseArray() {
    Consume(TokenType::LBracket);
    JsonArray j;

    if (Peek().type == TokenType::RBracket) {
        Consume(TokenType::RBracket);
        return JsonValue(std::move(j));
    } else {
        while(true) {
            JsonValue val = ParseValue();
            j.push_back(std::move(val));

            if (Peek().type == TokenType::RBracket) {
                Consume(TokenType::RBracket);
                break;
            }
            if (Peek().type == TokenType::Comma) {
                Consume(TokenType::Comma);
                continue;
            } else {
                throw std::runtime_error("Unknown type " + ToString(Peek().type) + 
                                         " at line " + std::to_string(Peek().line) + 
                                         ", column " + std::to_string(Peek().position));
            }
        }
        return JsonValue(std::move(j));
    }
}

JsonValue Parser::ParseObject() {
    Consume(TokenType::LBrace);
    JsonObject obj;

    if (Peek().type == TokenType::RBrace) {
        Consume(TokenType::RBrace);
        return JsonValue(std::move(obj));
    } else {
        while(true) {
            const Token& keyToken = Consume(TokenType::String);
            std::string key = std::get<std::string>(keyToken.value);

            Consume(TokenType::Colon);

            JsonValue val = ParseValue();
            obj[key] = std::move(val);

            if (Peek().type == TokenType::Comma) {
                Consume(TokenType::Comma);
                continue;
            }
            if (Peek().type == TokenType::RBrace) {
                Consume(TokenType::RBrace);
                break;
            } else {
                throw std::runtime_error("Unknown type " + ToString(Peek().type) + 
                    " at line " + std::to_string(Peek().line) + 
                        ", column " + std::to_string(Peek().position));
            }
        }
        return JsonValue(std::move(obj));
    }
}