//
//  Ball.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-03.
//

#ifndef Ball_hpp
#define Ball_hpp

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

#define BALL_STARTING_X   320.0f
#define BALL_STARTING_Y   568.0f
#define BALL_RADIUS        25.0f

class Ball
{
public:
    Ball();
    Ball(SpriteRenderer* sprite);
    
    void Update(glm::mat4 viewProjectionMatrix, b2Body* physicsBody);
    void Draw(Shader* shaderProgram);
    
private:
    SpriteRenderer* _sprite;
    
    glm::mat4 _mvpMatrix, _modelMatrix;
};

#endif /* Ball_hpp */
