#ifndef BOUNDS_H
#define BOUNDS_H

#include <Eigen/Dense>

template <typename T, int n> class Bounds {
public:
    Eigen::Vector<T, n> pMin, pMax;

    Bounds() :
        pMin(Eigen::Vector<T, n>::Zero()),
        pMax(Eigen::Vector<T, n>::Zero()) {}

    Bounds(const Eigen::Vector<T, n>& pMin, const Eigen::Vector<T, n>& pMax) :
        pMin(pMin),
        pMax(pMax) {}

    Bounds(const Bounds<T, n>& bounds) :
        pMin(bounds.pMin),
        pMax(bounds.pMax) {}

    ~Bounds() {}

    Eigen::Vector<T, n> adjust(const Eigen::Vector<T, n>& v) {
        Eigen::Vector<T, n> ans = v;
        for (int i = 0; i < n; i++) {
            ans(i) = std::max(ans(i), pMin(i));
            ans(i) = std::min(ans(i), pMax(i));
        }
        return ans;
    }
};

template <typename T> class Bounds2 : public Bounds<T, 2> {
public:
    Bounds2() :
        Bounds<T, 2>() {}

    Bounds2(const Eigen::Vector<T, 2>& pMin, const Eigen::Vector<T, 2>& pMax) :
        Bounds<T, 2>(pMin, pMax) {}

    Bounds2(const Bounds<T, 2>& bounds) :
        Bounds<T, 2>(bounds) {}

    ~Bounds2() {}

    T area() {
        Eigen::Vector<T, 2> d = this->pMax - this->pMin;
        return d.x() * d.y();
    }
};

template <typename T> class Bounds3 : public Bounds<T, 3> {
public:
    Bounds3() :
        Bounds<T, 3>() {}

    Bounds3(const Eigen::Vector<T, 3>& pMin, const Eigen::Vector<T, 3>& pMax) :
        Bounds<T, 3>(pMin, pMax) {}

    Bounds3(const Bounds<T, 3>& bounds) :
        Bounds<T, 3>(bounds) {}

    ~Bounds3() {}
};

typedef Bounds2<int> Bounds2i;
typedef Bounds2<float> Bounds2f;
typedef Bounds3<float> Bounds3f;

#endif