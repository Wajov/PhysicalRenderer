#ifndef BXDF_H
#define BXDF_H

#include <Eigen/Dense>

#include "spectrum/RGBSpectrum.h"

enum BxDFType {
    BXDF_REFLECTION = 1 << 0,
    BXDF_TRANSMISSION = 1 << 1,
    BXDF_DIFFUSE = 1 << 2,
    BXDF_GLOSSY = 1 << 3,
    BXDF_SPECULAR = 1 << 4,
    BXDF_ALL = BXDF_REFLECTION | BXDF_TRANSMISSION | BXDF_DIFFUSE | BXDF_GLOSSY | BXDF_SPECULAR
};

enum TransportMode {
    RADIANCE,
    IMPORTANCE
};

class BxDF {
protected:
    BxDFType type;

public:
    BxDF(BxDFType type);
    ~BxDF();
    bool matchFlags(BxDFType type) const;
    virtual RGBSpectrum f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const = 0;
    virtual RGBSpectrum sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) = 0;
    virtual RGBSpectrum rho(const Eigen::Vector3f& wo, int nSamples, const Eigen::Vector2f* samples) const = 0;
    virtual RGBSpectrum rho(int nSamples, const Eigen::Vector2f* sample1, const Eigen::Vector2f* sample2) const = 0;
    virtual float pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const = 0;
};

#endif