#pragma once

#include <cstddef>
#include <stdexcept>

using namespace std;

template <typename T, size_t N>

class SmallVector {
    private:
    union {
        alignas(T) char inline_data[sizeof(T) * N];
        char* heap_ptr;
    };
    size_t size_;
    size_t capacity_;
    bool is_heap_;

    void grow() {
        if (!is_heap_) {
            size_t new_capacity = capacity_ * 2;
            char* new_heap = new char[sizeof(T) * new_capacity];

            T* temp_ptr = reinterpret_cast<T*>(new_heap);
            for (size_t i = 0; i < size_; i++) {
                T* old_ptr = reinterpret_cast<T*>(inline_data) + i;
                new (&temp_ptr[i]) T(*old_ptr);
                old_ptr->~T();
            }

            heap_ptr = new_heap;
            capacity_ = new_capacity;
            is_heap_ = true;
        }
        else {
            size_t new_capacity = capacity_ * 2;
            char* new_heap = new char[sizeof(T) * new_capacity];

            T* new_heap_ptr = reinterpret_cast<T*>(new_heap);
            for (size_t i = 0; i < size_; i++) {
                T* old_heap = reinterpret_cast<T*>(heap_ptr) + i;
                new (&new_heap_ptr[i]) T(*old_heap);
                old_heap->~T();
            }

            delete[] heap_ptr;
            heap_ptr = new_heap;
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
            is_heap_ = true;

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
            is_heap_ = false;

            other.size_ = 0;
        }
    }
};