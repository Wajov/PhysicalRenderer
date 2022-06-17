#ifndef RGB_SPECTRUM_H
#define RGB_SPECTRUM_H

#include "Spectrum.h"

class RGBSpectrum : public Spectrum<3> {
public:
    RGBSpectrum(float v = 0.0f);
    RGBSpectrum(const Spectrum<3>& p);
    ~RGBSpectrum();
    Spectrum<3> toXYZ() const;
};

#endif