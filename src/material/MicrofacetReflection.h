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
    MicrofacetReflection(const RGBSpectrum& R, MicrofacetDistribution* distribution, Fresnel* fresnel);
    ~MicrofacetReflection();
    RGBSpectrum f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
    RGBSpectrum sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) override;
    float pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
};

#endif