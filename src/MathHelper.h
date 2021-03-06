#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <cmath>

#include <Eigen/Dense>

const float INF = std::numeric_limits<float>::infinity();
const float MACHINE_EPSILON = std::numeric_limits<float>::epsilon() * 0.5f;
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

inline static Eigen::Vector3f abs(const Eigen::Vector3f& v) {
    return Eigen::Vector3f(std::abs(v.x()), std::abs(v.y()), std::abs(v.z()));
}

inline static Eigen::Vector2i floor(const Eigen::Vector2f& v) {
    return Eigen::Vector2i((int)std::floor(v.x()), (int)std::floor(v.y()));
}

inline static Eigen::Vector2i ceil(const Eigen::Vector2f& v) {
    return Eigen::Vector2i((int)std::ceil(v.x()), (int)std::ceil(v.y()));
}

inline static float gamma(int n) {
    return ((float)n * MACHINE_EPSILON) / (1.0f - (float)n * MACHINE_EPSILON);
}

template <typename T> inline static T linearInterpolate(float t, T a, T b) {
    return (1.0f - t) * a + t * b;
}

#endif