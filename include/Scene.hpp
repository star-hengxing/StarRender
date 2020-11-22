#ifndef Scene_HPP
#define Scene_HPP

#include <vector>
#include <memory>

#include "math.hpp"
#include "Object.hpp"


// 16:9
enum class resolution
{
    re_200,
    re_400,
    re_720,
    re_1080,
    re_2k,
    re_4k
};

class Scene
{
public:
    Scene() {}
    Scene(int w, int h) : width(w), height(h) {}
    Scene(int w, int h, Vector3f bg) : width(w), height(h), backgroundColor(bg) {}
    Scene(resolution re)
    {
        switch (re)
        {
            case resolution::re_200:
            {
                width  = 200;
                height = 100;
                break;
            }
            case resolution::re_400:
            {
                width  = 400;
                height = 200;
                break;
            }
            case resolution::re_720:
            {
                width  = 1280;
                height = 720;
                break;
            }
            case resolution::re_1080:
            {
                width  = 1920;
                height = 1080;
                break;
            }
            case resolution::re_2k:
            {
                width  = 2560;
                height = 1440;
                break;
            }
            case resolution::re_4k:
            {
                width  = 3840;
                height = 2160;
                break;
            }
            default:
                break;
        }
    }

    Scene& add(std::shared_ptr<Object> object)
    {
        objects.push_back(std::move(object));
        return *this;
    }
    //场景物体清理
    void clear() { objects.clear(); }

    float GetAspectRatio() const noexcept { return static_cast<float>(width) / height; }

public:
    int width = 1920;
    int height = 1080;
    Vector3f backgroundColor = Vector3f();
    std::vector<std::shared_ptr<Object>> objects;
};

#endif // Scene_HPP