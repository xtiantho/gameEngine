#version 120

attribute vec3 position;
attribute vec2 texCoord;

//varying vec4 color;
varying vec2 texCoord0;

//uniform float uniFloat;
uniform mat4 transform;

void main()
{
    //color = vec4(clamp(position, 0.0, 1.0), 1.0);
	gl_Position = transform * vec4(position, 1.0);
    texCoord0 = texCoord;
}