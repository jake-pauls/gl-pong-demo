//
//  SpriteRenderer.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-03.
//

#ifndef SpriteRenderer_hpp
#define SpriteRenderer_hpp

#include <vector>

#include <glm/glm.hpp>

#include "Shader.hpp"

class SpriteRenderer
{
public:
    struct SpriteData {
        const float* vertices;
        float verticesSize;
        const float* textures;
        float texturesSize;
    };
    
    SpriteRenderer();
    
    void SetupSprite(SpriteData sprite);
    void CreateCircleSprite(std::vector<float>& vertices, float x, float y, float radius);
    void CreateCircleSprite2(std::vector<float>& vertices, float numberOfPoints, float radius);
    void CreateCircle(std::vector<float>& vertices, float numberOfPoints, float radius);
    
    GLuint VAO, VBO, TBO;
};

#endif /* SpriteRenderer_hpp */
