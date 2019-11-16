#include <gloat.hpp>

char allocator_storage[sizeof(nn::mem::StandardAllocator)];

nn::mem::StandardAllocator* GetAllocator(void) {
    nn::mem::StandardAllocator* allocator =
        reinterpret_cast<nn::mem::StandardAllocator*>(allocator_storage);

    if (allocator->IsInitialized()) {
        return allocator;
    }

    return nullptr;
}

void* __custom_allocator(size_t size, size_t alignment) {
    nn::mem::StandardAllocator* allocator = GetAllocator();

    if (allocator != nullptr) {
        return allocator->Allocate(size, alignment);
    }

    return nullptr;
}

void __custom_deallocator(void* ptr, size_t size) {
    nn::mem::StandardAllocator* allocator = GetAllocator();
    if (allocator != nullptr) {
        allocator->Free(ptr);
    }
}

extern unsigned char __code_start__[];
extern unsigned char __code_end__[];
extern unsigned char __tdata_align_abs__[];
extern unsigned char __tdata_start__[];
extern unsigned char __tdata_end__[];
extern unsigned char __tbss_align_abs__[];
extern unsigned char __tbss_start__[];
extern unsigned char __tbss_end__[];
extern unsigned char __got_start__[];
extern unsigned char __got_end__[];
extern unsigned char __rela_dyn_start__[];
extern unsigned char __rela_dyn_end__[];

extern unsigned char __rel_dyn_start__[];
extern unsigned char __rel_dyn_end__[];

extern unsigned char __rela_plt_start__[];
extern unsigned char __rela_plt_end__[];

extern unsigned char __rel_plt_start__[];
extern unsigned char __rel_plt_end__[];

extern unsigned char _DYNAMIC[];

extern void (*__preinit_array_start__[])(void);
extern void (*__preinit_array_end__[])(void);
extern void (*__init_array_start__[])(void);
extern void (*__init_array_end__[])(void);
extern void (*__fini_array_start__[])(void);
extern void (*__fini_array_end__[])(void);

extern "C" int __nnmusl_init_dso(
    unsigned char* EX_start, unsigned char* EX_end, unsigned char* tdata_start,
    unsigned char* tdata_end, unsigned char* tdata_align_abs,
    unsigned char* tdata_align_rel, unsigned char* tbss_start,
    unsigned char* tbss_end, unsigned char* tbss_align_abs,
    unsigned char* tbss_align_rel, unsigned char* got_start,
    unsigned char* got_end, unsigned char* rela_dyn_start,
    unsigned char* rela_dyn_end, unsigned char* rel_dyn_start,
    unsigned char* rel_dyn_end, unsigned char* rela_plt_start,
    unsigned char* rela_plt_end, unsigned char* rel_plt_start,
    unsigned char* rel_plt_end, unsigned char* DYNAMIC);

extern "C" void __nnmusl_fini_dso(unsigned char* EX_start,
                                  unsigned char* EX_end,
                                  unsigned char* tdata_start,
                                  unsigned char* tdata_end,
                                  unsigned char* tbss_start,
                                  unsigned char* tbss_end);

static volatile int nnmuslTlsInitializationPhase = 0;

extern "C" void __custom_init(void) {
    // TODO?
    if (nnmuslTlsInitializationPhase == 0) {
        nnmuslTlsInitializationPhase = __nnmusl_init_dso(
            __code_start__, __code_end__, __tdata_start__, __tdata_end__,
            __tdata_align_abs__,  // tdata_align_abs
            __tdata_start__,      // tdata_align_rel
            __tbss_start__, __tbss_end__,
            __tdata_align_abs__,  // tbss_align_abs
            __tbss_start__,       // tbss_align_rel
            __got_start__, __got_end__, __rela_dyn_start__, __rela_dyn_end__,
            __rel_dyn_start__, __rel_dyn_end__, __rela_plt_start__,
            __rela_plt_end__, __rel_plt_start__, __rel_plt_end__, _DYNAMIC);
        if (nnmuslTlsInitializationPhase == 1) {
            return;
        }
    }

    for (void (**f)() = __preinit_array_start__; f < __preinit_array_end__;
         ++f) {
        (*f)();
    }

    for (void (**f)() = __init_array_start__; f < __init_array_end__; ++f) {
        (*f)();
    }
}

extern "C" void __custom_fini(void) {
    for (void (**f)() = __fini_array_start__; f < __fini_array_end__; ++f) {
        (*f)();
    }

    __nnmusl_fini_dso(__code_start__, __code_end__, __tdata_start__,
                      __tdata_end__, __tbss_start__, __tbss_end__);
}

extern "C" size_t __gloat_get_heap_size() { return 0; }

extern volatile void* heap_address;
extern volatile size_t heap_size;
extern "C" void setupNewLibHeap(void);

extern "C" WEAK void nninitStartup(void) {
    // Clean up some stuffs to make sure that we don't catch garbage
    heap_address = nullptr;
    heap_size = 0;

    setupNewLibHeap();

    debug_log("Hello from nninitStartup");

    nn::os::MemoryInfo memoryInfo;
    nn::os::QueryMemoryInfo(&memoryInfo);

    // heap_size = (memoryInfo.availaible_size - memoryInfo.used_size) &
    // 0xFFFFFFFFFFE00000;
    heap_size = __gloat_get_heap_size();
    if (!heap_size) {
        heap_size = 0x200000 * 256;  // 512 MB
    }

    nn::Result result = nn::os::SetMemoryHeapSize(heap_size);
    if (!result.Ok()) {
        heap_size = 0x2000000;
        result = nn::os::SetMemoryHeapSize(heap_size);
        if (!result.Ok()) {
            debug_log("SetMemoryHeapSize: %x", result.GetValue());
            gloat::utils::Abort(&result);
        }
    }

    result = nn::os::AllocateMemoryBlock((uint64_t*)&heap_address, heap_size);
    if (!result.Ok()) {
        debug_log("AllocateMemoryBlock: %x", result.GetValue());
        gloat::utils::Abort(&result);
    }

    // We store the object in a plain char array because we don't want a
    // global constructor to destroy everything.
    // TODO: inplace new
    nn::mem::StandardAllocator new_allocator;
    new_allocator.Initialize((void*)heap_address, heap_size);
    memcpy(allocator_storage, &new_allocator,
           sizeof(nn::mem::StandardAllocator));

    nn::os::SetMemoryAllocatorForThreadLocal(__custom_allocator,
                                             __custom_deallocator);
}