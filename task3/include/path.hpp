#pragma once

#include "json_value.hpp"
#include <string>
#include <stdexcept>

class Path {
private:
    const JsonValue& json_;
    const std::string str_;
    size_t pos_ = 0;
public:
    explicit Path(const JsonValue& json, const std::string& str);

    const JsonValue& execute();
};