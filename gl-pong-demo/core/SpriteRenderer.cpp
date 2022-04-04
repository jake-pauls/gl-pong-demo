//
//  SpriteRenderer.cpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-03.
//

#include "SpriteRenderer.hpp"
#include "Assert.hpp"

SpriteRenderer::SpriteRenderer()
{ }

void SpriteRenderer::SetupSprite(SpriteData data)
{
    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));
    
    // Positions
    GL_CALL(glGenBuffers(1, &VBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, data.verticesSize, data.vertices, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *) 0));
    
    // Textures
    GL_CALL(glGenBuffers(1, &TBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, TBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, data.texturesSize, data.textures, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *) 0));
   
    // Unbind VAO
    GL_CALL(glBindVertexArray(0));
}

void SpriteRenderer::CreateCircleSprite(std::vector<float>& vertices, float x, float y, float radius)
{
    float pi2 = 6.28318530718;
    float fSize = vertices.size();
    float alpha = 1 / fSize * pi2;
    
    const float cosA = cos(alpha);
    const float sinA = sin(alpha);
    
    float curX = radius;
    float curY = 0;
    
    for (unsigned int i = 0; i < vertices.size(); i += 2)
    {
        vertices[i] = curX + x;
        vertices[i + 1] = curY + y;
        
        float nCurX = cosA * curX - sinA * curY;
        curY = sinA * curX + cosA * curY;
        curX = nCurX;
    }
}

void SpriteRenderer::CreateCircleSprite2(std::vector<float>& vertices, float numberOfPoints, float radius)
{
    int theta = 0;
    int currentSize = 0;
    float x, y;
    
    while (theta < 360)
    {
        x = radius * cosf(theta * M_PI / 180.0f);
        y = radius * sinf(theta * M_PI / 180.0f);
        
        vertices[currentSize++] = x;
        vertices[currentSize++] = y;
        
        theta = theta + (360 / numberOfPoints);
    }
}
