#ifndef LAMBERTIAN_TRANSMISSION_H
#define LAMBERTIAN_TRANSMISSION_H

#include "MathHelper.h"
#include "MaterialHelper.h"
#include "SampleHelper.h"
#include "spectrum/RGBSpectrum.h"
#include "BxDF.h"

class LambertianTransmission : public BxDF {
private:
    RGBSpectrum T;

public:
    LambertianTransmission(const RGBSpectrum& T);
    ~LambertianTransmission();
    RGBSpectrum f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
    RGBSpectrum sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) override;
    float pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
    RGBSpectrum rho(const Eigen::Vector3f& wo, int nSamples, const Eigen::Vector2f* samples) const override;
    RGBSpectrum rho(int nSamples, const Eigen::Vector2f* sample1, const Eigen::Vector2f* sample2) const override;
};

#endif