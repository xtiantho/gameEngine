#version 120

//varying vec4 color;
varying vec2 texCoord0;

uniform vec3 color;
uniform sampler2D diffuse;

void main() 
{
    vec4 TexColor = texture2D(diffuse, texCoord0.xy);
    
    if (TexColor == vec4(0,0,0,0))
    {
        gl_FragColor = vec4(color, 1);
    }
    else
    {
        gl_FragColor = texture2D(diffuse, texCoord0.xy) * vec4(color, 1.0);
    }
}