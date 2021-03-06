#include "../include/Object.hpp"

#include <cmath>

#include "../include/math.hpp"
#include "../include/Ray.hpp"
#include "../include/Material.hpp"

bool Sphere::hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
    Vector3f oc = ray.origin() - center;                // A-C
    float b = dot(ray.direction(), oc);
    float c = dot(oc, oc) - radius_square;     
    float a = dot(ray.direction(), ray.direction());    //
    float det = b * b - a * c;                          // b^2 - 4ac
    if(det > 0)
    {
        float root = sqrt(det);
        float temp = (-b - root) / a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = ray.at(temp);
            Vector3f outward_normal = (rec.p - center) / radius;
            rec.SetFaceNormal(ray, outward_normal);
            rec.material = material;
            return true;
        }
        temp = (-b + root) / a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = ray.at(temp);
            //rec.normal = (rec.p - center) / radius;
            Vector3f outward_normal = (rec.p - center) / radius;
            rec.SetFaceNormal(ray, outward_normal);
            rec.material = material;
            return true;
        }
        //Getuv((rec.p - center) / radius, rec.u, rec.v);
    }
    return false;
}

void Sphere::Getuv(const Vector3f& p, float& u, float& v) const
{
    auto phi = atan2(p.z(), p.x());
    auto theta = asin(p.y());
    u = 1-(phi + kPi) / (2 * kPi);
    v = (theta + kPi / 2) / kPi;
}