#include "XYZSpectrum.h"

XYZSpectrum::XYZSpectrum(float v) :
    Spectrum<3>(v) {}

XYZSpectrum::XYZSpectrum(const Spectrum<3>& p) :
    Spectrum<3>(p) {}

XYZSpectrum::~XYZSpectrum() {}

Spectrum<3> XYZSpectrum::toRGB() const {
    Spectrum<3> ans;
    ans[0] = 3.240479f * c[0] - 1.537150f * c[1] - 0.498535f * c[2];
    ans[1] = -0.969256f * c[0] + 1.875991f * c[1] + 0.041556f * c[2];
    ans[2] = 0.055648f * c[0] - 0.204043f * c[1] + 1.057311f * c[2];
    return ans;
}
