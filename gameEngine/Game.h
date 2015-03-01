
#ifndef __GameEngine__Game__
#define __GameEngine__Game__

#include <stdio.h>
#include "Input.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "Texture.h"
#include "BasicShader.h"
#include "PhongShader.h"

class Game
{
public:
    Game();
    ~Game();
    
    void processInput(const Input& input, float delta);
    void render();
    void update(float delta);
protected:
private:
    //TODO: get rid of the use of pointers in this class
    Mesh        m_mesh;
    PhongShader m_shader;
    Transform   m_transform;
    Material    m_material;
    Camera      m_camera;
    float       temp;
};

#endif 
