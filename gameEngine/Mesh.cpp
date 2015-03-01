
#include <iostream>
#include "Mesh.h"
#include <fstream>
#include <sstream>

Mesh::Mesh()
{
    initMeshData();
}

void Mesh::initMesh(const std::string& fileName)
{
    //mesh loader doesn't do texcoords or normals yet
    loadMesh(fileName);
}

void Mesh::initMesh(std::vector<Vertex>& vertices, const std::vector<int>&indices)
{
    addVertices(vertices, indices, false);
}

void Mesh::initMesh(std::vector<Vertex>& vertices, const std::vector<int>&indices, bool normals)
{
    addVertices(vertices, indices, normals);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void Mesh::initMeshData()
{
    m_size = 0;
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);
}

void Mesh::addVertices(std::vector<Vertex>& vertices, const std::vector<int>&indices, bool normals)
{
    if (normals)
    {
        calcNormals(vertices, indices);
    }
    
    m_size = indices.size();
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); //create buffer object
    
    //send in the data of vertices to the GPU
    //since the vector is essentially an array,
    //we can send in the first element of the vector since all of the data
    //is set up in memory contiguously
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(Vertex),
                 &vertices[0],
                 GL_STATIC_DRAW);
    
    //add our indices the to GPU
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(int),
                 &indices[0],
                 GL_STATIC_DRAW);
}

void Mesh::draw()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    
    //tells opengl how to interpret the data
    
    //param1 - The attrib number
    //param2 - how many floats we have
    //param4 - the stride.. it tells the gpu where to find the next set of data
    //param5 - how far into the vertex the data is located
    //  for the position data, it's located at offset 0
    //  for the texcoord data, the data is located 12 bytes into data
    
    
    //------------------------------------------------------------------
    //      |        Vertex1 data         |        Vertex2 data         |
    //------------------------------------------------------------------
    //byte  0                12          20
    //======|=====|=====|=====|=====|=====|=====|=====|=====|=====|=====|
    //      |pos.x|pos.y|pos.z|tex.u|tex.v|pos.x|pos.y|pos.z|tex.u|tex.v|
    //======|=====|=====|=====|=====|=====|=====|=====|=====|=====|=====|
    
    //stride = sizeof(Vertex) = 32 bytes with the normals now
    
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (GLvoid*) sizeof(vec3f));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (GLvoid*) (sizeof(vec3f) + sizeof(vec2f)));
    
    
    //don't need draw arrays cuz we are drawing array of indices instead
    //glDrawArrays(GL_TRIANGLES, 0, m_size);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

//Calculate the normals for each vertex.
//
//            i2
//           ^
//          /
//      v2 /
//        /
//       /     v1
//      i0 --------> i1
//
//take a triad of indices, representing a triangle face.
//calculate two vectors from one of the indices.
//take the cross product of those vectors to get a perpendicular one
//
//NOTE:
//  Since we are getting the normals for the vertices, it's important to note that
//  we have to add all the normals calculated for each vertex.
//  Then, at the end, we have to normalize them all.
void Mesh::calcNormals(std::vector<Vertex>& vertices, const std::vector<int>&indices)
{
    for (int i = 0; i < indices.size(); i+=3)
    {
        int i0 = indices[i];
        int i1 = indices[i+1];
        int i2 = indices[i+2];
        
        vec3f v1 = vertices[i1].m_pos - vertices[i0].m_pos;
        vec3f v2 = vertices[i2].m_pos - vertices[i0].m_pos;
        
        vec3f normal = v1.cross(v2);
        normal = normal.normalized();
        
        vertices[i0].m_normal = vertices[i0].m_normal + normal;
        vertices[i1].m_normal = vertices[i1].m_normal + normal;
        vertices[i2].m_normal = vertices[i2].m_normal + normal;
    }
    
    //normalize all the normals
    for (int i = 0; i < vertices.size(); i++)
    {
        vec3f norm = vertices[i].m_normal;
         norm = norm.normalized();
        vertices[i].m_normal = norm;
    }
}

void Mesh::loadMesh(const std::string& fileName)
{
    std::istringstream iss(fileName);
    std::vector<std::string> tokens;
    std::string token;
    while (getline(iss, token, '.')) {
        if (!token.empty())
            tokens.push_back(token);
    }
    
    std::string ext = tokens[tokens.size() - 1];
    if (ext != "obj")
    {
        std::cerr << "Error: File format not supported for mesh data." << std::endl;
        exit(1);
    }
    
    std::vector<Vertex> vertices;
    std::vector<int>    indices;
    
    std::string line;
    
    std::string path = "/Users/christianthorenfeldt/Documents/Projects/gameEngine/DerivedData/gameEngine/Build/Products/Debug/resources/models/" + fileName;
    
    std::ifstream infile(path);
    
    float x, y, z;
    int x_, y_, z_;
    
    while(getline(infile, line))
    {
        if (line.substr(0, 2) == "v ")
        {
            std::istringstream s(line.substr(2));
            s >> x; s >> y; s >> z;
            vertices.push_back(Vertex(x, y, z));
        }
        else if (line.substr(0, 2) == "f ")
        {
            std::istringstream s(line.substr(2));
            s >> x_; s >> y_; s >> z_;
            x_--; y_--; z_--;
            indices.push_back(x_);
            indices.push_back(y_);
            indices.push_back(z_);
        }
        else if(line[0] == '#') { /* ignore this line */ }
        else { /* ignore the rest */ }
    }
    
    addVertices(vertices, indices, true);
}

