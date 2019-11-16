#pragma once

#include <cstdint>

namespace nn {
// custrom encapsulation of nn::Result
class Result {
    uint32_t value;

   public:
    Result(uint32_t value) : value(value) {}

    bool Ok() { return value == 0; }

    uint32_t GetValue() { return value; }

    void SetValue(uint32_t value) { this->value = value; }
};
}  // namespace nn