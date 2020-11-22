#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

#include <limits>
#include <functional>
#include <random>

constexpr float kPi(3.14159265358979323846);
//constexpr float kInfinity = (std::numeric_limits<float>::max)();
constexpr float kInfinity(std::numeric_limits<float>::max());

inline float RandomFloat(float min = 0.f, float max = 1.f);

class Vector3f
{
public:
    Vector3f() : e{0} {}
    Vector3f(float e0) : e{e0, e0, e0} {}
    Vector3f(float e0, float e1, float e2) : e{e0, e1, e2} {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    Vector3f operator-() const { return Vector3f(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) { return e[i]; }

    friend Vector3f operator*(const float& t, const Vector3f& v);

    Vector3f operator*(const float& t) const;
    Vector3f operator/(const float& t) const;

    Vector3f operator+(const Vector3f& v) const;
    Vector3f operator-(const Vector3f& v) const;
    Vector3f operator*(const Vector3f& v) const;

    float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }

    inline static Vector3f random()
    {
        return Vector3f(RandomFloat(), RandomFloat(), RandomFloat());
    }

    inline static Vector3f random(float min, float max)
    {
        return Vector3f(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
    }
    
private:
    float e[3];
};
// 法线归一
inline Vector3f normalize(const Vector3f& v)
{
    float mag2 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    if (mag2 > 0)
    {
        float invMag = 1 / sqrt(mag2);
        return Vector3f(v[0] * invMag, v[1] * invMag, v[2] * invMag);
    }

    return v;
}
// 点乘
inline float dot(const Vector3f& a, const Vector3f& b)
{
    return a[0] * b[0] +
           a[1] * b[1] +
           a[2] * b[2];
}
// 叉乘
inline Vector3f cross(const Vector3f& a, const Vector3f& b)
{
    return Vector3f(a[1] * b[2] - a[2] * b[1],
                    a[2] * b[0] - a[0] * b[2],
                    a[0] * b[1] - a[1] * b[0]);
}

inline float clamp(const float& lo, const float& hi, const float& v)
{
    return std::max(lo, std::min(hi, v));
}
// 随机浮点数
inline float RandomFloat(float min, float max)
{
    static std::uniform_real_distribution<float> distribution(min, max);
#if 0
    static std::default_random_engine e;
    return distribution(e);
#endif
    static std::mt19937 generator;
    static std::function<float()> rand_generator =
        std::bind(distribution, generator);
    return rand_generator();
}

inline Vector3f RandomInUnitShpere()
{
    // 半球面向量（极坐标形式）
    float a = RandomFloat(0, 2 * kPi);
    float z = RandomFloat(-1, 1);
    float r = sqrt(1 - z * z);
    return Vector3f(r * cos(a), r * sin(a), z);
#if 0
    while(1)
    {
        Vector3f v = Vector3f::random(-1.f, 1.f);
        if(v.length() < 1.0f)
        {
            return v;
        }
    }
#endif
}

inline Vector3f RandomInHemisphere(const Vector3f& normal)
{
    Vector3f in_unit_sphere = RandomInUnitShpere();
    if (dot(in_unit_sphere, normal) > 0.0f) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}
// 从一个单位小圆盘射出光线
inline Vector3f RandomInUnitDisk()
{
    while (true)
    {
        auto p = Vector3f(RandomFloat(-1,1), RandomFloat(-1,1), 0);
        if (p.length() >= 1)
        {
            continue;
        }
        return p;
    }
}
// 反射
inline Vector3f reflect(const Vector3f& v, const Vector3f v2)
{
    return v - 2 * dot(v, v2) * v2;
}
// 折射
inline Vector3f refract(const Vector3f& uv, const Vector3f& n, float etai_over_etat)
{
    float cos_theta = dot(-uv, n);
    Vector3f r_out_parallel =  etai_over_etat * (uv + cos_theta * n);
    Vector3f r_out_perp = -sqrt(1.0 - r_out_parallel.length()) * n;
    return r_out_parallel + r_out_perp;
}

inline float schlick(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
// 弧度制转角度制
inline float DegreesToRaduans(const float& deg)
{
    return deg * kPi / 180.f;
}

#endif // MATH_HPP