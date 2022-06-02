#include "LambertianTransmission.h"

LambertianTransmission::LambertianTransmission(const RGBSpectrum& T) :
    BxDF(BxDFType(BXDF_TRANSMISSION | BXDF_DIFFUSE)),
    T(T) {}

LambertianTransmission::~LambertianTransmission() {}

RGBSpectrum LambertianTransmission::f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return INV_PI * T;
}

RGBSpectrum LambertianTransmission::sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) {
    wi = cosineSampleHemisphere(u);
    if (wo.z() > 0.0f)
        wi.z() = -wi.z();
    pdf = this->pdf(wo, wi);
    return INV_PI * T;
}

float LambertianTransmission::pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return sameHemisphere(wo, wi) ? INV_PI * absCosTheta(wi) : 0.0f;
}

RGBSpectrum LambertianTransmission::rho(const Eigen::Vector3f& wo, int nSamples, const Eigen::Vector2f* samples) const {
    return T;
}

RGBSpectrum LambertianTransmission::rho(int nSamples, const Eigen::Vector2f* sample1, const Eigen::Vector2f* sample2) const {
    return T;
}
