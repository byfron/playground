#ifndef __VEC3_HPP__
#define __VEC3_HPP__

#include <cmath>
#include <iostream>

template <typename T>
class Vec3 {
    public:

        Vec3() {};
        Vec3(T x, T y, T z) : data{x, y, z} {}

        T x() const { return data[0]; }
        T y() const { return data[1]; }
        T z() const { return data[2]; }

        Vec3 operator-() const {
            return Vec3(-data[0], -data[1], -data[2]);
        }
        T operator[](int i) const { return data[i]; }
        T& operator[](int i) { return data[i]; }

        Vec3& operator+=(const Vec3& v) {
            data[0] += v.data[0];
            data[1] += v.data[1];
            data[2] += v.data[2];
            return *this;
        }

        Vec3& operator*=(const T s) {
            data[0] *= s;
            data[1] *= s;
            data[2] *= s;
            return *this;
        }

        Vec3& operator/=(const T s) {
            return *this *= 1/s;
        }

        double length() {
            return sqrt(length_squared());
        }

        T length_squared() {
            return data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
        }

        template <typename U>
        friend Vec3<U> operator+(const Vec3<U> &u, const Vec3<U> &v);

        template <typename U>
        friend std::ostream& operator<<(std::ostream &out, const Vec3<U> &v);

        template <typename U>
        friend Vec3<U> operator-(const Vec3<U> &u, const Vec3<U> &v);

        template <typename U>
        friend Vec3<U> operator*(const Vec3<U> &u, const Vec3<U> &v);

        template <typename U>
        friend Vec3<U> operator*(double t, const Vec3<U> &v);

        template <typename U>
        friend Vec3<U> operator/(Vec3<U> v, double t);

    private:

        T data[3];
};

using Vec3d = Vec3<double>;
using Point3 = Vec3<double>;
using Color = Vec3<double>;

// vec3 Utility Functions

template <typename T>
inline std::ostream& operator<<(std::ostream &out, const Vec3<T> &v) {
    return out << v.data[0] << ' ' << v.data[1] << ' ' << v.data[2];
}

template <typename T>
inline Vec3<T> operator+(const Vec3<T> &u, const Vec3<T> &v) {
    return Vec3(u.data[0] + v.data[0], u.data[1] + v.data[1], u.data[2] + v.data[2]);
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T> &u, const Vec3<T> &v) {
    return Vec3(u.data[0] - v.data[0], u.data[1] - v.data[1], u.data[2] - v.data[2]);
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T> &u, const Vec3<T> &v) {
    return Vec3(u.data[0] * v.data[0], u.data[1] * v.data[1], u.data[2] * v.data[2]);
}

template <typename T>
inline Vec3<T> operator*(double t, const Vec3<T> &v) {
    return Vec3(t*v.data[0], t*v.data[1], t*v.data[2]);
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T> &v, double t) {
    return t * v;
}

template <typename T>
inline Vec3<T> operator/(Vec3<T> v, double t) {
    return (1/t) * v;
}

template <typename T>
inline double dot(const Vec3<T> &u, const Vec3<T> &v) {
    return u[0] * v[0]
         + u[1] * v[1]
         + u[2] * v[2];
}

template <typename T>
inline Vec3<T> cross(const Vec3<T> &u, const Vec3<T> &v) {
    return Vec3<T>(u[1] * v[2] - u[2] * v[1],
                   u[2] * v[0] - u[0] * v[2],
                   u[0] * v[1] - u[1] * v[0]);
}

template <typename T>
inline Vec3<T> unit_vector(Vec3<T> v) {
    return v / v.length();
}

#endif