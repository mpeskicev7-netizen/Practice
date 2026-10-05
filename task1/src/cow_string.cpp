#include "cow_string.hpp"
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

CowString::CowString(const char* str) {
    if(!str) {
        str = "";
    }

    size_t len = strlen(str);
    size_t total = sizeof(ControlBlock) + len + 1;
    ControlBlock* block = static_cast<ControlBlock*>(malloc(total));

    block->ref_count = 1;
    block->size = len;
    memcpy(block->data, str, len + 1);
    block_ = block;
}

CowString::~CowString() {
    if(block_ == nullptr) {
        return;
    }
    
    block_->ref_count--;

    if (block_->ref_count == 0) {
        free(block_);
    }
}

CowString::CowString(const CowString& other) {
    block_ = other.block_;

    block_->ref_count++;
}

size_t CowString::size() const {
    if (block_) {
        return block_->size;
    }
    return 0;
}

const char* CowString::c_str() const {
    if (block_) {
        return block_->data;
    }
    return "";  
}

char CowString::operator[](size_t index) const {
    if (block_ == nullptr) {
        return '\0';
    }
    return block_->data[index];
}

char& CowString::operator[](size_t index) {
    if (block_ == nullptr) {
        throw runtime_error("Cannot access element of null string");
    }
    if (block_->ref_count > 1) {
        detach();
    }
    return block_->data[index];
}

void CowString::detach() {
    size_t size_copy = sizeof(ControlBlock) + block_->size + 1;
    ControlBlock* copy_block = static_cast<ControlBlock*>(malloc(size_copy));

    copy_block->ref_count = 1;
    copy_block->size = block_->size;
    memcpy(copy_block->data, block_->data, block_->size + 1);

    block_->ref_count--;
    if (block_->ref_count == 0) {
        free(block_);
    }

    block_ = copy_block;
}

CowString::CowString(CowString&& other) noexcept {
    block_ = other.block_;
    other.block_ = nullptr;
}

CowString& CowString::operator=(CowString&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    if (block_ != nullptr) {
        block_->ref_count--;
        if (block_->ref_count == 0) {
            free(block_);
            block_ = nullptr;  // ← ДОБАВЬ!
        }
    }

    block_ = other.block_;
    other.block_ = nullptr;

    return *this;
}

bool CowString::operator==(const CowString& other) const {
    if (block_ == other.block_) {
        return true;
    }

    if (this->size() != other.size()) {
        return false;
    }

    return memcmp(this->c_str(), other.c_str(), this->size()) == 0;
}

bool CowString::operator!=(const CowString& other) const {
    return !(this->operator==(other));
}

CowString& CowString::operator=(const CowString& other) {
    if (this == &other) {
        return *this;
    }

    if (block_ != nullptr) {
        block_->ref_count--;

        if (block_->ref_count == 0) {
            free(block_);
        }
    }

    block_ = other.block_;
    block_->ref_count++;

    return *this;
}

CowString& CowString::operator+=(const CowString& other) {
    if (this == &other) {
        CowString temp(other);
        return *this += temp;
    }

    if (block_ == nullptr) {
        *this = other;
        return *this;
    }

    if (block_->ref_count > 1) {
        detach();
    }

    size_t len = other.size();
    size_t new_size = sizeof(ControlBlock) + block_->size + len + 1;
    ControlBlock* new_block = static_cast<ControlBlock*>(malloc(new_size));

    new_block->ref_count = 1;
    new_block->size = block_->size + len;

    memcpy(new_block->data, block_->data, block_->size);
    memcpy(new_block->data + block_->size, other.block_->data, len + 1);

    free(block_);
    block_ = new_block;

    return *this;
}

CowString CowString::operator+(const CowString& other) const {
    CowString result(*this);
    result += other;
    return result;
}

std::ostream& operator<<(std::ostream& os, const CowString& str) {
    os << str.c_str();
    return os;
}