#pragma once

#include <stdexcept>
#include <string>

class JsonError : public std::runtime_error {
public:
    explicit JsonError(const std::string& msg) 
        : std::runtime_error("JsonError: " + msg) {}
};

class LexerError : public JsonError {
public:
    explicit LexerError(const std::string& msg) 
        : JsonError("Lexer: " + msg) {}
};

class ParserError : public JsonError {
public:
    explicit ParserError(const std::string& msg) 
        : JsonError("Parser: " + msg) {}
};

class PathError : public JsonError {
public:
    explicit PathError(const std::string& msg) 
        : JsonError("Path: " + msg) {}
};