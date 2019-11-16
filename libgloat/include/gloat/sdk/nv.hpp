#pragma once

#include <cstddef>

namespace nv {
// last parameter seems to be some user data pointer
void SetGraphicsAllocator(void* allocator(size_t, size_t, void*),
                          void deallocator(void*, void*),
                          void* rallocator(void*, size_t, void*), void* unk);
void SetGraphicsDevtoolsAllocator(void* allocator(size_t, size_t, void*),
                                  void deallocator(void*, void*),
                                  void* rallocator(void*, size_t, void*),
                                  void* unk);
void InitializeGraphics(void* address, size_t size);
}  // namespace nv