#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <functional>
#include "json_value.hpp"
#include "path.hpp"

bool throws(std::function<void()> fn) {
    try {
        fn();
    } catch (const std::exception&) {
        return true;
    }
    return false;
}

void test_root_only() {
    std::cout << "Running test_root_only...\n";

    JsonObject obj;
    obj["a"] = JsonValue(1.0);
    JsonValue root(std::move(obj));

    Path path(root, "$");
    const JsonValue& result = path.execute();

    assert(result.is_object());
    assert(&result == &root); 

    std::cout << "test_root_only PASSED\n\n";
}

void test_simple_key() {
    std::cout << "Running test_simple_key...\n";

    JsonObject obj;
    obj["name"] = JsonValue(std::string("Vasya"));
    obj["age"] = JsonValue(25.0);
    JsonValue root(std::move(obj));

    Path path(root, "$.name");
    const JsonValue& result = path.execute();

    assert(result.is_string());
    assert(result.getString() == "Vasya");

    std::cout << "test_simple_key PASSED\n\n";
}

void test_nested_keys() {
    std::cout << "Running test_nested_keys...\n";

    JsonObject inner;
    inner["c"] = JsonValue(42.0);

    JsonObject mid;
    mid["b"] = JsonValue(std::move(inner));

    JsonObject root_obj;
    root_obj["a"] = JsonValue(std::move(mid));

    JsonValue root(std::move(root_obj));

    Path path(root, "$.a.b.c");
    const JsonValue& result = path.execute();

    assert(result.is_double());
    assert(result.getDouble() == 42.0);

    std::cout << "test_nested_keys PASSED\n\n";
}

void test_root_array_index() {
    std::cout << "Running test_root_array_index...\n";

    JsonArray arr;
    arr.push_back(JsonValue(10.0));
    arr.push_back(JsonValue(20.0));
    arr.push_back(JsonValue(30.0));
    JsonValue root(std::move(arr));

    Path path(root, "$[1]");
    const JsonValue& result = path.execute();

    assert(result.is_double());
    assert(result.getDouble() == 20.0);

    std::cout << "test_root_array_index PASSED\n\n";
}

void test_mixed_path() {
    std::cout << "Running test_mixed_path...\n";

    JsonObject user1;
    user1["name"] = JsonValue(std::string("Alice"));

    JsonObject user2;
    user2["name"] = JsonValue(std::string("Bob"));

    JsonArray users;
    users.push_back(JsonValue(std::move(user1)));
    users.push_back(JsonValue(std::move(user2)));

    JsonObject root_obj;
    root_obj["users"] = JsonValue(std::move(users));
    JsonValue root(std::move(root_obj));

    Path first(root, "$.users[0].name");
    assert(first.execute().getString() == "Alice");

    Path second(root, "$.users[1].name");
    assert(second.execute().getString() == "Bob");

    std::cout << "test_mixed_path PASSED\n\n";
}

void test_nested_arrays() {
    std::cout << "Running test_nested_arrays...\n";

    JsonArray row0;
    row0.push_back(JsonValue(1.0));
    row0.push_back(JsonValue(2.0));

    JsonArray row1;
    row1.push_back(JsonValue(3.0));
    row1.push_back(JsonValue(4.0));

    JsonArray matrix;
    matrix.push_back(JsonValue(std::move(row0)));
    matrix.push_back(JsonValue(std::move(row1)));

    JsonObject root_obj;
    root_obj["matrix"] = JsonValue(std::move(matrix));
    JsonValue root(std::move(root_obj));

    Path path(root, "$.matrix[1][0]");
    const JsonValue& result = path.execute();

    assert(result.is_double());
    assert(result.getDouble() == 3.0);

    std::cout << "test_nested_arrays PASSED\n\n";
}

void test_leaf_types() {
    std::cout << "Running test_leaf_types...\n";

    JsonObject obj;
    obj["ok"] = JsonValue(true);
    obj["bad"] = JsonValue(false);
    obj["nothing"] = JsonValue(nullptr);
    obj["text"] = JsonValue(std::string("hi"));
    JsonValue root(std::move(obj));

    Path ok(root, "$.ok");
    assert(ok.execute().is_bool());
    assert(ok.execute().getBool() == true);

    Path bad(root, "$.bad");
    assert(bad.execute().getBool() == false);

    Path nothing(root, "$.nothing");
    assert(nothing.execute().is_null());

    Path text(root, "$.text");
    assert(text.execute().getString() == "hi");

    std::cout << "test_leaf_types PASSED\n\n";
}

void test_error_no_dollar() {
    std::cout << "Running test_error_no_dollar...\n";

    JsonObject obj;
    obj["a"] = JsonValue(1.0);
    JsonValue root(std::move(obj));

    assert(throws([&] {
        Path path(root, "a");
        path.execute();
    }));

    std::cout << "test_error_no_dollar PASSED\n\n";
}

void test_error_missing_bracket() {
    std::cout << "Running test_error_missing_bracket...\n";

    JsonArray arr;
    arr.push_back(JsonValue(1.0));
    JsonValue root(std::move(arr));

    assert(throws([&] {
        Path path(root, "$[0");
        path.execute();
    }));

    std::cout << "test_error_missing_bracket PASSED\n\n";
}

void test_error_unknown_key() {
    std::cout << "Running test_error_unknown_key...\n";

    JsonObject obj;
    obj["a"] = JsonValue(1.0);
    JsonValue root(std::move(obj));

    assert(throws([&] {
        Path path(root, "$.nope");
        path.execute();
    }));

    std::cout << "test_error_unknown_key PASSED\n\n";
}

void test_error_key_on_number() {
    std::cout << "Running test_error_key_on_number...\n";

    JsonArray arr;
    arr.push_back(JsonValue(1.0));
    arr.push_back(JsonValue(2.0));
    JsonValue root(std::move(arr));

    assert(throws([&] {
        Path path(root, "$[0].name");
        path.execute();
    }));

    std::cout << "test_error_key_on_number PASSED\n\n";
}

void test_error_index_on_object() {
    std::cout << "Running test_error_index_on_object...\n";

    JsonObject obj;
    obj["a"] = JsonValue(1.0);
    JsonValue root(std::move(obj));

    assert(throws([&] {
        Path path(root, "$[0]");
        path.execute();
    }));

    std::cout << "test_error_index_on_object PASSED\n\n";
}

void test_error_unexpected_char() {
    std::cout << "Running test_error_unexpected_char...\n";

    JsonObject obj;
    obj["a"] = JsonValue(1.0);
    JsonValue root(std::move(obj));

    assert(throws([&] {
        Path path(root, "$a");
        path.execute();
    }));

    std::cout << "test_error_unexpected_char PASSED\n\n";
}

void run_path_tests() {
    std::cout << "=== Starting Path Tests ===\n\n";

    test_root_only();
    test_simple_key();
    test_nested_keys();
    test_root_array_index();
    test_mixed_path();
    test_nested_arrays();
    test_leaf_types();
    test_error_no_dollar();
    test_error_missing_bracket();
    test_error_unknown_key();
    test_error_key_on_number();
    test_error_index_on_object();
    test_error_unexpected_char();

    std::cout << "================================\n";
    std::cout << "🎉 ALL PATH TESTS PASSED! 🎉\n";
    std::cout << "================================\n\n";
}