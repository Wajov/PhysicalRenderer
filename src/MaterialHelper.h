#ifndef MATERIAL_HELPER_H
#define MATERIAL_HELPER_H

#include <cmath>

#include <Eigen/Dense>

#include "MathHelper.h"
#include "spectrum/RGBSpectrum.h"

inline static float cosTheta(const Eigen::Vector3f& w) {
    return w.z();
}

inline static float absCosTheta(const Eigen::Vector3f& w) {
    return std::abs(w.z());
}

inline static float cos2Theta(const Eigen::Vector3f& w) {
    return sqr(w.z());
}

inline static float sin2Theta(const Eigen::Vector3f& w) {
    return 1.0f - cos2Theta(w);
}

inline static float sinTheta(const Eigen::Vector3f& w) {
    return std::sqrt(sin2Theta(w));
}

inline static float tanTheta(const Eigen::Vector3f& w) {
    return sinTheta(w) / cosTheta(w);
}

inline static float tan2Theta(const Eigen::Vector3f& w) {
    return sin2Theta(w) / cos2Theta(w);
}

inline static float cosPhi(const Eigen::Vector3f& w) {
    float sin = sinTheta(w);
    return sin == 0.0f ? 1.0f : std::clamp(w.x() / sin, -1.0f, 1.0f);
}

inline static float cos2Phi(const Eigen::Vector3f& w) {
    return sqr(cosPhi(w));
}

inline static float sinPhi(const Eigen::Vector3f& w) {
    float sin = sinTheta(w);
    return sin == 0.0f ? 0.0f : std::clamp(w.y() / sin, -1.0f, 1.0f);
}

inline static float sin2Phi(const Eigen::Vector3f& w) {
    return sqr(sinPhi(w));
}

inline static bool sameHemisphere(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) {
    return wo.z() * wi.z() > 0.0f;
}

inline static Eigen::Vector3f faceForward(const Eigen::Vector3f& n, const Eigen::Vector3f& v) {
    return n.dot(v) > 0.0f ? n : -n;
}

inline static bool refract(const Eigen::Vector3f& wi, const Eigen::Vector3f& n, float eta, Eigen::Vector3f& wt) {
    float cosThetaI = n.dot(wi);
    float sin2ThetaI = std::max(0.0f, 1.0f - sqr(cosThetaI));
    float sin2ThetaT = sqr(eta) * sin2ThetaI;

    if (sin2ThetaT >= 1.0f)
        return false;

    float cosThetaT = std::sqrt(1.0f - sin2ThetaT);
    wt = eta * -wi + (eta * cosThetaI - cosThetaT) * n;
    return true;
}

inline static float dielectricFresnel(float etaI, float etaT, float cosThetaI) {
    cosThetaI = std::clamp(cosThetaI, -1.0f, 1.0f);
    if (cosThetaI < 0.0f) {
        std::swap(etaI, etaT);
        cosThetaI = -cosThetaI;
    }

    float sinThetaI = std::sqrt(std::max(0.0f, 1.0f - sqr(cosThetaI)));
    float sinThetaT = etaI * sinThetaI / etaT;

    if (sinThetaT >= 1.0f)
        return 1.0f;

    float cosThetaT = std::sqrt(std::max(0.0f, 1.0f - sqr(sinThetaT)));
    float para = (etaT * cosThetaI - etaI * cosThetaT) / (etaT * cosThetaI + etaI * cosThetaT);
    float perp = (etaI * cosThetaI - etaT * cosThetaT) / (etaI * cosThetaI + etaT * cosThetaT);
    return 0.5f * (sqr(para) + sqr(perp));
}

inline static RGBSpectrum conductorFresnel(const RGBSpectrum& etaI, const RGBSpectrum& etaT, const RGBSpectrum& k, float cosThetaI) {
    cosThetaI = std::clamp(cosThetaI, -1.0f, 1.0f);
    RGBSpectrum eta = etaT / etaI;
    RGBSpectrum etaK = k / etaI;

    float cos2ThetaI = sqr(cosThetaI);
    float sin2ThetaI = 1.0f - cos2ThetaI;
    RGBSpectrum eta2 = sqr(eta);
    RGBSpectrum etaK2 = sqr(etaK);

    RGBSpectrum t0 = eta2 - etaK2 - RGBSpectrum(sin2ThetaI);
    RGBSpectrum a2PlusB2 = sqrt((sqr(t0) + 4.0f * eta2 * etaK2));
    RGBSpectrum t1 = a2PlusB2 + RGBSpectrum(cos2ThetaI);
    RGBSpectrum a = sqrt(0.5f * (a2PlusB2 + t0));
    RGBSpectrum t2 = 2.0f * cosThetaI * a;
    RGBSpectrum perp = (t1 - t2) / (t1 + t2);

    RGBSpectrum t3 = cos2ThetaI * a2PlusB2 + sqr(sin2ThetaI);
    RGBSpectrum t4 = t2 * sin2ThetaI;
    RGBSpectrum para = perp * (t3 - t4) / (t3 + t4);

    return 0.5f * (para + perp);
}

#endif