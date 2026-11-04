#pragma once

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
    public:
        
};
