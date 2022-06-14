#include "MicrofacetTransmission.h"

MicrofacetTransmission::MicrofacetTransmission(const RGBSpectrum& T, MicrofacetDistribution* distribution, float etaA, float etaB, TransportMode mode) :
    BxDF(BxDFType(BXDF_TRANSMISSION | BXDF_GLOSSY)),
    T(T),
    distribution(distribution),
    etaA(etaA),
    etaB(etaB),
    fresnel(new DielectricFresnel(etaA, etaB)),
    mode(mode) {}

MicrofacetTransmission::~MicrofacetTransmission() {}

RGBSpectrum MicrofacetTransmission::f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    if (sameHemisphere(wo, wi))
        return 0.0f;

    float cosThetaO = cosTheta(wo);
    float cosThetaI = cosTheta(wi);
    if (cosThetaO == 0.0f || cosThetaI == 0.0f)
        return RGBSpectrum(0.0f);

    float eta = cosTheta(wo) > 0.0f ? etaB / etaA : etaA / etaB;
    Eigen::Vector3f wh = (wo + wi * eta).normalized();
    if (wh.z() < 0.0f)
        wh = -wh;

    if (wo.dot(wh) * wi.dot(wh) > 0.0f)
        return RGBSpectrum(0.0f);

    RGBSpectrum F = fresnel->evaluate(wo.dot(wh));
    float t = wo.dot(wh) + eta * wi.dot(wh);
    float factor = mode == TransportMode::RADIANCE ? 1.0f / eta : 1.0f;

    return (RGBSpectrum(1.0f) - F) * T * std::abs(distribution->D(wh) * distribution->G(wo, wi) * sqr(eta) * std::abs(wi.dot(wh)) * std::abs(wo.dot(wh)) * sqr(factor) / (cosThetaO * cosThetaI * sqr(t)));
}

RGBSpectrum MicrofacetTransmission::sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) {
    if (wo.z() == 0.0f)
        return 0.0f;

    Eigen::Vector3f wh = distribution->sample(wo, u);
    if (wo.dot(wh) < 0.0f)
        return 0.0f;

    float eta = cosTheta(wo) > 0.0f ? etaA / etaB : etaB / etaA;
    if (!refract(wo, wh, eta, wi))
        return 0.0f;

    pdf = this->pdf(wo, wi);
    return f(wo, wi);
}

float MicrofacetTransmission::pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    if (sameHemisphere(wo, wi))
        return 0.0f;

    float eta = cosTheta(wo) > 0.0f ? etaB / etaA : etaA / etaB;
    Eigen::Vector3f wh = (wo + wi * eta).normalized();
    if (wo.dot(wh) * wi.dot(wh) > 0.0f)
        return 0.0f;

    float t = wo.dot(wh) + eta * wi.dot(wh);
    return distribution->pdf(wo, wh) * std::abs(sqr(eta) * wi.dot(wh) / sqr(t));
}
