#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <cmath>

template <int n> class Spectrum {
protected:
    float c[n];

public:
    Spectrum(float v = 0.0f) {
        for (int i = 0; i < n; i++)
            c[i] = v;
    }

    Spectrum(const Spectrum<n>& s) {
        for (int i = 0; i < n; i++)
            c[i] = s.c[i];
    }

    ~Spectrum() {}

    Spectrum<n> operator+(const Spectrum<n>& s) const {
        Spectrum<n> ans;
        for (int i = 0; i < n; i++)
            ans.c[i] = c[i] + s.c[i];
        return ans;
    }

    Spectrum<n>& operator+=(const Spectrum<n>& s) {
        for (int i = 0; i < n; i++)
            c[i] += s.c[i];
        return *this;
    }

    Spectrum<n> operator-(const Spectrum<n>& s) const {
        Spectrum<n> ans;
        for (int i = 0; i < n; i++)
            ans.c[i] = c[i] - s.c[i];
        return ans;
    }

    Spectrum<n>& operator-=(const Spectrum<n>& s) {
        for (int i = 0; i < n; i++)
            c[i] -= s.c[i];
        return *this;
    }

    friend inline Spectrum<n> operator*(float v, const Spectrum<n>& s) {
        Spectrum<n> ans;
        for (int i = 0; i < n; i++)
            ans.c[i] = v * s.c[i];
        return ans;
    }

    Spectrum<n> operator*(float v) const {
        Spectrum<n> ans;
        for (int i = 0; i < n; i++)
            ans.c[i] = c[i] * v;
        return ans;
    }

    Spectrum<n>& operator*=(float v) {
        for (int i = 0; i < n; i++)
            c[i] *= v;
        return *this;
    }

    Spectrum<n> operator*(const Spectrum<n>& s) const {
        Spectrum<n> ans;
        for (int i = 0; i < n; i++)
            ans.c[i] = c[i] * s.c[i];
        return ans;
    }

    Spectrum<n>& operator*=(const Spectrum<n>& s) {
        for (int i = 0; i < n; i++)
            c[i] *= s.c[i];
        return *this;
    }

    Spectrum<n> operator/(float v) const {
        Spectrum<n> ans;
        for (int i = 0; i < n; i++)
            ans.c[i] = c[i] / v;
        return ans;
    }

    Spectrum<n>& operator/=(float v) {
        for (int i = 0; i < n; i++)
            c[i] /= v;
        return *this;
    }

    Spectrum<n> operator/(const Spectrum<n>& s) const {
        Spectrum<n> ans;
        for (int i = 0; i < n; i++)
            ans.c[i] = c[i] / s.c[i];
        return ans;
    }

    Spectrum<n>& operator/=(const Spectrum<n>& s) {
        for (int i = 0; i < n; i++)
            c[i] /= s.c[i];
        return *this;
    }

    float& operator[](int i) {
        return c[i];
    }

    float operator[](int i) const {
        return c[i];
    }

    friend inline Spectrum<n> sqrt(const Spectrum<n>& s) {
        Spectrum<n> ans;
        for (int i = 0; i < n; i++)
            ans.c[i] = std::sqrt(s.c[i]);
        return ans;
    }
};

#endif