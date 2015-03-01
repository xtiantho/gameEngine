#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;
varying vec4 color0;

uniform mat4 transform;
uniform mat4 transformProjected;

void main()
{
    
    gl_Position = transformProjected * vec4(position, 1.0);
    texCoord0 = texCoord;
    
    //HAVE TO TRANSLATE THE NORMALS
    //normal0 = normal;
    color0 = vec4(normal, 1.0);
    normal0 = (transform * vec4(normal, 0.0)).xyz;
    worldPos0 = (transform * vec4(position, 1.0)).xyz;
}