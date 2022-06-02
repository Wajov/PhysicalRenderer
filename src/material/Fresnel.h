#ifndef FRESNEL_H
#define FRESNEL_H

#include "spectrum/RGBSpectrum.h"

class Fresnel {
public:
    Fresnel();
    ~Fresnel();
    virtual RGBSpectrum evaluate(float cosThetaI) const = 0;
};

#endif