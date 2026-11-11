#pragma once

#include "lexer.hpp"
#include "json_value.hpp"
#include <string>
#include <vector>
#include <stdexcept>


class Parser {
    private:
        std::vector<Token> tok_;
        size_t pos_;
    public:
        Parser(std::vector<Token> tokens) : pos_(0), tok_(std::move(tokens)) {} 
        
        const Token& Peek() const {
            if (pos_ >= tok_.size()) {
                throw std::runtime_error("Error, the position is larger than the size");
            }

            return tok_[pos_];
        }

        const Token& Advance() {
            if (pos_ >= tok_.size()) {
                throw std::runtime_error("Error, the position is larger than the size");
            }

            return tok_[pos_++];
        }

        const Token& Consume(TokenType expeсted) {
            std::string msg = "Expected " + ToString(expeсted) + ", but got " + ToString(Peek().type) + " at line " + std::to_string(Peek().line) + ", column " + std::to_string(Peek().position);

            if (Peek().type == expeсted) {
                return Advance();
            }
            else {
                throw std::runtime_error(msg);
            }
        }

        JsonValue ParseValue() {
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
                break;

                default:
                throw std::runtime_error("Expected " + ToString(t.type) + ", but got " + ToString(Peek().type) + " at line " + std::to_string(Peek().line) + ", column " + std::to_string(Peek().position));

                
            }
        }
};