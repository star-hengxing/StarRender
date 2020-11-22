#include <iostream>
#include <memory>

#include "include/RayTracer.hpp"
#include "include/Material.hpp"
#include "include/Texture.hpp"

using namespace std;

int main()
{
	Scene scene(resolution::re_720);
	// Add objects
	auto sphere_1 = make_shared<Sphere>(Vector3f(-1.f, 0.0f, -1.0f), 0.5f);
	auto sphere_2 = make_shared<Sphere>(Vector3f(0.f, 0.5f, -1.0f), 0.5f);
	//auto sphere_3 = make_shared<Sphere>(Vector3f(1.0f, 1.0f, -1.0f), 0.5f);
	// our ground is a big sphere
	auto background_sphere = make_shared<Sphere>(Vector3f(0.0f, -100.5f, -1.0f), 100.0f);
	// 设置材质(漫反射，金属，玻璃)
	auto checker = make_shared<CheckerBoard>(
		make_shared<ConstantTexture>(Vector3f(1.f, 0.f, 0.f)),
		make_shared<ConstantTexture>(Vector3f(1.f, 1.f, 0.f)));
	background_sphere->SetMaterial(make_shared<Lambertian>(checker));

	sphere_1->SetMaterial(make_shared<Metal>(Vector3f(0.7f, 0.6f, 0.5f), 0.1f));
	sphere_2->SetMaterial(make_shared<Lambertian>(make_shared<ConstantTexture>(Vector3f(0.7f, 0.3f, 0.3f))));
	//sphere_3->SetMaterial(make_shared<Dielectric>(1.5f));

	scene.add(move(background_sphere))
		//.add(move(sphere_3))
		.add(move(sphere_1))
		.add(move(sphere_2));
	// Set Camera position
	Vector3f lookfrom(0.0f, 0.0f, 1.0f);
	Vector3f lookat(0.f, 0.f, -1.f);
	Vector3f vup(0.f, 1.f, 0.f);
	float aperture = 0.0f;
	Camera camera(lookfrom, lookat, vup, 90, scene.GetAspectRatio(), aperture, (lookfrom - lookat).length());

	RayTracer ray_tracer(scene, camera);
	ray_tracer.render();
	return 0;
}

