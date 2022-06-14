#include "Pixel.h"

Pixel::Pixel() :
    filterWeightSum(0.0f),
    xyz{0.0f, 0.0f, 0.0f},
    splatXYZ{0.0f, 0.0f, 0.0f} {}

Pixel::~Pixel() {}
