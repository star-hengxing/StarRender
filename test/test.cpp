#include <iostream>
#include <memory>

#include "include/RayTracer.hpp"
#include "include/Material.hpp"

using namespace std;

int main()
{
	Scene scene; // 1920x1080,default resolution
    //Scene scene(1280, 720);
    // Add objects
    auto sphere_1 = make_shared<Sphere>(Vector3f(0.0f, 0.0f, -1.0f), 0.5f);
    // our ground is a big sphere
    auto background_sphere = make_shared<Sphere>(Vector3f(0.0f, -100.5f, -1.0f), 100.0f);
    auto sphere_2 = make_shared<Sphere>(Vector3f(1.5f, 0.0f, -1.0f), 0.5f);
    // 设置材质(漫反射，金属)
    sphere_1->SetMaterial(make_shared<Lambertian>(Vector3f(0.7f, 0.3f, 0.3f)));
    sphere_2->SetMaterial(make_shared<Metal>(Vector3f(0.1f, 0.1f, 0.1f), 0.1f));
    background_sphere->SetMaterial(make_shared<Metal>(Vector3f(0.5f, 0.5f, 0.5f),0.1f)); 
    
    scene.add(move(background_sphere))
         .add(move(sphere_1))
         .add(move(sphere_2));
    // Set Camera position
    Camera camera(  Vector3f(-2.f, 2.f, -3.f),
                    Vector3f(0, 0, -1),
                    Vector3f(0, 1, 0),
                    90,
                    scene.GetAspectRatio());

    RayTracer ray_tracer(scene,camera);
    ray_tracer.render();
    return 0;
}
