

#ifndef __GameEngine__BasicShader__
#define __GameEngine__BasicShader__

#include <stdio.h>
#include "Shader.h"
#include "Material.h"

class BasicShader : public Shader
{
public:
    BasicShader();
    void updateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, const Material& material);
private:
};

#endif 
