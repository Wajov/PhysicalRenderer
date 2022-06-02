#ifndef DIELECTRIC_FRESNEL_H
#define DIELECTRIC_FRESNEL_H

#include <algorithm>
#include <cmath>

#include "MathHelper.h"
#include "MaterialHelper.h"
#include "spectrum/RGBSpectrum.h"
#include "Fresnel.h"

class DielectricFresnel : public Fresnel {
private:
    float etaI, etaT;

public:
    DielectricFresnel(float etaI, float etaT);
    ~DielectricFresnel();
    RGBSpectrum evaluate(float cosThetaI) const override;
};

#endif