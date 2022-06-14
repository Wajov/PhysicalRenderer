#include "MicrofacetReflection.h"

MicrofacetReflection::MicrofacetReflection(const RGBSpectrum& R, MicrofacetDistribution* distribution, Fresnel* fresnel) :
    BxDF(BxDFType(BXDF_REFLECTION | BXDF_GLOSSY)),
    R(R),
    distribution(distribution),
    fresnel(fresnel) {}

MicrofacetReflection::~MicrofacetReflection() {}

RGBSpectrum MicrofacetReflection::f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    float cosThetaO = absCosTheta(wo);
    float cosThetaI = absCosTheta(wi);
    Eigen::Vector3f wh = wi + wo;
    if (cosThetaO == 0.0f || cosThetaI == 0.0f)
        return RGBSpectrum(0.0f);
    if (wh == Eigen::Vector3f::Zero())
        return RGBSpectrum(0.0f);

    wh = wh.normalized();
    RGBSpectrum F = fresnel->evaluate(wo.dot(faceForward(wh, Eigen::Vector3f(0.0f, 0.0f ,1.0f))));
    return R * distribution->D(wh) * distribution->G(wo, wi) * F / (4.0f * cosThetaO * cosThetaI);
}

RGBSpectrum MicrofacetReflection::sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) {
    if (wo.z() == 0.0f)
        return 0.0f;

    Eigen::Vector3f wh = distribution->sample(wo, u);
    if (wo.dot(wh) < 0.0f)
        return RGBSpectrum(0.0f);

    wi = reflect(wo, wh);
    if (!sameHemisphere(wo, wi))
        return RGBSpectrum(0.0f);

    pdf = distribution->pdf(wo, wh) / (4.0f * wo.dot(wh));
    return f(wo, wi);
}

float MicrofacetReflection::pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    if (!sameHemisphere(wo, wi))
        return 0.0f;

    Eigen::Vector3f wh = (wo + wi).normalized();
    return distribution->pdf(wo, wh) / (4.0f * wo.dot(wh));
}
