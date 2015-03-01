
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& fileName, GLenum textureTarget, GLfloat filter)
{
    std::string path = "/Users/christianthorenfeldt/Documents/Projects/gameEngine/DerivedData/gameEngine/Build/Products/Debug/resources/textures/" + fileName;
    
    int x,y,n;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 4);
    if (data == NULL) {
        // error
        std::cerr << "Error, data was null" << std::endl;
    } else {
        // process
        init(x,y,data,textureTarget,filter);
    }
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}

void Texture::setTextures(bool enabled)
{
    if (enabled)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
}


void Texture::bind() const
{
    glBindTexture(m_textureTarget, m_textureID);
}

int Texture::getId() const
{
    return m_textureID;
}

void Texture::init(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
    m_textureTarget = textureTarget;
    
    if(width > 0 && height > 0 && data != 0)
    {
        glGenTextures(1, &m_textureID);
        glBindTexture(textureTarget, m_textureID);
        glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter);
        glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        m_textureID = 0;
    }
}