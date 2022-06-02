#include "LambertianReflection.h"

LambertianReflection::LambertianReflection(const RGBSpectrum& R) :
    BxDF(BxDFType(BXDF_REFLECTION | BXDF_DIFFUSE)),
    R(R) {}

LambertianReflection::~LambertianReflection() {}

RGBSpectrum LambertianReflection::f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return INV_PI * R;
}

RGBSpectrum LambertianReflection::sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) {
    wi = cosineSampleHemisphere(u);
    if (wo.z() < 0.0f)
        wi.z() = -wi.z();
    pdf = this->pdf(wo, wi);
    return INV_PI * R;
}

float LambertianReflection::pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return sameHemisphere(wo, wi) ? INV_PI * absCosTheta(wi) : 0.0f;
}

RGBSpectrum LambertianReflection::rho(const Eigen::Vector3f& wo, int nSamples, const Eigen::Vector2f* samples) const {
    return R;
}

RGBSpectrum LambertianReflection::rho(int nSamples, const Eigen::Vector2f* sample1, const Eigen::Vector2f* sample2) const {
    return R;
}
