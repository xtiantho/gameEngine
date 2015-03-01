

#ifndef __GameEngine__Material__
#define __GameEngine__Material__

#include <stdio.h>
#include "Texture.h"
#include "Math3d.h"

struct Material
{
    Material(const std::string& texName, const vec3f& color);
    Material(const std::string& texName, const vec3f& color, const float& specularIntensity, const float& specularExponent);
    ~Material();

    Texture* m_texture;
    vec3f m_color;
    float m_specularIntensity;
    float m_specularPower;
};

#endif 
