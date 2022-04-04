//
//  Paddle.cpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-01.
//

#include "Paddle.hpp"
#include "Assert.hpp"

Paddle::Paddle()
{ }

Paddle::Paddle(SpriteRenderer* sprite, glm::vec3 pos)
    : _sprite(sprite), _pos(pos)
{ }

void Paddle::Update(glm::mat4 viewProjectionMatrix)
{
    _modelMatrix = glm::translate(glm::mat4(1.0f), _pos);
    _modelMatrix = glm::scale(_modelMatrix, glm::vec3(PADDLE_SCALE_X, PADDLE_SCALE_Y, 1.0f));
    
    _mvpMatrix = viewProjectionMatrix * _modelMatrix;
}

void Paddle::Draw(Shader* shaderProgram)
{
    shaderProgram->Bind();
    
    shaderProgram->SetUniformMatrix4fv("_mvpMatrix", glm::value_ptr(_mvpMatrix));
    shaderProgram->SetUniform4f("_color", 1.0f, 1.0f, 1.0f, 1.0);
    
    GL_CALL(glBindVertexArray(_sprite->VAO));
    GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
    GL_CALL(glBindVertexArray(0));
}
