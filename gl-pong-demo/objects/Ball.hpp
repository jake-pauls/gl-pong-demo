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

#include "SpriteRenderer.hpp"
#include "Shader.hpp"

#define BALL_STARTING_X  (50.0f / 2) * -1

class Ball
{
public:
    Ball();
    Ball(SpriteRenderer* sprite, glm::vec3 pos);
    
    void Update(glm::mat4 viewProjectionMatrix);
    void Draw(Shader* shaderProgram);
    
private:
    SpriteRenderer* _sprite;
    
    glm::mat4 _mvpMatrix, _modelMatrix;
    
    glm::vec3 _pos;
};

#endif /* Ball_hpp */
