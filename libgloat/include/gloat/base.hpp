#pragma once

extern "C" {

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WEAK __attribute__((weak))

#define GL_GLEXT_PROTOTYPES
#define EGLAPI WEAK
#define GLAPI WEAK

uint32_t svcOutputDebugString(const char *str, uint64_t size);

#define debug_log(...)                                  \
    {                                                   \
        char log_buf[0x200];                            \
        snprintf(log_buf, 0x200, __VA_ARGS__);          \
        svcOutputDebugString(log_buf, strlen(log_buf)); \
    }
}
