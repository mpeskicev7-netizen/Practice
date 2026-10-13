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
    SmallVector() : heap_ptr(nullptr), size_(0), capacity_(N), is_heap_(false) {

    }

    ~SmallVector() {
        for (size_t i = 0; i < size_; i++) {
            if (is_heap_) {
                T* temp_ptr = reinterpret_cast<T*>(heap_ptr);
                temp_ptr[i].~T();
            }
            else {
                T* temp_data = reinterpret_cast<T*>(inline_data);
                temp_data[i].~T();
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
            T* temp_ptr = reinterpret_cast<T*>(heap_ptr) + size_;
            new (temp_ptr) T(value);
        }
        else {
            T* temp_data = reinterpret_cast<T*>(inline_data) + size_;
            new (temp_data) T(value);
        }

        size_++;
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw out_of_range("Index out of bounds");
        }

        if (is_heap_) {
            T* temp_ptr = reinterpret_cast<T*>(heap_ptr);
            return temp_ptr[index];
        }
        else {
            T* temp_data = reinterpret_cast<T*>(inline_data);
            return temp_data[index];
        }
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw out_of_range("Index out of bounds");
        }

        if (is_heap_) {
            T* temp_ptr = reinterpret_cast<T*>(heap_ptr);
            return temp_ptr[index];
        }
        else {
            T* temp_data = reinterpret_cast<T*>(inline_data);
            return temp_data[index];
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
                T* old_data = reinterpret_cast<T*>(other.inline_data) + i;
                T* new_data = reinterpret_cast<T*>(inline_data) + i; 
                new (new_data) T(move(*old_data));
                old_data->~T();
            }

            size_ = other.size_;
            capacity_ = other.capacity_;
            is_heap_ = false;

            other.size_ = 0;
        }
    }

    SmallVector& operator=(SmallVector&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        if (is_heap_) {
            for (size_t i = 0; i < size_; i++) {
                T* temp_ptr = reinterpret_cast<T*>(heap_ptr);
                temp_ptr[i].~T();
            }
        }
        else {
            for (size_t i = 0; i < size_; i++) {
                T* temp_data = reinterpret_cast<T*>(inline_data);
                temp_data[i].~T();
            }
        }

        if (is_heap_) {
            delete[] heap_ptr;
        }

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
                T* old_data = reinterpret_cast<T*>(other.inline_data) + i;
                T* new_data = reinterpret_cast<T*>(inline_data) + i; 
                new (new_data) T(move(*old_data));
                old_data->~T();
            }

            size_ = other.size_;
            capacity_ = other.capacity_;
            is_heap_ = false;

            other.size_ = 0;
        }

        return *this;
    }

    SmallVector(const SmallVector& other) {
        if (other.is_heap_) {
            char* new_heap = new char[sizeof(T) * other.capacity_];

            T* temp_ptr = reinterpret_cast<T*>(new_heap);
            for (size_t i = 0; i < other.size_; i++) {
                T* old_ptr = reinterpret_cast<T*>(other.heap_ptr) + i;
                new (&temp_ptr[i]) T(*old_ptr);
            }

            size_ = other.size_;
            capacity_ = other.capacity_;
            is_heap_ = true;
        }
        else {
            for (size_t i = 0; i < other.size_; i++) {
                T* old_data = reinterpret_cast<T*>(other.inline_data) + i;
                T* new_data = reinterpret_cast<T*>(inline_data) + i;
                new (new_data) T(*old_data);
            }

            size_ = other.size_;
            capacity_ = N;
            is_heap_ = false;
        }
    }

    SmallVector& operator=(const SmallVector& other) {
        if (this == &other) {
            return *this;
        }

        if (is_heap_) {
            for (size_t i = 0; i < size_; i++) {
                T* temp_ptr = reinterpret_cast<T*>(heap_ptr);
                temp_ptr[i].~T();
            }
        }
        else {
            for (size_t i = 0; i < size_; i++) {
                T* temp_data = reinterpret_cast<T*>(inline_data);
                temp_data[i].~T();
            }
        }

        if (is_heap_) {
            delete[] heap_ptr;
        }

        if (other.is_heap_) {
            char* new_heap = new char[sizeof(T) * other.capacity_];

            T* temp_ptr = reinterpret_cast<T*>(new_heap);
            for (size_t i = 0; i < other.size_; i++) {
                const T* old_ptr = reinterpret_cast<const T*>(other.heap_ptr) + i;
                new (&temp_ptr[i]) T(*old_ptr);
            }

            heap_ptr = new_heap;
            size_ = other.size_;
            capacity_ = other.capacity_;
            is_heap_ = true;
        }
        else {
            for (size_t i = 0; i < other.size_; i++) {
                const T* old_data = reinterpret_cast<const T*>(other.inline_data) + i;
                T* new_data = reinterpret_cast<T*>(inline_data) + i;
                new (new_data) T(*old_data);
            }

            size_ = other.size_;
            capacity_ = N;
            is_heap_ = false;
        }

        return *this;
    }
};