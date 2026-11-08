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
        JsonValue() : value_(nullptr) {}

        JsonValue(double data) : value_(data) {}

        JsonValue(std::string data) : value_(std::move(data)) {}

        JsonValue(std::nullptr_t) : value_(nullptr) {}
        
        JsonValue(bool data) : value_(data) {}

        JsonValue(JsonArray&& arr) : value_(std::make_unique<JsonArray>(std::move(arr))) {}

        JsonValue(JsonObject&& obj) : value_(std::make_unique<JsonObject>(std::move(obj))) {}

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

        bool is_array() const {
            return std::holds_alternative<std::unique_ptr<JsonArray>>(value_);
        }

        bool is_object() const {
            return std::holds_alternative<std::unique_ptr<JsonObject>>(value_);
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

        const JsonArray& getJsonArray() const {
            if (!is_array()) {
                throw std::runtime_error("Expected array");
            }

            return *std::get<std::unique_ptr<JsonArray>>(value_);
        }

        const JsonObject& getJsonObject() const {
            if (!is_object()) {
                throw std::runtime_error("Expected object");
            }

            return *std::get<std::unique_ptr<JsonObject>>(value_);
        }

        bool operator==(const JsonValue& other) const {
            if (!(this->value_.index() == other.value_.index())) {
                return false;
            }

            switch(value_.index()) {
                case 0:
                    return true;
                case 1:
                    return std::get<std::string>(this->value_) == std::get<std::string>(other.value_);
                case 2:
                    return *std::get<std::unique_ptr<JsonArray>>(this->value_) == *std::get<std::unique_ptr<JsonArray>>(other.value_);
                case 3:
                    return *std::get<std::unique_ptr<JsonObject>>(this->value_) == *std::get<std::unique_ptr<JsonObject>>(other.value_);
                case 4:
                    return std::get<double>(this->value_) == std::get<double>(other.value_);
                case 5:
                    return std::get<bool>(this->value_) == std::get<bool>(other.value_);
                break;

                default:
                    return false;
            }
        }
};
