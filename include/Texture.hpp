#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "math.hpp"

class Texture
{
public:
    virtual Vector3f value(float u, float v, const Vector3f& p) const = 0;
    
};
// single RGB
class ConstantTexture : public Texture
{
public:
    ConstantTexture() {}
    ConstantTexture(Vector3f col) : color(col) {}

    Vector3f value(float u, float v, const Vector3f& p) const override
    {
        return color;
    }

private:
    Vector3f color;

};

class CheckerBoard : public Texture
{
public:
    CheckerBoard() {}
    CheckerBoard(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1) : even(t0), odd(t1) {}

    Vector3f value(float u, float v, const Vector3f& p) const override
    {
        auto sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
        if (sines < 0)
        {
            return odd->value(u, v, p);
        }
        else
        {
            return even->value(u, v, p);
        }
    }

private:
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;
};

class ImageTexture : public Texture
{
public:
    ImageTexture(unsigned char *pixels, int _x, int _y) : data(pixels), x(_x), y(_y) {}

    ~ImageTexture() {}
    Vector3f value(float u, float v, const Vector3f& p) const override
    {
        if (data == nullptr)
        {
            return Vector3f(0,1,1);
        }

        auto i = static_cast<int>(u * x);
        auto j = static_cast<int>((1-v) * y - 0.001);

        if (i < 0) i = 0;
        if (j < 0) j = 0;
        if (i > x-1) i = x - 1;
        if (j > y-1) j = y - 1;

        auto r = static_cast<int>(data[3 * i + 3 * x * j + 0]) / 255.0f;
        auto g = static_cast<int>(data[3 * i + 3 * x * j + 1]) / 255.0f;
        auto b = static_cast<int>(data[3 * i + 3 * x * j + 2]) / 255.0f;

        return Vector3f(r, g, b);
    }

public:
    unsigned char *data = nullptr;
    int x, y;
};

#endif // TEXTURE_HPP