

#include "Transform.h"

Camera* Transform::s_camera = NULL;
Matrix4f Transform::s_projectionMatrix;

Transform::Transform() : m_transform(0.0f, 0.0f, 0.0f),
m_scale(1.0f, 1.0f, 1.0f), m_rotation(0.0f, 0.0f, 0.0f)
{
    
}

vec3f* Transform::getTransform()
{
    return &m_transform;
}

void Transform::setTransform(const vec3f& r)
{
    m_transform = r;
}

void Transform::setTransform(const float& x, const float& y, const float& z)
{
    m_transform = vec3f(x, y, z);
}

Matrix4f Transform::getTransformation()
{
    Matrix4f matTranslation, matRotation, matScale;
    matTranslation.initTranslation(m_transform.getX(), m_transform.getY(), m_transform.getZ());
    matRotation.initRotationEuler(m_rotation.getX(), m_rotation.getY(), m_rotation.getZ());
    matScale.initScale(m_scale.getX(), m_scale.getY(), m_scale.getZ());

    return matTranslation * matRotation * matScale;
}

void Transform::initProjection(const float& fov, const float& width, const float& height, const float& zNear, const float& zFar)
{
    s_projectionMatrix.initProjection(fov, width, height, zNear, zFar);
}

Matrix4f Transform::getProjectedTransformation()
{
    Matrix4f transformationMatrix = getTransformation();
    Matrix4f cameraRotation, cameraTranslation;
    cameraRotation.initCamera(s_camera->getForward(), s_camera->getUp());
    cameraTranslation.initTranslation(-1*s_camera->getPos().getX(),
                                      -1*s_camera->getPos().getY(),
                                      -1*s_camera->getPos().getZ());
    
    Matrix4f result = s_projectionMatrix * cameraRotation * cameraTranslation * transformationMatrix;
    
    return result;
}

vec3f* Transform::getRotation()
{
    return &m_rotation;
}

void Transform::setRotation(const vec3f& r)
{
    m_rotation = r;
}

void Transform::setRotation(const float& x, const float& y, const float& z)
{
    m_rotation = vec3f(x, y, z);
}

void Transform::setScale(const vec3f& r)
{
    m_scale = r;
}

void Transform::setScale(const float& x, const float& y, const float &z)
{
    m_scale = vec3f(x, y, z);
}

Camera* Transform::getCamera()
{
    return s_camera;
}

void Transform::setCamera(Camera* camera)
{
    s_camera = camera;
}