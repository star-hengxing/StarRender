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
    void Getuv(const Vector3f& p, float& u, float& v) const;

private:
    Vector3f center;
    float radius;
    float radius_square;
    std::shared_ptr<Material> material;
};

class Rectangle : public Object
{
public:
    Rectangle(float _x0, float _x1, float _y0, float _y1, float _k) :
        x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k) {}

    bool hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const override
    {
        auto t = (k - ray.origin().z()) / ray.direction().z();
        if (t < t_min || t > t_max)
        {
            return false;
        }
        auto x = ray.origin().x() + t * ray.direction().x();
        auto y = ray.origin().y() + t * ray.direction().y();
        if (x < x0 || x > x1 || y < y0 || y > y1)
        {
            return false;
        }
        rec.u = (x - x0) / (x1 - x0);
        rec.v = (y - y0) / (y1 - y0);
        rec.t = t;
        Vector3f outward_normal = Vector3f(0.f, 0.f, 1.f);
        rec.SetFaceNormal(ray, outward_normal);
        rec.material = material;
        rec.p = ray.at(t);
        return true;
    }
    void SetMaterial(std::shared_ptr<Material> m) { material = std::move(m); }

private:
    float x0, x1, y0, y1, k;
    std::shared_ptr<Material> material;
};

#endif // OBJECT_HPP