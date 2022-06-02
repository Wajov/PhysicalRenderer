#include "BxDF.h"

BxDF::BxDF(BxDFType type) :
    type(type) {}

BxDF::~BxDF() {}

bool BxDF::matchFlags(BxDFType flags) const {
    return (type & flags) == type;
}