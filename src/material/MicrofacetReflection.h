#ifndef MICROFACET_REFLECTION_H
#define MICROFACET_REFLECTION_H

#include "BxDF.h"
#include "Fresnel.h"
#include "MicrofacetDistribution.h"
#include "spectrum/RGBSpectrum.h"

class MicrofacetReflection : public BxDF {
private:
    RGBSpectrum R;
    MicrofacetDistribution* distribution;
    Fresnel* fresnel;

public:
    MicrofacetReflection(const RGBSpectrum& R, MicrofacetReflection* distribution, Fresnel* fresnel);
    ~MicrofacetReflection();

};

#endif