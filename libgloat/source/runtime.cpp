#include <cstddef>
#include <gloat.hpp>

__attribute__((section(".bss"))) char __nx_module_runtime[0xD0];

// We setup newlib internal heap that may be used by it (printf, ect)
extern "C" void setupNewLibHeap(void* heap_start, size_t heap_size) {
    extern char* fake_heap_start;
    extern char* fake_heap_end;

    fake_heap_start = (char*)heap_start;
    fake_heap_end = (char*)heap_start + heap_size;
}

// Utils
void gloat::utils::Abort(nn::Result const* result) {
    nn::err::ShowError(*result);
    while (1)
        ;
}
