#ifndef MICROFACET_TRANSMISSION_H
#define MICROFACET_TRANSMISSION_H

#include "BxDF.h"
#include "DielectricFresnel.h"
#include "MicrofacetDistribution.h"
#include "spectrum/RGBSpectrum.h"

class MicrofacetTransmission : public BxDF {
private:
    RGBSpectrum T;
    MicrofacetDistribution* distribution;
    float etaA, etaB;
    DielectricFresnel* fresnel;
    TransportMode mode;

public:
    MicrofacetTransmission(const RGBSpectrum& T, MicrofacetDistribution* distribution, float etaA, float etaB, TransportMode mode);
    ~MicrofacetTransmission();
    RGBSpectrum f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
    RGBSpectrum sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) override;
    float pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
};

#endif