#shader vertex
#version 300 es

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textures;

out vec4 v_color;

uniform vec4 _color;
uniform mat4 _mvpMatrix;

void main()
{
    v_color = _color;
    
    gl_Position = _mvpMatrix * vec4(position.xy, 0.0, 1.0);
}
