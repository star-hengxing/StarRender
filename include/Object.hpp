#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>

#include "math.hpp"
#include "Ray.hpp"
#include "Material.hpp"

class Object
{
public:
    virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const = 0;
};

class Sphere : public Object
{
public:
    Sphere() {}
    Sphere(Vector3f v, float r) : center(v), radius(r), radius_square(r * r) {}
    Sphere(Vector3f v, float r,
           std::shared_ptr<Material> m) : 
                center(v),
                radius(r),
                radius_square(r * r),
                material(m) {}
    void SetMaterial(std::shared_ptr<Material> m) { material = std::move(m); }
    /**
     * 判断与球体是否有撞击
     * \param r 光线
     * \param t_min 范围
     * \param t_max 范围
     * \param rec 撞击点
     * \return 是否有撞击
     */
    bool hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const override; 

private:
    Vector3f center;
    float radius;
    float radius_square;
    std::shared_ptr<Material> material;
};

#endif // OBJECT_HPP