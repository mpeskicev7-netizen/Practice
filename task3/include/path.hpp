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
    explicit Path(const JsonValue& json, const std::string& str) : json_(json), str_(str), pos_(0) {}

    const JsonValue& execute() {
        if (str_[0] == '$') {
            pos_++;

            const JsonValue* value = &json_;
            while(pos_ < str_.size()) {
                if (str_[pos_] == '.') {
                    pos_++;

                    size_t end = str_.find_first_of('.[', pos_);
                    std::string key;

                    if (end == std::string::npos) {
                        key = str_.substr(pos_, str_.size() - pos_);
                        pos_ = str_.size();
                    }
                    else {
                        key = str_.substr(pos_, end - pos_);
                        pos_ = end;
                    }
                }
                else {
                    break;
                }
            }

            return *value;
        }
        else {
            throw std::runtime_error("Invalid symbol");
        }
    }
};