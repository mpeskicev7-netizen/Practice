#pragma once

#include <stdexcept>
#include <variant>
#include <map>
#include <vector>
#include <string>
#include <memory>

class JsonValue;

using JsonArray = std::vector<JsonValue>;
using JsonObject = std::map<std::string, JsonValue>;
using JsonValueVariant = std::variant< 
    std::nullptr_t,
    std::string,
    std::unique_ptr<JsonArray>,
    std::unique_ptr<JsonObject>,
    double,
    bool
>;

class JsonValue {
    private:
        JsonValueVariant value_;
    public:
        JsonValue(double data) : value_(data) {}

        JsonValue(std::string data) : value_(std::move(data)) {}

        JsonValue(std::nullptr_t) : value_(nullptr) {}
        
        JsonValue(bool data) : value_(data) {}

        bool is_bool() const {
            return std::holds_alternative<bool>(value_);
        }

        bool is_double() const {
            return std::holds_alternative<double>(value_);
        }

        bool is_string() const {
            return std::holds_alternative<std::string>(value_);
        }

        bool is_null() const {
            return std::holds_alternative<nullptr_t>(value_);
        }

        double getDouble() const {
            if (!is_double()) {
                throw std::runtime_error("Expected double, but got something else");
            }

            return std::get<double>(value_);
        }

        std::string getString() const {
            if (!is_string()) {
                throw std::runtime_error("Expected string");
            }

            return std::get<std::string>(value_);
        }

        bool getBool() const {
            if (!is_bool()) {
                throw std::runtime_error("Expected bool");
            }

            return std::get<bool>(value_);
        }
};
