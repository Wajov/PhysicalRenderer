#include "OrenNayarReflection.h"

OrenNayarReflection::OrenNayarReflection(const RGBSpectrum& R, float sigma) :
    BxDF(BxDFType(BXDF_REFLECTION | BXDF_DIFFUSE)),
    R(R) {
    sigma = radian(sigma);
    float sigma2 = sqr(sigma);
    A = 1.0f - sigma2 / (2.0f * sigma2 + 0.33f);
    B = 0.45f * sigma2 / (sigma2 + 0.09f);
}

OrenNayarReflection::~OrenNayarReflection() {}

RGBSpectrum OrenNayarReflection::f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {;
    float sinThetaI = sinTheta(wi);
    float sinThetaO = sinTheta(wo);

    float maxCos = 0.0f;
    if (sinThetaO > 1e-4 && sinThetaI > 1e-4) {
        float cosPhiI = cosPhi(wi);
        float sinPhiI = sinPhi(wi);
        float cosPhiO = cosPhi(wo);
        float sinPhiO = sinPhi(wo);
        float dCos = cosPhiI * cosPhiO + sinPhiI * sinPhiO;
        maxCos = std::max(0.0f, dCos);
    }

    float sinAlpha, tanBeta;
    if (absCosTheta(wi) > absCosTheta(wo)) {
        sinAlpha = sinThetaO;
        tanBeta = sinThetaI / absCosTheta(wi);
    } else {
        sinAlpha = sinThetaI;
        tanBeta = sinThetaO / absCosTheta(wo);
    }

    return R * INV_PI * (A + B * maxCos * sinAlpha * tanBeta);
}
