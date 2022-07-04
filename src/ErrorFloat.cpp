#include "ErrorFloat.h"

ErrorFloat::ErrorFloat() {}

ErrorFloat::ErrorFloat(float v, float err) :
    v(v) {
    if (err == 0.0f)
        lower = upper = v;
    else {
        lower = nextFloatDown(v - err);
        upper = nextFloatUp(v + err);
    }
}

ErrorFloat::~ErrorFloat() {}

u_int32_t ErrorFloat::floatToBits(float f) {
    u_int32_t u;
    memcpy(&u, &f, sizeof(float));
    return u;
}

float ErrorFloat::bitsToFloat(u_int32_t u) {
    float f;
    memcpy(&f, &u, sizeof(u_int32_t));
    return f;
}

float ErrorFloat::nextFloatDown(float v) {
    if (std::isinf(v) && v < 0.0f)
        return v;
    if (v == 0.0f)
        v = -0.0f;

    u_int32_t u = floatToBits(v);
    if (v > 0.0f)
        u--;
    else
        u++;

    return bitsToFloat(u);
}

float ErrorFloat::nextFloatUp(float v) {
    if (std::isinf(v) && v > 0.0f)
        return v;
    if (v == -0.0f)
        v = 0.0f;

    u_int32_t u = floatToBits(v);
    if (v >= 0.0f)
        u++;
    else
        u--;

    return bitsToFloat(u);
}

float ErrorFloat::getLower() const {
    return lower;
}

float ErrorFloat::getUpper() const {
    return upper;
}


ErrorFloat::operator float() const {
    return v;
}

ErrorFloat ErrorFloat::operator+(const ErrorFloat& f) const {
    ErrorFloat ans;
    ans.v = v + f.v;
    ans.lower = nextFloatDown(lower + f.lower);
    ans.upper = nextFloatUp(upper + f.upper);
    return ans;
}

ErrorFloat ErrorFloat::operator-(const ErrorFloat& f) const {
    ErrorFloat ans;
    ans.v = v - f.v;
    ans.lower = nextFloatDown(lower - f.upper);
    ans.upper = nextFloatUp(upper - f.lower);
    return ans;
}

ErrorFloat ErrorFloat::operator*(const ErrorFloat& f) const {
    ErrorFloat ans;
    ans.v = v * f.v;
    float t0 = lower * f.lower;
    float t1 = lower * f.upper;
    float t2 = upper * f.lower;
    float t3 = upper * f.upper;
    ans.lower = std::min(std::min(t0, t1), std::min(t2, t3));
    ans.upper = std::max(std::max(t0, t1), std::max(t2, t3));
}

ErrorFloat ErrorFloat::operator/(const ErrorFloat& f) const {
    ErrorFloat ans;
    ans.v = v / f.v;
    if (f.lower < 0.0f && f.upper > 0.0f) {
        ans.lower = -INF;
        ans.upper = INF;
    } else {
        float t0 = lower / f.lower;
        float t1 = lower / f.upper;
        float t2 = upper / f.lower;
        float t3 = upper / f.upper;
        ans.lower = std::min(std::min(t0, t1), std::min(t2, t3));
        ans.upper = std::max(std::max(t0, t1), std::max(t2, t3));
    }
    return ans;
}
