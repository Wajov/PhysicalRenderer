#include "RGBSpectrum.h"

RGBSpectrum::RGBSpectrum(float v) :
    Spectrum<3>(v) {}

RGBSpectrum::RGBSpectrum(const Spectrum<3>& p) :
    Spectrum<3>(p) {}

RGBSpectrum::~RGBSpectrum() {}

Spectrum<3> RGBSpectrum::toXYZ() const {
    Spectrum<3> ans;
    ans[0] = 0.412453f * c[0] + 0.357580f * c[1] + 0.180423f * c[2];
    ans[1] = 0.212671f * c[0] + 0.715160f * c[1] + 0.072169f * c[2];
    ans[2] = 0.019334f * c[0] + 0.119193f * c[1] + 0.950227f * c[2];
    return ans;
}
