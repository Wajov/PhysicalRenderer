#include "SpecularTransmission.h"

SpecularTransmission::SpecularTransmission(const RGBSpectrum& T, float etaA, float etaB, TransportMode mode) :
    BxDF(BxDFType(BXDF_TRANSMISSION | BXDF_SPECULAR)),
    T(T),
    etaA(etaA),
    etaB(etaB),
    mode(mode) {}

SpecularTransmission::~SpecularTransmission() {}

RGBSpectrum SpecularTransmission::f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return RGBSpectrum(0.0f);
}

RGBSpectrum SpecularTransmission::sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) {
    bool entering = cosTheta(wo) > 0.0f;
    float etaI = entering ? etaA : etaB;
    float etaT = entering ? etaB : etaA;

    if (!refract(wo, faceForward(Eigen::Vector3f(0.0f, 0.0f, 1.0f), wo), etaI / etaT, wi))
        return RGBSpectrum(0.0f);

    pdf = 1.0f;
    RGBSpectrum ft = T * (1.0f - dielectricFresnel(etaA, etaB, cosTheta(wi)));
    if (mode == RADIANCE)
        ft *= sqr(etaI) / sqr(etaT);

    return ft / absCosTheta(wi);
}

float SpecularTransmission::pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return 0.0f;
}
