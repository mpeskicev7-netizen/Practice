#include "json_value.hpp"

JsonValue::JsonValue() : value_(nullptr) {}
JsonValue::JsonValue(double data) : value_(data) {}
JsonValue::JsonValue(std::string data) : value_(std::move(data)) {}
JsonValue::JsonValue(std::nullptr_t) : value_(nullptr) {}
JsonValue::JsonValue(bool data) : value_(data) {}
JsonValue::JsonValue(JsonArray&& arr) : value_(std::make_unique<JsonArray>(std::move(arr))) {}
JsonValue::JsonValue(JsonObject&& obj) : value_(std::make_unique<JsonObject>(std::move(obj))) {}

double JsonValue::getDouble() const {
    if (!is_double()) {
        throw std::runtime_error("Expected double, but got something else");
    }
    return std::get<double>(value_);
}

std::string JsonValue::getString() const {
    if (!is_string()) {
        throw std::runtime_error("Expected string");
    }
    return std::get<std::string>(value_);
}

bool JsonValue::getBool() const {
    if (!is_bool()) {
        throw std::runtime_error("Expected bool");
    }
    return std::get<bool>(value_);
}

const JsonArray& JsonValue::getJsonArray() const {
    if (!is_array()) {
        throw std::runtime_error("Expected array");
    }
    return *std::get<std::unique_ptr<JsonArray>>(value_);
}

const JsonObject& JsonValue::getJsonObject() const {
    if (!is_object()) {
        throw std::runtime_error("Expected object");
    }
    return *std::get<std::unique_ptr<JsonObject>>(value_);
}

bool JsonValue::operator==(const JsonValue& other) const {
    if (this->value_.index() != other.value_.index()) {
        return false;
    }

    switch(value_.index()) {
        case 0: // nullptr_t
            return true;
        case 1: // std::string
            return std::get<std::string>(this->value_) == std::get<std::string>(other.value_);
        case 2: // std::unique_ptr<JsonArray>
            return *std::get<std::unique_ptr<JsonArray>>(this->value_) == *std::get<std::unique_ptr<JsonArray>>(other.value_);
        case 3: // std::unique_ptr<JsonObject>
            return *std::get<std::unique_ptr<JsonObject>>(this->value_) == *std::get<std::unique_ptr<JsonObject>>(other.value_);
        case 4: // double
            return std::get<double>(this->value_) == std::get<double>(other.value_);
        case 5: // bool
            return std::get<bool>(this->value_) == std::get<bool>(other.value_);
        default:
            return false;
    }
}