#include "RGBSpectrum.h"

RGBSpectrum::RGBSpectrum(float v) :
    Spectrum<3>(v) {}

RGBSpectrum::RGBSpectrum(const Spectrum<3>& p) :
    Spectrum<3>(p) {}

RGBSpectrum::~RGBSpectrum() {}