#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "math.hpp"
#include "Ray.hpp"

class Camera
{
public:
    Camera( Vector3f l = Vector3f(-2.0f, -1.0f, -1.0f),
            Vector3f h = Vector3f(4.0f, 0.0f, 0.0f),
            Vector3f v = Vector3f(0.0f, 2.0f, 0.0f),
            Vector3f o = Vector3f(0.0f, 0.0f, 0.0f)) :
            lower_left_corner(l),
            horizontal(h),
            vertical(v),
            origin(o) {}
    /**
    * \param lookfrom 相机位置
    * \param lookat 观察点
    * \param vup 相机的倾斜方向 view up
    * \param vfov 视野 field of view
    * \param aspect 宽高比
    */
    Camera( Vector3f lookfrom,
            Vector3f lookat,
            Vector3f vup,
            float vfov,
            float aspect,
            float aperture,
            float focus_dist);
    
    Ray GetRay(float u, float v) const;

private:
    Vector3f lower_left_corner;     //画布左下角点
    Vector3f horizontal;            //宽
    Vector3f vertical;              //高
    Vector3f origin;                //相机原点
    Vector3f u, v, w;
    float lens_radius;
};

#endif
