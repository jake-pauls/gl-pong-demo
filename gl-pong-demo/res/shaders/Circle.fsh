#shader fragment
#version 300 es

precision highp float;

out vec4 FragColor;

in highp vec2 textureCoordinate;
in vec4 v_color;

const highp vec2 center = vec2(0.5, 0.5);
const highp float radius = 0.5;

void main()
{
    highp float distanceFromCenter = distance(center, textureCoordinate);
    lowp float checkIfInCircle = step(distanceFromCenter, radius);
    
    FragColor = v_color * checkIfInCircle;
}

