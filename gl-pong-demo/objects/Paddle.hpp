//
//  Paddle.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-01.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include <OpenGLES/ES3/gl.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2Body.h"

#include "SpriteRenderer.hpp"
#include "Shader.hpp"

#define PADDLE_WIDTH   170.0f
#define PADDLE_HEIGHT   40.0f

#define PADDLE_STARTING_X          320.0f
#define PADDLE_PLAYER_STARTING_Y    50.0f
#define PADDLE_ENEMY_STARTING_Y   1086.0f

class Paddle
{
public:
    Paddle();
    Paddle(SpriteRenderer* sprite);
    
    void Update(glm::mat4 viewProjectionMatrix, b2Body* physicsBody);
    void Draw(Shader* shaderProgram);
    
private:
    SpriteRenderer* _sprite;
    
    glm::mat4 _mvpMatrix, _modelMatrix;
    
    glm::vec3 _pos;
};

#endif /* Paddle_hpp */
