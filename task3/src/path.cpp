#include "path.hpp"
#include "error.hpp"

Path::Path(const JsonValue& json, const std::string& str) : json_(json), str_(str), pos_(0) {}

const JsonValue& Path::execute() {
        pos_ = 0;
        
        if (str_[0] == '$') {
        pos_++;

        const JsonValue* value = &json_;
        while (pos_ < str_.size()) {
            if (str_[pos_] == '.') {
                pos_++;

                size_t end = str_.find_first_of(".[", pos_);
                std::string key;

                if (end == std::string::npos) {
                    key = str_.substr(pos_, str_.size() - pos_);
                    pos_ = str_.size();
                }
                else {
                    key = str_.substr(pos_, end - pos_);
                    pos_ = end;
                }
                if (value->is_object()) {
                    value = &value->getJsonObject().at(key);
                }
                else {
                    throw PathError("Not an object");
                }
            }
            else if (str_[pos_] == '[') {
                pos_++;

                size_t end = str_.find_first_of(']', pos_);
                int num;

                if (end != std::string::npos) {
                    std::string key = str_.substr(pos_, end - pos_);
                    pos_ = end + 1;
                    num = std::stoi(key);
                }
                else {
                    throw PathError("Missing closing bracket");
                }
                if (value->is_array()) {
                    if (num >= 0 && static_cast<size_t>(num) < value->getJsonArray().size()) {
                        value = &value->getJsonArray().at(num);
                    }
                }
                else {
                    throw PathError("Non at array");
                }
            }
            else {
                throw PathError("Unexpected character in path");
            }
        }

        return *value;
    }
    else {
        throw PathError("Invalid symbol");
    }
}