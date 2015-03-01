

#ifndef __GameEngine__Transform__
#define __GameEngine__Transform__

#include <stdio.h>
#include "Math3d.h"
#include "Camera.h"

class Transform
{
public:
    Transform();
    vec3f* getRotation();
    vec3f* getTransform();
    Matrix4f getProjectedTransformation();
    Matrix4f getTransformation();
    Camera* getCamera();
    
    static void setCamera(Camera* camera);
    static void initProjection(const float& fov, const float& width, const float& height, const float& zNear, const float& zFar);
    
    void setRotation(const vec3f& r);
    void setRotation(const float& x, const float& y, const float& z);
    void setTransform(const vec3f& r);
    void setTransform(const float& x, const float& y, const float& z);
    void setScale(const vec3f& r);
    void setScale(const float& x, const float& y, const float& z);
private:
    vec3f           m_transform;
    vec3f           m_rotation;
    vec3f           m_scale;
    static Matrix4f s_projectionMatrix;
    static Camera*  s_camera;
};

#endif
