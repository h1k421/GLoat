#include <cstddef>
#include <gloat.hpp>

#define INNER_HEAP_SIZE 0x80000

size_t nx_inner_heap_size = INNER_HEAP_SIZE;
char nx_inner_heap[INNER_HEAP_SIZE];

volatile void* heap_address;
volatile size_t heap_size;

__attribute__((section(".bss"))) char __nx_module_runtime[0xD0];

// We setup newlib internal heap that may be used by it (printf, ect)
extern "C" void setupNewLibHeap(void) {
    void* addr = nx_inner_heap;
    size_t size = nx_inner_heap_size;

    extern char* fake_heap_start;
    extern char* fake_heap_end;

    fake_heap_start = (char*)addr;
    fake_heap_end = (char*)addr + size;
}

// Utils
void gloat::utils::Abort(nn::Result const* result) {
    nn::err::ShowError(*result);
    while (1)
        ;
}
