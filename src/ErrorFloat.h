#ifndef ERROR_FLOAT_H
#define ERROR_FLOAT_H

#include <cstring>
#include <cmath>

#include "MathHelper.h"

class ErrorFloat {
private:
    float v, lower, upper;
    inline static u_int32_t floatToBits(float f);
    inline static float bitsToFloat(u_int32_t u);
    inline static float nextFloatDown(float v);
    inline static float nextFloatUp(float v);

public:
    ErrorFloat();
    ErrorFloat(float v, float err = 0.0f);
    ~ErrorFloat();
    float getLower() const;
    float getUpper() const;
    explicit operator float() const;
    ErrorFloat operator+(const ErrorFloat& f) const;
    ErrorFloat operator-(const ErrorFloat& f) const;
    ErrorFloat operator*(const ErrorFloat& f) const;
    ErrorFloat operator/(const ErrorFloat& f) const;
};

#endif