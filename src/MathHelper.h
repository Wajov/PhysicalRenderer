#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <cmath>

const float PI = 3.14159265358979323846f;
const float INV_PI = 1.0f / PI;
const float PI_OVER_2 = 0.5f * PI;
const float PI_OVER_4 = 0.25f * PI;

template <typename T> inline static T sqr(T x) {
    return x * x;
}

inline static float radian(float degree) {
    return PI / 180.0f * degree;
}

inline static float degree(float radian) {
    return 180.0f / PI * radian;
}

#endif