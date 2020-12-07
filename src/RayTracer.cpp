#include "../include/RayTracer.hpp"

#include <Windows.h>
#include <assert.h>

#include <cmath>

#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <future>

#include "../include/math.hpp"
#include "../include/Ray.hpp"
#include "../include/Scene.hpp"
#include "../include/Camera.hpp"
#include "../include/Object.hpp"

void RayTracer::UpdateProgress(float progress) const
{
    assert(progress == 0.f);
    printf("progress bar: %d %%\r", static_cast<int>(progress * 100.f));
    fflush(stdout);
}

void RayTracer::HideCursor() const
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

bool RayTracer::hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool flag(false);
    float closest_so_far(t_max);

    for(const auto& x : scene.objects)
    {
        if(x->hit(ray, t_min, closest_so_far, temp_rec))
        {
            flag = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return flag;
}

Vector3f RayTracer::SetColor(const Ray& ray, int depth) const
{
    if(depth <=0)
    {
        return Vector3f();
    }
    
    if(HitRecord rec; hit(ray, 0.001f, kInfinity, rec))
    {
        Ray scattered;
        Vector3f attenuation;
        Vector3f emitted = rec.material->emitted(rec.u, rec.v, rec.p);
        if(rec.material->scatter(ray, rec, attenuation, scattered))
        {
            return emitted + attenuation * SetColor(scattered, depth-1);
        }
        else
        {
            return emitted;
        }
    }
    else
    {
        return scene.backgroundColor;
    }
#if 0
            Vector3f target = rec.p + rec.normal + RandomInUnitShpere();//阴影重一点，下面则轻很多
            //Vector3f target = rec.p + RandomInHemisphere(rec.normal);
            return 0.5 * color(Ray(rec.p, target - rec.p), depth - 1);
            return 0.5f * Vector3f(rec.normal.x() + 1,
                                    rec.normal.y() + 1,
                                    rec.normal.z() + 1);
    Vector3f unit_direction = normalize(ray.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * Vector3f(1.0f, 1.0f, 1.0f) + t * Vector3f(0.5f, 0.7f, 1.0f);
#endif
}

std::string RayTracer::SubRender(int start, int end) const
{
    std::stringstream ss;
    for (int j(start); j >= end; --j)
    {
        for (int i(0); i < scene.width; ++i)
        {
            Vector3f col;
            for(int k(0); k < sample; ++k)
            {
                float u = (static_cast<float>(i) + RandomFloat()) / scene.width;
                float v = (static_cast<float>(j) + RandomFloat()) / scene.height;
                Ray ray = camera.GetRay(u, v);
                col = col + SetColor(ray, 50);
            }
            col = col * (1.0f / static_cast<float>(sample));
            ss  << static_cast<int>(255.999f * sqrtf(col.x())) << ' '
                << static_cast<int>(255.999f * sqrtf(col.y())) << ' '
                << static_cast<int>(255.999f * sqrtf(col.z())) << '\n';
        }
        //UpdateProgress((scene.height - j) / static_cast<float>(scene.height));
    }
    return ss.str();
}

void RayTracer::render(bool mul_threads) const
 {
    HideCursor();
    std::ofstream save(file_name,std::ios::out);

    if(save.is_open())
    {
        save << "P3\n" << scene.width << " " << scene.height << "\n255 \n";
        clock_t start_time = clock();
        if(mul_threads && core > 1)
        {
            printf("Enable %d-thread rendering\n", core);
            std::vector<std::future<std::string>> threads;
            
            int bias(scene.height / core);
            int start(scene.height - 1);
            int end(scene.height - bias);
            /*
            * bias 480
            * 1920 - 1, 1440
            * 1440 - 1, 960
            * 960 - 1, 480
            * 480 - 1, 0
            */
            for(int x(0); x < core; ++x)
            {
                threads.push_back(
                            std::async(
                                std::launch::async,
                                &RayTracer::SubRender,
                                this,
                                start,
                                end));
                start = end - 1;
                end -= bias;
            }
            
            for(auto& x : threads)
            {
                save << x.get();
            }
        }
        else
        {
            for (int j(scene.height - 1); j >= 0; --j)
            {
                for (int i(0); i < scene.width; ++i)
                {
                    Vector3f col;
                    for(int k(0); k < sample; ++k)
                    {
                        float u = (static_cast<float>(i) + RandomFloat()) / scene.width;
                        float v = (static_cast<float>(j) + RandomFloat()) / scene.height;
                        Ray ray = camera.GetRay(u, v);
                        col = col + SetColor(ray, 50);
                    }
                    col = col * (1.0f / static_cast<float>(sample));
                    save    << static_cast<int>(255.999f * sqrtf(col.x())) << ' '
                            << static_cast<int>(255.999f * sqrtf(col.y())) << ' '
                            << static_cast<int>(255.999f * sqrtf(col.z())) << '\n';
                }
                UpdateProgress((scene.height - j) / static_cast<float>(scene.height));
            }
            UpdateProgress(1.f);
        }
        clock_t end_time = clock();
        save.close();

        int time = static_cast<int>(end_time - start_time) / CLOCKS_PER_SEC;
        if(time < 60)
        {
            printf("This program ran for %d seconds\n", time);
        }
        else if(time < 3600)
        {
            printf("This program ran for %d mins %d seconds\n", time/60, time%60);
        }
        else
        {
            int t = time % 3600;
            printf("This program ran for %d hour %d mins %d seconds\n",
                time / 3600,
                t / 60,
                t % 60);
        }
    }
    else
    {
        printf("cannot save the image!");
    }
}
