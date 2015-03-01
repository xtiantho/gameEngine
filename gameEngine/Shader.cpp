

#include "Shader.h"
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader()
{
    m_program = glCreateProgram();
    
    if (m_program == 0)
    {
        std::cerr << "Shader program creation failed." << std::endl;
        exit(1);
    }
}

Shader::~Shader()
{
    glDeleteShader(m_program);
}

void Shader::bind() const
{
    glUseProgram(m_program);
}

void Shader::compileShader() const
{
    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");
    
    glLinkProgram(m_program);
    glValidateProgram(m_program);
}

void Shader::addVertexShader(const std::string& text)
{
    addProgram(loadShader(text), GL_VERTEX_SHADER);
}

void Shader::addFragmentShader(const std::string& text)
{
    addProgram(loadShader(text), GL_FRAGMENT_SHADER);
}

void Shader::addProgram(const std::string& text, int type)
{
    int shader = glCreateShader(type);
    
    if (shader == 0)
    {
        std::cerr << "Shader program creation failed." << std::endl;
        exit(1);
    }
    
    //GLchar* const files[] = { text.c_str() };
    const char* data = text.c_str();
    
    glShaderSource(shader, 1, &data, NULL); //feed the data
    glCompileShader(shader); //compile the shader
    
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar InfoLog[1024];
        
        glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", shader, InfoLog);
        
        exit(1);
    }
    
    glAttachShader(m_program, shader);
}

void Shader::addUniform(const std::string& uniform)
{
    std::cout << "adding the following uniform: " + uniform << std::endl;
    
    unsigned int uniformLoc = glGetUniformLocation(m_program, uniform.c_str());
    
    if (uniformLoc == 0xFFFFFFFF)
    {
        std::cerr << "Could not find the location of uniform: " + uniform << std::endl;
        exit(1);
    }
    
    m_uniforms[uniform] = uniformLoc;
}

void Shader::setUniformi(const std::string& name, const int& value) const
{
    glUniform1i(m_uniforms.at(name), value);
}

void Shader::setUniformf(const std::string& name, const float& value) const
{
    glUniform1f(m_uniforms.at(name), value);
}

void Shader::setUniform(const std::string& name, const vec3f& value) const
{
    glUniform3f(m_uniforms.at(name), value.getX(), value.getY(), value.getZ());
}

void Shader::setUniform(const std::string& name, const Matrix4f& value) const
{
    glUniformMatrix4fv(m_uniforms.at(name), 1, GL_FALSE, &(value[0][0]));
}

std::string Shader::loadShader(const std::string& fileName) const
{
    std::string result, line;
    result = "";
    
    std::string path = "/Users/christianthorenfeldt/Documents/Projects/gameEngine/DerivedData/gameEngine/Build/Products/Debug/resources/shaders/" + fileName;
    std::ifstream infile(path);
    if (infile)
    {
        while(getline(infile, line))
        {
            std::cout << line << std::endl;
            result += line;
            result += '\n';
        }
        return result;
    }
    else
    {
        std::cerr << "File could not be opened!!!" << std::endl;
        exit(1);
    }
}