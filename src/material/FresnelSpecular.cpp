#include "FresnelSpecular.h"

FresnelSpecular::FresnelSpecular(const RGBSpectrum& R, const RGBSpectrum& T, float etaA, float etaB, TransportMode mode) :
    BxDF(BxDFType(BXDF_REFLECTION | BXDF_TRANSMISSION | BXDF_SPECULAR)),
    R(R),
    T(T),
    etaA(etaA),
    etaB(etaB),
    mode(mode) {}

FresnelSpecular::~FresnelSpecular() {}

RGBSpectrum FresnelSpecular::f(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return RGBSpectrum(0.0f);
}

RGBSpectrum FresnelSpecular::sample(const Eigen::Vector3f& wo, Eigen::Vector3f& wi, const Eigen::Vector2f& u, float& pdf, BxDFType* type) {
    float F = dielectricFresnel(etaA, etaB, cosTheta(wo));
    if (u[0] < F) {
        wi = Eigen::Vector3f(-wo.x(), -wo.y(), wo.z());
        if (type != nullptr)
            *type = BxDFType(BXDF_REFLECTION | BXDF_SPECULAR);
        pdf = F;
        return F * R / absCosTheta(wi);
    } else {
        bool entering = cosTheta(wo) > 0.0f;
        float etaI = entering ? etaA : etaB;
        float etaT = entering ? etaB : etaA;

        if (!refract(wo, faceForward(Eigen::Vector3f(0.0f, 0.0f, 1.0f), wo), etaI / etaT, wi))
            return RGBSpectrum(0.0f);

        RGBSpectrum ft = T * (1.0f - F);
        if (mode == RADIANCE)
            ft *= sqr(etaI) / sqr(etaT);
        if (type != nullptr)
            *type = BxDFType(BXDF_TRANSMISSION | BXDF_SPECULAR);
        pdf = 1.0f - F;
        return ft / absCosTheta(wi);
    }
}

float FresnelSpecular::pdf(const Eigen::Vector3f& wo, const Eigen::Vector3f& wi) const {
    return 0.0f;
}