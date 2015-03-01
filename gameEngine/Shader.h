
#ifndef __GameEngine__Shader__
#define __GameEngine__Shader__

#include <stdio.h>
#include <string>
#include <unordered_map>
#include "Math3d.h"
#include "Material.h"

//Base class for the shaders
class Shader
{
public:
    Shader();
    ~Shader();
    void addVertexShader(const std::string& text);
    void addFragmentShader(const std::string& text);
    void addProgram(const std::string& text, int type);
    void addUniform(const std::string& uniform);
    void compileShader() const;
    void bind() const;
    void setUniformi(const std::string& name, const int& value) const;
    void setUniformf(const std::string& name, const float& value) const;
    void setUniform(const std::string& name, const vec3f& value) const;
    void setUniform(const std::string& name, const Matrix4f& value) const;
    virtual void updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, const Material& material) {}
private:
    int m_program;
    std::unordered_map<std::string, int> m_uniforms;
    std::string loadShader(const std::string& fileName) const;
};

#endif 
