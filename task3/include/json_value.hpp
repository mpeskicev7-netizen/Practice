#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <variant>
#include <stdexcept>

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
    JsonValue();
    JsonValue(double data);
    JsonValue(std::string data);
    JsonValue(std::nullptr_t);
    JsonValue(bool data);
    JsonValue(JsonArray&& arr);
    JsonValue(JsonObject&& obj);

    bool is_bool() const { return std::holds_alternative<bool>(value_); }
    bool is_double() const { return std::holds_alternative<double>(value_); }
    bool is_string() const { return std::holds_alternative<std::string>(value_); }
    bool is_null() const { return std::holds_alternative<std::nullptr_t>(value_); }
    bool is_array() const { return std::holds_alternative<std::unique_ptr<JsonArray>>(value_); }
    bool is_object() const { return std::holds_alternative<std::unique_ptr<JsonObject>>(value_); }

    double getDouble() const;
    std::string getString() const;
    bool getBool() const;
    const JsonArray& getJsonArray() const;
    const JsonObject& getJsonObject() const;

    bool operator==(const JsonValue& other) const;
};