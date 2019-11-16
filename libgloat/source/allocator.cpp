#include <errno.h>

#include <gloat.hpp>

extern "C" int* __errno_location(void);

extern nn::mem::StandardAllocator* GetAllocator(void);

extern "C" void* malloc(size_t size) {
    void* ptr = nullptr;

    nn::mem::StandardAllocator* allocator = GetAllocator();

    if (allocator != nullptr) {
        ptr = allocator->Allocate(size);
        if (ptr == nullptr) {
            int* err = __errno_location();
            *err = ENOMEM;
        }
    }

    return ptr;
}

extern "C" void free(void* ptr) {
    nn::mem::StandardAllocator* allocator = GetAllocator();

    if (allocator != nullptr) {
        allocator->Free(ptr);
    }
}

extern "C" void* realloc(void* ptr, size_t size) {
    nn::mem::StandardAllocator* allocator = GetAllocator();

    if (allocator != nullptr) {
        ptr = allocator->Reallocate(ptr, size);
        if (ptr == nullptr) {
            int* err = __errno_location();
            *err = ENOMEM;
        }

        return ptr;
    }

    return nullptr;
}

extern "C" void* calloc(size_t n, size_t s) {
    void* ptr = nullptr;

    nn::mem::StandardAllocator* allocator = GetAllocator();

    if (allocator != nullptr) {
        ptr = allocator->Allocate(n * s);
    }

    if (ptr == nullptr) {
        int* err = __errno_location();
        *err = ENOMEM;
    }

    return ptr;
}

extern "C" void* aligned_alloc(size_t alignment, size_t size) {
    void* ptr = nullptr;

    nn::mem::StandardAllocator* allocator = GetAllocator();

    if (allocator != nullptr) {
        ptr = allocator->Allocate(size, alignment);
        if (ptr == nullptr) {
            int* err = __errno_location();
            *err = ENOMEM;
        }
    }

    return ptr;
}
