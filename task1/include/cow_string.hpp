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
    void detach();
    public:
    CowString(const char* str);
    ~CowString();
    CowString(const CowString& other);
    size_t size() const;
    const char* c_str() const;
    char operator[](size_t index) const;
    char& operator[](size_t index);
    bool operator==(const CowString& other) const;
    bool operator!=(const CowString& other) const;
    CowString(CowString&& other) noexcept;
    CowString& operator=(CowString&& other) noexcept;
    CowString& operator=(const CowString& other); 
    CowString& operator+=(const CowString& other);
    CowString operator+(const CowString& other) const;
    friend std::ostream& operator<<(std::ostream& os, const CowString& str);
};