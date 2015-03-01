

#ifndef __GameEngine__Mesh__
#define __GameEngine__Mesh__

#include <stdio.h>
#include "Vertex.h"
#include <vector>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>

class Mesh
{
public:
    Mesh();
    ~Mesh();
    
    void initMesh(const std::string& fileName);
    void initMesh(std::vector<Vertex>& vertices, const std::vector<int>&indices);
    void initMesh(std::vector<Vertex>& vertices, const std::vector<int>&indices, bool normals);
    
    void draw();
private:
    int    m_size; //how much data we have
    GLuint m_vbo;  //vertex buffer object
    GLuint m_ibo;  //index buffer object (an array of integers)
                   //every three of the integers will be a triangle
    
    void calcNormals(std::vector<Vertex>& vertices, const std::vector<int>&indices);
    void addVertices(std::vector<Vertex>& vertices, const std::vector<int>&indices, bool normals);
    void loadMesh(const std::string& fileName);
    void initMeshData();
};

#endif 
