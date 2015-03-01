
#ifndef __GameEngine__BaseLight__
#define __GameEngine__BaseLight__

#include <stdio.h>
#include "Math3d.h"

struct Attenuation
{
    inline Attenuation(const float& c, const float& l, const float& e) :
    constant(c), linear(l), exponent(e) {}
    
    float constant;
    float linear;
    float exponent;
};

//Base light structure
struct BaseLight
{
    inline BaseLight(const vec3f& color, const float& intensity) : color(color),
    intensity(intensity) {}
    
    vec3f     color;
    float     intensity;
};

struct DirectionalLight : public BaseLight
{
    inline DirectionalLight(BaseLight bLight, const vec3f& direction) :
    BaseLight(bLight), direction(direction.normalized()) {}
    
    vec3f    direction;
};

struct PointLight : public BaseLight
{
    inline PointLight(const BaseLight& bLight, const Attenuation& a, const vec3f& p, const float& f) :
    BaseLight(bLight), atten(a), position(p), range(f) {}
    
    Attenuation atten;
    vec3f       position;
    float       range;
};

struct SpotLight : public PointLight
{
    inline SpotLight(const PointLight& pLight, const vec3f& d, const float& c) :
    PointLight(pLight), direction(d), cutoff(c) {}
    
    vec3f   direction;
    float   cutoff;
};


#endif
