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
};