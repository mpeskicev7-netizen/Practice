#pragma once

#include <cstddef>
#include <iosfwd>

class CowString {
    private:
    struct ControlBlock {
        mutable size_t ref_count;
        size_t size;
        char data[];
    };
    ControlBlock* block_;
    public:
    CowString(const char* str);
    ~CowString();
    CowString(const CowString& other);
    size_t size() const;
    const char* c_str() const;
    char operator[](size_t index) const;
    char& operator[](size_t index);
};