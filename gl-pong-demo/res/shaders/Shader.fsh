#shader fragment
#version 300 es

precision highp float;

out vec4 FragColor;

in vec4 v_color;

void main()
{
    FragColor = v_color;
}

