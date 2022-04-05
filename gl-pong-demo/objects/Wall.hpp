//
//  Wall.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-04.
//

#ifndef Wall_hpp
#define Wall_hpp

#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2Body.h"

#include "SpriteRenderer.hpp"
#include "Shader.hpp"

class Wall
{
public:
    Wall();
    Wall(SpriteRenderer* sprite);
    
    void Update(glm::mat4 viewProjectionMatrix, b2Body* physicsBody);
    void Draw(Shader* shaderProgram);
    
private:
    SpriteRenderer* _sprite;
    
    glm::mat4 _mvpMatrix, _modelMatrix;
};

#endif /* Wall_hpp */
