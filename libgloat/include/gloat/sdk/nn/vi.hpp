#pragma once

#include "Result.hpp"

namespace nn {
namespace vi {
// everything is unknown about those structs, TODO: re
struct Display;

struct Layer;

enum ScalingMode {
    Unk0 = 0,
    Unk1 = 1,
    Unk2 = 2,
};

void Initialize();

nn::Result OpenDefaultDisplay(Display** out);

nn::Result CreateLayer(Layer** out, Display* display, int width, int height);

nn::Result SetLayerScalingMode(Layer* layer, ScalingMode mode);

nn::Result GetNativeWindow(void** nativeWindow, Layer* layout);
}  // namespace vi
}  // namespace nn