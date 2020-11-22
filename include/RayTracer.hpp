#ifndef RayTRACER_HPP
#define RayTRACER_HPP

#include <sstream>
#include <string>
#include <thread>
#include <memory>
#include <string_view>

#include "math.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Object.hpp"

class RayTracer
{
public:
    RayTracer() {}
    RayTracer(const Scene& s) : scene(s) {}
    RayTracer(const Scene& s, const Camera& c) : scene(s), camera(c) {}
    RayTracer(const Scene& s, const Camera& c, std::string_view name) : scene(s),
                                                                        camera(c),
                                                                        file_name(name) {}

    /**
     * 主渲染函数，默认生成output.ppm
     * \param mul_threads 默认开启多线程，线程数默认最大
     */
    void render(bool mul_threads = true) const;

    inline static void SetSampleValue(int value) { sample = value; }
    inline static void SetThreadValue(int threads) { core = threads; }

private:
    // 进度条
    void UpdateProgress(float progress) const;
    // 隐藏光标
    void HideCursor() const;

    bool hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const;
    Vector3f SetColor(const Ray& ray, int depth) const;
    //分段多线程渲染
    std::string SubRender(int start, int end) const;

private:
    Scene scene;
    Camera camera;
    std::string file_name = "output.ppm";
    static inline int sample = 64;          // 采样次数
    static inline unsigned core = std::thread::hardware_concurrency();
};

#endif // RayTRACER_HPP