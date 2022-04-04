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

#include "SpriteRenderer.hpp"
#include "Shader.hpp"

#define PADDLE_SCALE_X  170.0f
#define PADDLE_SCALE_Y   40.0f

#define PADDLE_STARTING_X         (PADDLE_SCALE_X / 2) * -1
#define PADDLE_PLAYER_STARTING_Y  -450.0f

class Paddle
{
public:
    Paddle();
    Paddle(SpriteRenderer* sprite, glm::vec3 pos);
    
    void Update(glm::mat4 viewProjectionMatrix);
    void Draw(Shader* shaderProgram);
    
private:
    SpriteRenderer* _sprite;
    
    glm::mat4 _mvpMatrix, _modelMatrix;
    
    glm::vec3 _pos;
};

#endif /* Paddle_hpp */
