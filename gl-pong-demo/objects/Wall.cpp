//
//  Wall.cpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-04.
//

#include "Wall.hpp"

Wall::Wall()
{ }

Wall::Wall(SpriteRenderer* sprite)
    : _sprite(sprite)
{ }

void Wall::Update(glm::mat4 viewProjectionMatrix, b2Body *physicsBody)
{
    
}

void Wall::Draw(Shader* shaderProgram)
{
    
}
