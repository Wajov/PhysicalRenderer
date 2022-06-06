#ifndef OREN_NAYAR_REFLECTION_H
#define OREN_NAYAR_REFLECTION_H

#include "MathHelper.h"
#include "MaterialHelper.h"
#include "BxDF.h"
#include "spectrum/RGBSpectrum.h"

class OrenNayarReflection : public BxDF {
private:
    RGBSpectrum R;
    float A, B;

public:
    OrenNayarReflection(const RGBSpectrum& R, float sigma);
    ~OrenNayarReflection();
    RGBSpectrum f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const override;
};

#endif