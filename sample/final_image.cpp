#include <iostream>
#include <memory>

#include "include/RayTracer.hpp"
#include "include/Material.hpp"

using namespace std;

int main()
{
    Vector3f lookfrom(13, 2, 3);
    Vector3f lookat(0, 0, 0);
    float dist_to_focus = 10;
    float aperture = 0.1;
    Scene scene(resolution::re_720);
    Camera camera(lookfrom, lookat, Vector3f(0, 1, 0), 20, scene.GetAspectRatio(), aperture, dist_to_focus);

    auto background_Sphere = make_shared<Sphere>(Vector3f(0.f, -1000.f, 0.f), 1000.f);
    background_Sphere->SetMaterial(make_shared<Lambertian>(Vector3f(0.5f, 0.5f, 0.5f)));

    scene.add(make_shared<Sphere>(Vector3f(4.f, 1.f, 0.f), 1.f, make_shared<Metal>(Vector3f(0.7f, 0.6f, 0.5f), 0.0f)))
         .add(make_shared<Sphere>(Vector3f(0.f, 1.f, 0.f), 1.f, make_shared<Metal>(Vector3f(0.7f, 0.3f, 0.3f), 0.5)))
         .add(make_shared<Sphere>(Vector3f(-4.f, 1.f, 0.f), 1.f, make_shared<Lambertian>(Vector3f(0.4f, 0.2f, 0.1f))))
         .add(background_Sphere);

    constexpr int num(11);
    for (int a = -num; a < num; ++a)
    {
        for (int b = -num; b < num; ++b)
        {
            auto choose_mat = RandomFloat();
            Vector3f center(a + 0.9f * RandomFloat(), 0.2f, b + 0.9f * RandomFloat());
            if ((center - Vector3f(4.f, 0.2f, 0.f)).length() > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = Vector3f::random() * Vector3f::random();
                    scene.add(make_shared<Sphere>(center, 0.2f, make_shared<Lambertian>(albedo)));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = Vector3f::random(0.5f, 1.f);
                    auto fuzz = RandomFloat(0.f, 0.5f);
                    scene.add(make_shared<Sphere>(center, 0.2f, make_shared<Metal>(albedo, fuzz)));
                }
            }
        }
    }

    RayTracer x(scene, camera, "final_image_720.ppm");
    x.render();
    
    return 0;
}
