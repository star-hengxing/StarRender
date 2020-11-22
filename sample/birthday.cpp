#include <iostream>
#include <memory>

#include "include/RayTracer.hpp"
#include "include/Material.hpp"
#include "include/Texture.hpp"

using namespace std;

int main()
{
	Scene scene(resolution::re_2k);

    Vector3f lookfrom(0.0f, 0.0f, 12.f);
	Vector3f lookat(0.f, 0.f, -1.f);
	Vector3f vup(0.f, 1.f, 0.f);
	float aperture = 0.0f;
	Camera camera(lookfrom, lookat, vup, 90, scene.GetAspectRatio(), aperture, (lookfrom - lookat).length());

	auto background_sphere = make_shared<Sphere>(Vector3f(0.0f, -100.5f, -1.0f), 100.0f);
	auto checker = make_shared<CheckerBoard>(
		make_shared<ConstantTexture>(Vector3f(1.f, 0.f, 0.f)), // 红
		make_shared<ConstantTexture>(Vector3f(1.f, 1.f, 0.f)));// 黄
	background_sphere->SetMaterial(make_shared<Metal>(Vector3f(0.5f, 0.5f, 0.5f), 0.5f));
    scene.add(background_sphere);

    float radius = 0.5f;    //半径
    float space  = -1.0f;    //文字所在平面

    //生
    float y = 0.0f;
    float x;
    for(int i(0); i < 3; ++i)
    {
        x = -20.0f;    
        for(int j(0); j < 9; ++j)
        {
            auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
            sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
            scene.add(sphere);
            x +=1.f;
        }
        y +=2.f;
    }

    y = 1.f;
    for(int i(0); i < 4; ++i)
    {
        if(i == 3)
        {
            y -=1.f;
        }
        auto sphere = make_shared<Sphere>(Vector3f(-16.f, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y +=2.f;
    }

    y = 6.f;
	x = -20.f;
	for (int i(0); i < 6; ++i)
	{
		auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
		sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
		scene.add(sphere);
		x -= 0.5f;
		y -= 0.5f;
	}
    //日
    y = 0.f;
    for(int i(0); i < 3; ++i)
    {
        x = -7.0f;    
        for(int j(0); j < 7; ++j)
        {
            auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
            sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
            scene.add(sphere);
            x +=1.f;
        }
        y +=3.f;
    }

    x = -7.0f;
    y = 0.f;
    for(int i(0); i < 2; ++i)
    {
        y = 0.f;
        for(int j(0); j < 7; ++j)
        {
            auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
            sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
            scene.add(sphere);
            y +=1.f;
        }
        x += 6.f;
    }
    //快
    x = 5.f;
    y = 0.f;
    for(int i(0); i < 8; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y += 1.f;
    }

    x = 4.f;
    y = 4.f;
    for(int i(0); i < 3; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y -= 0.5f;
        x -= 0.5f;
    }

    x = 6.f;
    y = 5.f;
    for(int i(0); i < 2; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y -= 0.5f;
        x += 0.5f;
    }

    x = 8.0f;
    y = 6.f;
    for(int i(0); i < 5; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        x += 1.f;
    }

    x = 6.5f;
	y = 3.5f;
    for(int i(0); i < 8; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        x += 1.f;
    }

    x = 12.5f;
	y = 3.5f;
    for(int i(0); i < 3; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y += 1.f;
    }

    x = 10.f;
	y = 4.5f;
    for(int i(0); i < 4; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y += 1.f;
    }

    x = 10.f;
	y = 2.5f;
    for(int i(0); i < 4; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y -= 0.7f;
        x -= 0.7f;
    }

    x = 10.f;
	y = 2.5f;
    for(int i(0); i < 4; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y -= 0.7f;
        x += 0.7f;
    }
    //乐
    x = 16.f;
	y = 6.f;
    for(int i(0); i < 7; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        x += 1.f;
        y += 0.1f;
    }
    
    x = 16.f;
	y = 3.f;
    for(int i(0); i < 7; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        x += 1.f;
    }

    x = 16.f;
	y = 5.f;
    for(int i(0); i < 2; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y -= 1.f;
    }

    x = 19.f;
	y = 4.f;
    for(int i(0); i < 6; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y -= 1.f;
    }

    y += 1.f;
    for(int i(0); i < 1; ++i)
    {
        y += 0.5f;
		x -= 1.3f;
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
    }

    x = 17.f;
	y = 1.5f;
    for(int i(0); i < 3; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y -= 0.7f;
        x -= 0.7f;
    }

    x = 21.f;
	y = 1.5f;
    for(int i(0); i < 3; ++i)
    {
        auto sphere = make_shared<Sphere>(Vector3f(x, y, space), radius);
        sphere->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f::random() * Vector3f::random())));
        scene.add(sphere);
        y -= 0.7f;
        x += 0.7f;
    }

    RayTracer make(scene,camera);
    make.render();
	return 0;
}
