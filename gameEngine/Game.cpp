
#include "Game.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "Vertex.h"

Game::Game() : m_material("test3.jpg", vec3f(1,1,1), 1, 8)
{
    temp = 0.0f;
    
    float fieldDepth = 10.0f;
    float fieldWidth = 10.0f;
    
    std::vector<Vertex> data;
    std::vector<int> indices;
    
    data.push_back(Vertex(vec3f(-fieldWidth, 0.0f, -fieldDepth), vec2f(0.0f, 0.0f)));
    data.push_back(Vertex(vec3f(-fieldWidth, 0.0f, fieldDepth * 3), vec2f(0.0f, 1.0f)));
    data.push_back(Vertex(vec3f(fieldWidth * 3, 0.0f, -fieldDepth), vec2f(1.0f, 0.0f)));
        data.push_back(Vertex(vec3f(fieldWidth * 3, 0.0f, fieldDepth * 3),vec2f(1.0f, 1.0f)));
    
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(3);
    
    //initialize the mesh the the data to create the buffer objects
    //here we are sending vertices, indices, and we want to calculate normals
    m_mesh.initMesh(data, indices, true);
    
    //these two functions set up the static member variables that persist through
    //the entire game's existance
    Transform::initProjection(70, 800, 600, 0.1f, 1000);
    Transform::setCamera(&m_camera);
    
    m_transform.setTransform(-5.0f, -5.0f, 10.0f);
    
    m_shader.setAmbient(vec3f(0.2f,0.2f,0.2f));
    m_shader.setDirectionalLight(DirectionalLight(BaseLight(vec3f(0.5,0.5,0.5), 0.2f), vec3f(1,1,1)));
    
    PointLight pLight1(BaseLight(vec3f(1,0,0), 0.8f), Attenuation(0, 0, 1), vec3f(-2, -4, 9),10);
    PointLight pLight2(BaseLight(vec3f(0,0,1), 0.8f), Attenuation(0, 0, 1), vec3f(2, -4, 9),10);
    
    PointLight pLight3(BaseLight(vec3f(1,1,1), 0.8f), Attenuation(0, 0, 0.1f), vec3f(0, -4.5, 5),30);
    
    SpotLight sLight(pLight3, vec3f(1,1,1), 0.7f);
    std::vector<PointLight> pLights = {pLight1, pLight2};
    std::vector<SpotLight> sLights = {sLight};
    m_shader.setPointLights(pLights);
    m_shader.setSpotLights(sLights);
    
}

Game::~Game()
{
    //dtor
}

void Game::processInput(const Input& input, float delta)
{
    m_camera.processInput(input, delta);
    
}

void Game::render()
{
    m_shader.bind();
    
    //set the uniforms after bind.
    m_shader.updateUniforms(m_transform.getTransformation(),
                            m_transform.getProjectedTransformation(),
                            m_transform.getCamera(),
                            m_material);
    m_mesh.draw();
}

void Game::update(float delta)
{
    temp += delta;
    float s = (float) sin(temp);

}
