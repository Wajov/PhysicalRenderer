#ifndef SPECULAR_REFLECTION_H
#define SPECULAR_REFLECTION_H

#include <Eigen/Dense>

#include "MaterialHelper.h"
#include "spectrum/RGBSpectrum.h"
#include "BxDF.h"
#include "Fresnel.h"

class SpecularReflection : public BxDF {
private:
    RGBSpectrum R;
    Fresnel* fresnel;

public:
    SpecularReflection(const RGBSpectrum& reflectance, Fresnel* fresnel);
    ~SpecularReflection();
    RGBSpectrum f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
    RGBSpectrum sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) override;
    float pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
};

#endif