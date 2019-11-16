#pragma once

#include <cstddef>

#include "Result.hpp"

namespace nn {
namespace os {
struct MemoryInfo {
    size_t availaible_size;
    size_t used_size;
    char unk[0x28];  // TODO: reverse this?
};

void QueryMemoryInfo(MemoryInfo *memoryInfo);

nn::Result SetMemoryHeapSize(size_t heap_size);

nn::Result AllocateMemoryBlock(unsigned long *address, size_t size);

void SetMemoryAllocatorForThreadLocal(void *allocator(size_t, size_t),
                                      void deallocator(void *, size_t));
}  // namespace os
}  // namespace nn