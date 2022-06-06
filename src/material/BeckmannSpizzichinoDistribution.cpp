#include "BeckmannSpizzichinoDistribution.h"

BeckmannSpizzichinoDistribution::BeckmannSpizzichinoDistribution(float alphaX, float alphaY, bool sampleVisibleArea) :
    MicrofacetDistribution(sampleVisibleArea),
    alphaX(std::max(0.001f, alphaX)),
    alphaY(std::max(0.001f, alphaY)) {}

BeckmannSpizzichinoDistribution::~BeckmannSpizzichinoDistribution() {}

float BeckmannSpizzichinoDistribution::D(const Eigen::Vector3f& wh) const {
    float tan2 = tan2Theta(wh);
    if (std::isinf(tan2))
        return 0.0f;

    float cos4 = sqr(cos2Theta(wh));
    float e = tan2 * (cos2Phi(wh) / sqr(alphaX) + sin2Phi(wh) / sqr(alphaY));
    return std::exp(-e) / (PI * alphaX * alphaY * cos4);
}

float BeckmannSpizzichinoDistribution::lambda(const Eigen::Vector3f& w) const {
    float absTan = std::abs(tanTheta(w));
    if (std::isinf(absTan))
        return 0.0f;

    float alpha = std::sqrt(cos2Phi(w) * sqr(alphaX) + sin2Phi(w) * sqr(alphaY));
    float a = 1.0f / (alpha * absTan);
    if (a >= 1.6f)
        return 0.0f;

    return (1.0f - 1.259f * a + 0.396f * sqr(a)) / (3.535f * a + 2.181f * sqr(a));
}

Eigen::Vector3f BeckmannSpizzichinoDistribution::sample(const Eigen::Vector3f& wo, const Eigen::Vector2f& u) const {
    // TODO
}
