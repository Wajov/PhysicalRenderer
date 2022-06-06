#include "MicrofacetDistribution.h"

MicrofacetDistribution::MicrofacetDistribution(bool sampleVisibleArea) :
    sampleVisibleArea(sampleVisibleArea) {}

MicrofacetDistribution::~MicrofacetDistribution() {}

float MicrofacetDistribution::G1(const Eigen::Vector3f& w) const {
    return 1.0f / (1.0f + lambda(w));
}

float MicrofacetDistribution::G(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return 1.0f / (1.0f + lambda(wo) + lambda(wi));
}

float MicrofacetDistribution::pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wh) const {
    if (sampleVisibleArea)
        return D(wh) * G1(wo) * std::abs(wo.dot(wh)) / absCosTheta(wo);
    else
        return D(wh) * absCosTheta(wo);
}
