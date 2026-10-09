#pragma once

#include <cstddef>
#include <stdexcept>

using namespace std;

template <typename T, size_t N>

class SmallVector {
    private:
    union {
        T inline_data[N];
        T* heap_ptr;
    };
    size_t size_;
    size_t capacity_;
    bool is_heap_;

    void grow() {
        if (!is_heap_) {
            size_t new_capacity = capacity_ * 2;
            T* temp_ptr = new T[new_capacity];

            for (size_t i = 0; i < size_; i++) {
                temp_ptr[i] = inline_data[i];
            }

            heap_ptr = temp_ptr;
            is_heap_ = true;
            capacity_ = new_capacity;
        }
        else {
            size_t new_capacity = capacity_ * 2;
           T* new_heap_ptr = new T[new_capacity];

            for (size_t i = 0; i < size_; i++) {
                new_heap_ptr[i] = heap_ptr[i];
            }

            delete[] heap_ptr;
            heap_ptr = new_heap_ptr;
            capacity_ = new_capacity;
        }
    }
    public:
    SmallVector() : size_(0), capacity_(N), is_heap_(false) {

    }

    ~SmallVector() {
        for (size_t i = 0; i < size_; i++) {
            if (is_heap_) {
                heap_ptr[i].~T();
            }
            else {
                inline_data[i].~T();
            }
        }

        if (is_heap_) {
            delete[] heap_ptr;
        }
    }

    size_t size() const {return size_;}

    size_t capacity() const {return capacity_;}

    bool empty() const {return size_ == 0;}

    void push_back(const T& value) {
        if (size_ == capacity_) {
            grow();
        }

        if (is_heap_) {
            heap_ptr[size_] = value;
        }
        else {
            inline_data[size_] = value;
        }

        size_++;
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw out_of_range("Index out of bounds");
        }

        if (is_heap_) {
            return heap_ptr[index];
        }
        else {
            return inline_data[index];
        }
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw out_of_range("Index out of bounds");
        }

        if (is_heap_) {
            return heap_ptr[index];
        }
        else {
            return inline_data[index];
        }
    }

    SmallVector(SmallVector&& other) noexcept {
        if (other.is_heap_) {
            heap_ptr = other.heap_ptr;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.heap_ptr = nullptr;
            other.size_ = 0;
            other.is_heap_ = false;
        }
        else {
            for (size_t i = 0; i < other.size_; i++) {
                inline_data[i] = other.inline_data[i]; 
            }

            size_ = other.size_;
            capacity_ = other.capacity_;

            other.size_ = 0;
        }
    }
};