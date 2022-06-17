#ifndef TRANSFORM_HELPER_H
#define TRANSFORM_HELPER_H

#include <Eigen/Dense>

#include "Transform.h"

inline static Transform translate(const Eigen::Vector3f& v) {
    Eigen::Matrix4f m, invM;
    m = invM = Eigen::Matrix4f::Identity();
    for (int i = 0; i < 3; i++) {
        m(i, 3) = v(i);
        invM(i, 3) = -v(i);
    }
    return Transform(m, invM);
}

inline static Transform scale(const Eigen::Vector3f& v) {
    Eigen::Matrix4f m, invM;
    m = invM = Eigen::Matrix4f::Identity();
    for (int i = 0; i < 3; i++) {
        m(i, i) = v(i);
        invM(i) = 1.0f / v(i);
    }
    return Transform(m, invM);
}

#endif