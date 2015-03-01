

#include "Material.h"


Material::Material(const std::string& texName, const vec3f& color) : m_color(color)
{
    //m_texture = new Texture(texName, GL_TEXTURE_2D, GL_LINEAR);
    
    //THIS DOES NOT WORK..
    //It creates a temporary object and then deletes it.. does not modify "this" object
    Material(texName, color, 2, 32);
}

Material::Material(const std::string& texName, const vec3f& color, const float& specularIntensity, const float& specularPower) :
    m_color(color),
    m_specularIntensity(specularIntensity),
    m_specularPower(specularPower)
{
    //TODO: if no texture
    if (texName == "")
    {
        
    }
    m_texture = new Texture(texName, GL_TEXTURE_2D, GL_LINEAR);
}

Material::~Material()
{
    delete m_texture;
}
