#ifndef MICROFACET_DISTRIBUTION_H
#define MICROFACET_DISTRIBUTION_H

#include <cmath>

#include <Eigen/Dense>

#include "MaterialHelper.h"

class MicrofacetDistribution {
protected:
    bool sampleVisibleArea;

public:
    MicrofacetDistribution(bool sampleVisibleArea);
    ~MicrofacetDistribution();
    virtual float D(const Eigen::Vector3f& wh) const = 0;
    virtual float lambda(const Eigen::Vector3f& w) const = 0;
    float G1(const Eigen::Vector3f& w) const;
    float G(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const;
    virtual Eigen::Vector3f sample(const Eigen::Vector3f& wo, const Eigen::Vector2f& u) const = 0;
    float pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wh) const;
};

#endif