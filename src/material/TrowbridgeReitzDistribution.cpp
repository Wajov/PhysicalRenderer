#include "TrowbridgeReitzDistribution.h"

TrowbridgeReitzDistribution::TrowbridgeReitzDistribution(float alphaX, float alphaY, bool sampleVisibleArea) :
    MicrofacetDistribution(sampleVisibleArea),
    alphaX(std::max(0.001f, alphaX)),
    alphaY(std::max(0.001f, alphaY)) {}

TrowbridgeReitzDistribution::~TrowbridgeReitzDistribution() {}

float TrowbridgeReitzDistribution::D(const Eigen::Vector3f& wh) const {
    float tan2 = tan2Theta(wh);
    if (std::isinf(tan2))
        return 0.0f;

    float cos4 = sqr(cos2Theta(wh));
    float e = tan2 * (cos2Phi(wh) / sqr(alphaX) + sin2Phi(wh) / sqr(alphaY));
    return 1.0f / (PI * alphaX * alphaY * cos4 * sqr(1.0f + e));
}

float TrowbridgeReitzDistribution::lambda(const Eigen::Vector3f& w) const {
    float absTan = std::abs(tanTheta(w));
    if (std::isinf(absTan))
        return 0.0f;

    float alpha = std::sqrt(cos2Phi(w) * sqr(alphaX) + sin2Phi(w) * sqr(alphaY));
    return 0.5f * (-1.0f + std::sqrt(1.0f + sqr(alpha * absTan)));
}

Eigen::Vector3f TrowbridgeReitzDistribution::sample(const Eigen::Vector3f& wo, const Eigen::Vector2f& u) const {
    // TODO
}
