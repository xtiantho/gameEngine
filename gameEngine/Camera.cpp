
#include "Camera.h"
#include <iostream>

vec3f Camera::yAxis;

Camera::Camera(const vec3f& pos, const vec3f& forward, const vec3f& up) :
    m_pos(pos), m_forward(forward), m_up(up)
{
    temp = 0.0f;
    yAxis = vec3f(0,1,0);
    
    m_up = m_up.normalized();
    m_forward = m_forward.normalized();
}

Camera::Camera():Camera(vec3f(0,0,0), vec3f(0,0,1), vec3f(0,1,0)) {}

void Camera::move(const vec3f& dir, float amt)
{
    m_pos += dir*amt;
}

void Camera::rotateY(const float& angle)
{
    vec3f Haxis = yAxis.cross(m_forward);
    Haxis = Haxis.normalized();
    
    m_forward = m_forward.rotate(angle, yAxis);
    m_forward = m_forward.normalized();
    
    m_up = m_forward.cross(Haxis);
    m_up = m_up.normalized();
}

void Camera::rotateX(const float& angle)
{
    vec3f Haxis = yAxis.cross(m_forward);
    Haxis = Haxis.normalized();
    
    m_forward = m_forward.rotate(angle, Haxis);
    m_forward = m_forward.normalized();
    
    m_up = m_forward.cross(Haxis);
    m_up = m_up.normalized();
}

vec3f Camera::getLeft() 
{
    vec3f left = m_forward.cross(m_up);
    left = left.normalized();
    return left;
}

vec3f Camera::getRight()
{
    vec3f right = m_up.cross(m_forward);
    right = right.normalized();
    return right;
}

void Camera::processInput(const Input& input, const float& delta)
{
    float mvAmt = (float) 10 * delta;
    float rotAmt = (float) (100.0f * (1.0f/ 60.0f));
    
    if (input.getKey(input.KEY_W))
    {
        move(m_forward, mvAmt);
    }
    if (input.getKey(input.KEY_A))
    {
        move(getLeft(), mvAmt);
    }
    if (input.getKey(input.KEY_D))
    {
        move(getRight(), mvAmt);
    }
    if(input.getKey(input.KEY_S))
    {
        move(m_forward, -mvAmt);
    }
    
    if (input.getKey(input.KEY_UP))
    {
        rotateX(rotAmt);
    }
    if (input.getKey(input.KEY_DOWN))
    {
        rotateX(-rotAmt);
    }
    if (input.getKey(input.KEY_LEFT))
    {
        rotateY(-rotAmt);
    }
    if(input.getKey(input.KEY_RIGHT))
    {
        rotateY(rotAmt);
    }
    
}

void Camera::update(float delta)
{
    temp = 10 * delta;
    move(m_forward, -temp);
}

vec3f Camera::getForward() { return m_forward; }
vec3f Camera::getUp()      { return m_up; }
vec3f Camera::getPos()     { return m_pos; }