#shader fragment
#version 300 es

precision highp float;

out vec4 FragColor;

in vec4 v_color;
in vec2 v_textures;

uniform bool useTexture;
uniform sampler2D texSampler;

void main()
{
    vec4 fc = vec4(0.0f);
    
    if (useTexture) {
        vec4 texColor = texture(texSampler, v_textures);
        
        if (texColor.a < 0.1)
            discard;
        
        fc = texColor * vec4(1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        fc = v_color;
    }
    
    FragColor = fc;
}

