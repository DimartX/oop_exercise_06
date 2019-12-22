#pragma once

#include <cstdlib>
#include <cstdint>
#include <utility>

#include <exception>
#include <iostream>
#include <type_traits>

#include "vector.hpp"

template<class T, size_t BLOCK_SIZE>
struct my_allocator {
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using is_always_equal = std::false_type;

    template<class U>
    struct rebind {
        using other = my_allocator<U, BLOCK_SIZE>;
    };

    my_allocator():
        memory_pool_begin_(new char[BLOCK_SIZE]),
        memory_pool_end_(memory_pool_begin_ + BLOCK_SIZE),
        memory_pool_tail_(memory_pool_begin_)
    {}

    my_allocator(const my_allocator&) = delete;
    my_allocator(my_allocator&&) = delete;

    ~my_allocator() {
        delete[] memory_pool_begin_;
    }

    T* allocate(std::size_t n);
    void deallocate(T* ptr, std::size_t n);

private:
    size_t search_free_block(size_t n);
    
    char* memory_pool_begin_;
    char* memory_pool_end_;
    char* memory_pool_tail_;
    bad::TVector<std::pair<char*, size_t>> free_blocks_;
};

template<class T, size_t BLOCK_SIZE>
T* my_allocator<T, BLOCK_SIZE>::allocate(std::size_t n) {
    
    if(size_t(memory_pool_end_ - memory_pool_tail_) < sizeof(T) * n){
        if(!free_blocks_.empty()){
            size_t idx = search_free_block(n);
            char* ptr = free_blocks_[idx].first;
            free_blocks_.erase(idx);
            return reinterpret_cast<T*>(ptr);
        }
        throw std::bad_alloc();
    }
    else {
        T* result = reinterpret_cast<T*>(memory_pool_tail_);
        memory_pool_tail_ += n * sizeof(T);
        return result;
    }
    throw std::bad_alloc();
}

template<class T, size_t BLOCK_SIZE>
void my_allocator<T, BLOCK_SIZE>::deallocate(T* ptr, std::size_t n) {
    if(ptr == nullptr){
        return;
    }
    char* freePtr = reinterpret_cast<char*>(ptr);
    size_t freeSize = n * sizeof(T);
    free_blocks_.push_back(std::pair{freePtr, freeSize});
}

template<class T, size_t BLOCK_SIZE>
size_t my_allocator<T, BLOCK_SIZE>::search_free_block(size_t n) {
    for (size_t i = 0; i < free_blocks_.size(); i++) {
        if (free_blocks_[i].second >= n * sizeof(T))
            return i;
    }
    throw std::bad_alloc();
}
