#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>

#include "Ray.hpp"
#include "Object.hpp"
#include "math.hpp"
#include "Texture.hpp"

class Material;

//TODO: 检查是否要字节对齐
struct HitRecord
{
    Vector3f p;     // 坐标
    Vector3f normal;
    std::shared_ptr<Material> material;
    float t = 0;    // 时间
    float u;
    float v;
    bool front_face;

    inline void SetFaceNormal(const Ray& ray, const Vector3f& outward_normal)
    {
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Material
{
public:
    virtual bool scatter(const Ray& ray,
                         const HitRecord& rec,
                         Vector3f& attenuation,
                         Ray& scattered) const = 0;

};
// 漫反射材质
class Lambertian : public Material
{
public:
    Lambertian(std::shared_ptr<Texture> x) : albedo(x) {}

    bool scatter(const Ray& ray,
                         const HitRecord& rec,
                         Vector3f& attenuation,
                         Ray& scattered) const override
    {
        Vector3f scatter_direction = rec.normal + RandomInUnitShpere();
        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }


private:
    std::shared_ptr<Texture> albedo;
};
// 金属材质
class Metal : public Material
{
public:
    Metal(const Vector3f& v, float f) : albedo(v), fuzz(f < 1? f : 1) {}

    bool scatter(const Ray& ray,
                         const HitRecord& rec,
                         Vector3f& attenuation,
                         Ray& scattered) const override
    {
        Vector3f reflected = reflect(ray.direction(), normalize(rec.normal));
        scattered = Ray(rec.p, reflected + fuzz * RandomInUnitShpere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
private:
    Vector3f albedo;
    float fuzz; // 模糊度
};
// 电介质
class Dielectric : public Material
{
public:
    Dielectric(float ri) : ref_idx(ri) {}

    bool scatter(const Ray& ray,
                         const HitRecord& rec,
                         Vector3f& attenuation,
                         Ray& scattered) const override
    {
        attenuation = Vector3f(1.0f);
        float etai_over_etat = (rec.front_face) ? (1.0f / ref_idx) : (ref_idx);

        Vector3f unit_direction = normalize(ray.direction());
        float cos_theta = std::min(dot(-unit_direction, rec.normal), 1.0f);
        float sin_theta = sqrt(1.0f - cos_theta * cos_theta);
        
        if (etai_over_etat * sin_theta > 1.0f )
        {
            Vector3f reflected = reflect(unit_direction, rec.normal);
            scattered = Ray(rec.p, reflected);
            return true;
        }
        /*
        * Fresnel 光在透明介质表面被折射的光通量的比率
        * 光线照射到透明物体上时，一部分发生反射，一部分进入物体内部并在介质交界处发生折射
        * 被反射和折射的光通量存在一定的比率关系，这个比率关系可以通过 Fresnel 定律进行计算。 
        */
        float reflect_prob = schlick(cos_theta, etai_over_etat);
        if (RandomFloat() < reflect_prob)
        {
            Vector3f reflected = reflect(unit_direction, rec.normal);
            scattered = Ray(rec.p, reflected);
            return true;
        }
        
        Vector3f refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = Ray(rec.p, refracted);
        return true;
    }

private:
    float ref_idx;
};
#endif // MATERIAL_HPP