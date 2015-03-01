
#ifndef __GameEngine__Texture__
#define __GameEngine__Texture__

#include <stdio.h>
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>

class Texture
{
public:
    Texture(const std::string& fileName, GLenum textureTarget, GLfloat filter);
    ~Texture();
    int getId() const;
    void bind() const;
private:
    GLuint m_textureID;
    GLenum m_textureTarget;
    
    void init(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter);
    void setTextures(bool enabled);

};

#endif 
