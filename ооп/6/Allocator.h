#pragma once

#include <memory>
#include "List.h"

template <typename T, size_t ALLOC_SIZE>
class Allocator {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using is_always_equal = std::false_type;

    Allocator(const Allocator&) = delete;
    Allocator(Allocator&&) = delete;

    template<class V>
    struct rebind {
        using other = Allocator<V, ALLOC_SIZE>;
    };

    Allocator() {
        size_t object_count = ALLOC_SIZE / sizeof(T);

        memory = reinterpret_cast<char*>(operator new(sizeof(T) * object_count));
        for (size_t i = 0; i < object_count; ++i) {
            free_blocks.Insert(free_blocks.end(), memory + sizeof(T) * i);
        }
    }

    ~Allocator() {
        operator delete(memory);
    }

    T* allocate(size_t size) {
        if (size > 1) {
            throw std::logic_error("This allocator cant do that");
        }
        if (free_blocks.Empty()) {
            throw std::bad_alloc();
        }
        T* temp = reinterpret_cast<T*>(*free_blocks.begin());
        free_blocks.Erase(free_blocks.begin());
        return temp;

    }

    void deallocate(T* ptr, size_t size) {
        if (size > 1) {
            throw std::logic_error("This allocator cant do that");
        }
        free_blocks.Insert(free_blocks.end(), reinterpret_cast<char*>(ptr));
    }

private:
    Containers::List<char*> free_blocks;
    char* memory;
};
