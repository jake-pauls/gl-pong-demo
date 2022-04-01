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

#include "Mesh.hpp"
#include "Shader.hpp"

class Paddle
{
public:
    Paddle();
    Paddle(Mesh* mesh, glm::vec3 pos);
    
    void Update(glm::mat4 projectionMatrix);
    void Draw(Shader* shaderProgram);
    
private:
    Mesh* _mesh;
    
    glm::mat4 _mvpMatrix, _modelMatrix;
    
    glm::vec3 _pos;
};

#endif /* Paddle_hpp */
