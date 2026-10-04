#include "cow_string.hpp"
#include <cstring>
#include <cstdlib>
#include <stdexcept>

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