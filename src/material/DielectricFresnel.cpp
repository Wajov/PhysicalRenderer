#include "DielectricFresnel.h"

DielectricFresnel::DielectricFresnel(float etaI, float etaT) :
    Fresnel(),
    etaI(etaI),
    etaT(etaT) {}

DielectricFresnel::~DielectricFresnel() {}

RGBSpectrum DielectricFresnel::evaluate(float cosThetaI) const {
    return RGBSpectrum(dielectricFresnel(etaI, etaT, cosThetaI));
}
