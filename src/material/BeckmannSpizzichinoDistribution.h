#ifndef BECKMANN_SPIZZICHINO_DISTRIBUTION_H
#define BECKMANN_SPIZZICHINO_DISTRIBUTION_H

#include <algorithm>

#include "MicrofacetDistribution.h"

class BeckmannSpizzichinoDistribution : public MicrofacetDistribution {
private:
    float alphaX, alphaY;

public:
    BeckmannSpizzichinoDistribution(float alphaX, float alphaY, bool sampleVisibleArea = true);
    ~BeckmannSpizzichinoDistribution();
    float D(const Eigen::Vector3f& wh) const override;
    float lambda(const Eigen::Vector3f& w) const override;
    Eigen::Vector3f sample(const Eigen::Vector3f& wo, const Eigen::Vector2f& u) const override;
};

#endif