#include "SpecularReflection.h"

SpecularReflection::SpecularReflection(const RGBSpectrum& reflectance, const Fresnel* fresnel) :
        BxDF(BxDFType(BXDF_REFLECTION | BXDF_SPECULAR)),
        R(reflectance),
        fresnel((Fresnel*)fresnel) {}

SpecularReflection::~SpecularReflection() {}

RGBSpectrum SpecularReflection::f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return RGBSpectrum(0.0f);
}

RGBSpectrum SpecularReflection::sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) {
    wi = Eigen::Vector3f(-wo.x(), -wo.y(), wo.z());
    pdf = 1.0f;
    return fresnel->evaluate(cosTheta(wo)) * R / absCosTheta(wo);
}

float SpecularReflection::pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return 0.0f;
}
