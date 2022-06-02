#ifndef CONDUCTOR_FRESNEL_H
#define CONDUCTOR_FRESNEL_H

#include <algorithm>

#include "MathHelper.h"
#include "MaterialHelper.h"
#include "spectrum/RGBSpectrum.h"
#include "Fresnel.h"

class ConductorFresnel : public Fresnel {
private:
    RGBSpectrum etaI, etaT, k;

public:
    ConductorFresnel(const RGBSpectrum& etaI, const RGBSpectrum& etaT, const RGBSpectrum& k);
    ~ConductorFresnel();
    RGBSpectrum evaluate(float cosThetaI) const override;
};

#endif