#ifndef XYZ_SPECTRUM_H
#define XYZ_SPECTRUM_H

#include "Spectrum.h"

class XYZSpectrum : public Spectrum<3> {
public:
    XYZSpectrum(float v = 0.0f);
    XYZSpectrum(const Spectrum<3>& p);
    ~XYZSpectrum();
    Spectrum<3> toRGB() const;
};

#endif