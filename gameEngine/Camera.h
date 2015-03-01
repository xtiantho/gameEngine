

#ifndef __GameEngine__Camera__
#define __GameEngine__Camera__

#include "Math3d.h"
#include <stdio.h>
#include "Input.h"

class Camera
{
public:
    static vec3f yAxis;
    
    Camera();
    Camera(const vec3f& pos, const vec3f& forward, const vec3f& up);
    void move(const vec3f& dir, float amt);
    vec3f getLeft();
    vec3f getRight();
    vec3f getForward();
    vec3f getUp();
    vec3f getPos();
    void rotateX(const float& angle);
    void rotateY(const float& angle);
    void processInput(const Input& input, const float& delta);
    void update(float delta);
private:
    float temp;
    vec3f m_pos;
    vec3f m_forward;
    vec3f m_up;
};

#endif
