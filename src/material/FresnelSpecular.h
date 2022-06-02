#ifndef FRESNEL_SPECULAR_H
#define FRESNEL_SPECULAR_H

#include <Eigen/Dense>

#include "MaterialHelper.h"
#include "spectrum/RGBSpectrum.h"
#include "BxDF.h"
#include "DielectricFresnel.h"

class FresnelSpecular : public BxDF {
private:
    RGBSpectrum R, T;
    float etaA, etaB;
    TransportMode mode;

public:
    FresnelSpecular(const RGBSpectrum& R, const RGBSpectrum& T, float etaA, float etaB, TransportMode mode);
    ~FresnelSpecular();
    RGBSpectrum f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
    RGBSpectrum sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) override;
    float pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
};

#endif