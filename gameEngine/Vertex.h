
#ifndef __GameEngine__Vertex__
#define __GameEngine__Vertex__

#include <stdio.h>
#include "Math3d.h"

struct Vertex
{
public:
    //static => shared by all instances of the class and doesn't need to be instantiated to be accessed ... Vertex::SIZE is OKAY.
    //const => cannot be changed
    //we have three floating points in this vertex class.
    //now it is equal to five since we have two more pieces of data from texcoords..
    static const int SIZE = 5;
    
    inline Vertex(const vec3f& pos) : Vertex(pos, vec2f(0,0)) {}
    inline Vertex(const vec3f& pos, const vec2f& texCoord) :
        m_normal(0,0,0), m_pos(pos), m_texCoord(texCoord) {}
    inline Vertex(float x, float y, float z) : Vertex(vec3f(x,y,z), vec2f(0,0)) {}

    vec3f m_pos;
    vec2f m_texCoord;
    vec3f m_normal;
};

#endif
