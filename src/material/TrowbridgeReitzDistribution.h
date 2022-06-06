#ifndef TROWBRIDGE_REITZ_DISTRIBUTION_H
#define TROWBRIDGE_REITZ_DISTRIBUTION_H

#include "MicrofacetDistribution.h"

class TrowbridgeReitzDistribution : public MicrofacetDistribution {
private:
    float alphaX, alphaY;

public:
    TrowbridgeReitzDistribution(float alphaX, float alphaY, bool sampleVisibleArea = true);
    ~TrowbridgeReitzDistribution();
    float D(const Eigen::Vector3f& wh) const override;
    float lambda(const Eigen::Vector3f& w) const override;
    Eigen::Vector3f sample(const Eigen::Vector3f& wo, const Eigen::Vector2f& u) const override;
};

#endif