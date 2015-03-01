

#ifndef __GameEngine__PhongShader__
#define __GameEngine__PhongShader__

#include <stdio.h>
#include "Shader.h"
#include "BaseLight.h"
#include "Camera.h"
#include <vector>

#include <iostream>

class PhongShader : public Shader
{
public:
    PhongShader();
    void updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Camera* camera,
                        const Material& material);
    void setAmbient(const vec3f& ambientLight);
    void setUniform(const std::string& name,  DirectionalLight& directionalLight) const;
    void setUniformPoint(const std::string& name, PointLight& pointLight) const;
    void setUniformBase(const std::string& name,  BaseLight& baseLight) const;
    void setUniform(const std::string& name,  SpotLight& spotLight) const;
    void setDirectionalLight(const DirectionalLight& directionalLight);
    void setPointLights(const std::vector<PointLight>& pointLights);
    void setSpotLights(const std::vector<SpotLight>& spotLights);
private:
    static const int        MAX_POINT_LIGHTS = 4;
    static const int        MAX_SPOT_LIGHTS = 4;
    vec3f                   m_ambientLight;
    DirectionalLight        m_directionalLight;
    std::vector<PointLight> m_pointLights;
    std::vector<SpotLight>  m_spotLights;
};

#endif 
