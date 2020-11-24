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

    bool scatter(   const Ray& ray,
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

    bool scatter(   const Ray& ray,
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

    bool scatter(   const Ray& ray,
                    const HitRecord& rec,
                    Vector3f& attenuation,
                    Ray& scattered) const override
    {
        attenuation = Vector3f(1.0f);
        Vector3f reflected = reflect(ray.direction(), rec.normal);
        float ratio = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);;
        float cosine = std::min(dot(-ray.direction(), rec.normal), 1.0f); // 入射角余弦

        float reflect_prob; // 反射系数
        Vector3f refracted;
        if(refract(ray.direction(), rec.normal, ratio, refracted))
        {   // 发生了折射 计算反射系数
            reflect_prob = schlick(cosine, ref_idx);
        }
        else
        {   // 全反射
            reflect_prob = 1.0f;
        }
        
        if (reflect_prob > RandomFloat())
        {
            scattered = Ray(rec.p, reflected);
        }
        else
        {
            scattered = Ray(rec.p, refracted);
        }
        return true;
    }

private:
    float ref_idx; // Refractive index
};
#endif // MATERIAL_HPP