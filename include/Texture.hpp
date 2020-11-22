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

#endif // TEXTURE_HPP