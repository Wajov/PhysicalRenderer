#ifndef SPECULAR_TRANSMISSION_H
#define SPECULAR_TRANSMISSION_H

#include <Eigen/Dense>

#include "MaterialHelper.h"
#include "spectrum/RGBSpectrum.h"
#include "BxDF.h"
#include "DielectricFresnel.h"

class SpecularTransmission : public BxDF {
private:
    RGBSpectrum T;
    float etaA, etaB;
    TransportMode mode;

public:
    SpecularTransmission(const RGBSpectrum& T, float etaA, float etaB, TransportMode mode);
    ~SpecularTransmission();
    RGBSpectrum f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
    RGBSpectrum sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) override;
    float pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
};

#endif