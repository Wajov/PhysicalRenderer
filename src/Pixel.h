#ifndef PIXEL_H
#define PIXEL_H

#include "spectrum/XYZSpectrum.h"

class Pixel {
public:
    float filterWeightSum;
    XYZSpectrum spectrumSum;
    Pixel();
    ~Pixel();
};

#endif