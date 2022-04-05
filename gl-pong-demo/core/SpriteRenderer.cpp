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
