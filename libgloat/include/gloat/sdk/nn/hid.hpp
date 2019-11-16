#pragma once

#include "hid/KeyboardState.hpp"

namespace nn {
namespace hid {
void InitializeKeyboard();
void GetKeyboardState(KeyboardState *state);
int GetKeyboardStates(KeyboardState *states, int count);
}  // namespace hid
}  // namespace nn