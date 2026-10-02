#include "cow_string.hpp"
#include <cstring>
#include <cstdlib>

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