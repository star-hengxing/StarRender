#include "../include/Camera.hpp"

#include "../include/math.hpp"
#include "../include/Ray.hpp"

Camera::Camera( Vector3f lookfrom,
                Vector3f lookat,
                Vector3f vup,
                float vfov,
                float aspect,
                float aperture,
                float focus_dist)
{
    origin = lookfrom;
    lens_radius = aperture / 2;

    float theta =  DegreesToRaduans(vfov);
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;

    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);
    
    lower_left_corner = origin
                      - half_width * focus_dist * u
                      - half_height * focus_dist * v
                      - focus_dist * w;


    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
}

Ray Camera::GetRay(float u, float v) const
{
    Vector3f rd = lens_radius * RandomInUnitDisk();
    Vector3f offset = u * rd.x() + v * rd.y();
    return Ray(
        origin + offset,
        lower_left_corner + u * horizontal + v * vertical - origin - offset);
}