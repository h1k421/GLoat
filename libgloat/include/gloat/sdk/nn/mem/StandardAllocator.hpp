#pragma once

#include <cstddef>

namespace nn {
namespace mem {
class StandardAllocator {
    char is_init;
    char unknown[0x47];

   public:
    StandardAllocator();

    void Initialize(void* address, size_t size);

    void* Allocate(size_t size);

    void* Allocate(size_t size, size_t alignment);

    void* Reallocate(void* address, size_t size);

    void Free(void* address);

    // Custom stuffs
    bool IsInitialized(void) { return is_init != 0; }
};
}  // namespace mem
}  // namespace nn