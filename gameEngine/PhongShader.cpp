

#include "PhongShader.h"
#include "Transform.h"
#include <sstream>


PhongShader::PhongShader() : Shader(), m_ambientLight(vec3f(0.1f,0.1f,0.1f)),
    m_directionalLight(BaseLight(vec3f(1,1,1), 0), vec3f(0,0,0))
{
    
    addVertexShader("phongVertex.vs");
    addFragmentShader("phongFragment.fs");
    compileShader();
    
    addUniform("transform");
    addUniform("transformProjected");
    addUniform("baseColor");
    addUniform("ambientLight");
    
    addUniform("directionalLight.base.color");
    addUniform("directionalLight.base.intensity");
    addUniform("directionalLight.direction");
    
    addUniform("specularIntensity");
    addUniform("specularPower");
    addUniform("eyePos");
    
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        std::ostringstream pointLightNameBuilder;
        pointLightNameBuilder << "pointLights[" << i << "]";
        std::string pointLightName = pointLightNameBuilder.str();
        
        addUniform(pointLightName + ".base.color");
        addUniform(pointLightName + ".base.intensity");
        addUniform(pointLightName + ".atten.constant");
        addUniform(pointLightName + ".atten.linear");
        addUniform(pointLightName + ".atten.exponent");
        addUniform(pointLightName + ".position");
        addUniform(pointLightName + ".range");
    }
    
    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
    {
        std::ostringstream spotLightNameBuilder;
        spotLightNameBuilder << "spotLights[" << i << "]";
        std::string spotLightName = spotLightNameBuilder.str();
        
        addUniform(spotLightName + ".pointLight.base.color");
        addUniform(spotLightName + ".pointLight.base.intensity");
        addUniform(spotLightName + ".pointLight.atten.constant");
        addUniform(spotLightName + ".pointLight.atten.linear");
        addUniform(spotLightName + ".pointLight.atten.exponent");
        addUniform(spotLightName + ".pointLight.position");
        addUniform(spotLightName + ".pointLight.range");
        addUniform(spotLightName + ".direction");
        addUniform(spotLightName + ".cutoff");
    }
}

void PhongShader::updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Camera* camera, const Material& material)
{
    if (material.m_texture != NULL)
    {
        material.m_texture->bind();
    }
    else
    {
        //unbind texture
    }
    
    Shader::setUniform("transform", worldMatrix);
    Shader::setUniform("transformProjected", projectedMatrix);
    Shader::setUniform("baseColor", material.m_color);
    Shader::setUniform("ambientLight", m_ambientLight);
    setUniform("directionalLight", m_directionalLight);
    for(int i = 0; i < m_pointLights.size(); i++)
    {
        std::ostringstream pointLightNameBuilder;
        pointLightNameBuilder << "pointLights[" << i << "]";
        std::string pointLightName = pointLightNameBuilder.str();
        
        setUniformPoint(pointLightName, m_pointLights[i]);
    }
    for (int i = 0; i < m_spotLights.size(); i++)
    {
        std::ostringstream spotLightNameBuilder;
        spotLightNameBuilder << "spotLights[" << i << "]";
        std::string spotLightName = spotLightNameBuilder.str();
        
        setUniform(spotLightName, m_spotLights[i]);
    }
    
    Shader::setUniformf("specularIntensity", material.m_specularIntensity);
    Shader::setUniformf("specularPower", material.m_specularPower);
    Shader::setUniform("eyePos", camera->getPos());
}

void PhongShader::setPointLights(const std::vector<PointLight>& pointLights)
{
    if (pointLights.size() > MAX_POINT_LIGHTS)
    {
        std::cerr << "Exceeded maximum allowed point lights" << std::endl;
        exit(1);
    }
    m_pointLights = pointLights;
}

void PhongShader::setSpotLights(const std::vector<SpotLight>& spotLights)
{
    if (spotLights.size() > MAX_SPOT_LIGHTS)
    {
        std::cerr << "Exceeded maximum allowed point lights" << std::endl;
        exit(1);
    }
    m_spotLights = spotLights;
}

void PhongShader::setDirectionalLight(const DirectionalLight& directionalLight)
{
    m_directionalLight = directionalLight;
}

void PhongShader::setAmbient(const vec3f& ambientLight)
{
    m_ambientLight = ambientLight;
}

void PhongShader::setUniformBase(const std::string& name, BaseLight& baseLight) const
{
    Shader::setUniform(name + ".color", baseLight.color);
    Shader::setUniformf(name + ".intensity", baseLight.intensity);
}

void PhongShader::setUniform(const std::string& name, DirectionalLight& directionalLight) const
{
    setUniformBase(name + ".base", directionalLight);
    Shader::setUniform(name + ".direction", directionalLight.direction);
}

void PhongShader::setUniformPoint(const std::string& name, PointLight& pointLight) const
{
    setUniformBase(name + ".base", pointLight);
    Shader::setUniformf(name + ".atten.constant", pointLight.atten.constant);
    Shader::setUniformf(name + ".atten.linear", pointLight.atten.linear);
    Shader::setUniformf(name + ".atten.exponent", pointLight.atten.exponent);
    Shader::setUniform(name + ".position", pointLight.position);
    Shader::setUniformf(name + ".range", pointLight.range);
}

void PhongShader::setUniform(const std::string& name, SpotLight& spotLight) const
{
    setUniformPoint(name + ".pointLight", spotLight);
    Shader::setUniform(name + ".direction", spotLight.direction);
    Shader::setUniformf(name + ".cutoff", spotLight.cutoff);
}

