#ifndef WINDOWMANAGER_VECTOR3_H
#define WINDOWMANAGER_VECTOR3_H

#include <cmath>

template <typename T>
class Vector3 {
public:
    T x = 0;
    T y = 0;
    T z = 0;

    Vector3() = default;

    Vector3(const T& x, const T& y, const T& z):
            x(x),
            y(y),
            z(z) {}

    Vector3 operator+(const Vector3& vec) const {
        return Vector3(x + vec.x, y + vec.y, z + vec.z);
    }

    T operator*(const Vector3& vec) const {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    Vector3 operator-(const Vector3& vec) const {
        return Vector3(x - vec.x, y - vec.y, z - vec.z);
    }

    Vector3& operator-() {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    double len() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    double operator^(const Vector3& vec) const {
        return std::acos((*this * vec) / (len() * vec.len()));
    }

    double cos(const Vector3& vec) const {
        return (*this * vec) / (len() * vec.len());
    }

    Vector3& operator=(const Vector3& color) {
        x = color.x;
        y = color.y;
        z = color.z;

        return *this;
    }
};

#endif //WINDOWMANAGER_VECTOR3_H
