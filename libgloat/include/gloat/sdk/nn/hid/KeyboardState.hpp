#pragma once

#include <cinttypes>

namespace nn {
namespace hid {
struct KeyboardState {
    int64_t samplerCount;
    int32_t modifiers;
    int32_t unk;
    uint32_t keys[0x8];
};

static_assert(sizeof(KeyboardState) == 0x30, "KeyboardState size is invalid");
}  // namespace hid
}  // namespace nn