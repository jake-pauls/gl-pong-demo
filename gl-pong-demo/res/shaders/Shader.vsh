#shader vertex
#version 300 es

layout(location = 0) in vec4 position;

out vec4 v_color;

uniform vec4 color;
uniform mat4 modelViewProjectionMatrix;

void main()
{
    v_color = color;
    
    gl_Position = modelViewProjectionMatrix * position;
}
