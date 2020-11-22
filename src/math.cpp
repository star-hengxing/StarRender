#include "../include/math.hpp"

#include <cmath>

Vector3f operator*(const float& t, const Vector3f& v)
{
    return Vector3f(v[0] * t, v[1] * t, v[2] * t);
}

Vector3f Vector3f::operator*(const float& t) const
{
    return Vector3f(e[0] * t, e[1] * t, e[2] * t);
}

Vector3f Vector3f::operator/(const float& t) const
{
    return Vector3f(e[0] / t, e[1] / t, e[2] / t);
}

Vector3f Vector3f::operator+(const Vector3f& v) const
{
    return Vector3f(e[0] + v[0], e[1] + v[1], e[2] + v[2]);
}

Vector3f Vector3f::operator-(const Vector3f& v) const
{
    return Vector3f(e[0] - v[0], e[1] - v[1], e[2] - v[2]);
}

Vector3f Vector3f::operator*(const Vector3f& v) const
{
    return Vector3f(e[0] * v[0], e[1] * v[1], e[2] * v[2]);
}
