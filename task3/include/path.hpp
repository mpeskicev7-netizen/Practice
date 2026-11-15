#pragma once

#include "json_value.hpp"
#include <string>

class Path {
private:
    const JsonValue& json_;
    const std::string str_;
    size_t pos_ = 0;
public:
    explicit Path(const JsonValue& json, const std::string& str) : json_(json), str_(str), pos_(0) {}
};