

#include "BasicShader.h"

BasicShader::BasicShader() : Shader()
{
    addVertexShader("basicVertex.vs");
    addFragmentShader("basicFragment.fs");
    compileShader();
    
    //these variables are inside glsl files as uniforms
    addUniform("transform");
    addUniform("color");
}

void BasicShader::updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, const Material& material)
{
    if (material.m_texture != NULL)
    {
        material.m_texture->bind();
    }
    else
    {
        //TODO: unbind texture
    }
    
    setUniform("transform", projectedMatrix);
    setUniform("color", material.m_color);
}

