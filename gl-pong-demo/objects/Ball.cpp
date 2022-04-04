//
//  Ball.cpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-03.
//

#include "Ball.hpp"
#include "Assert.hpp"

Ball::Ball()
{ }

Ball::Ball(SpriteRenderer* sprite, glm::vec3 pos)
    : _sprite(sprite), _pos(pos)
{ }

void Ball::Update(glm::mat4 viewProjectionMatrix)
{
    _modelMatrix = glm::translate(glm::mat4(1.0f), _pos);
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _modelMatrix = glm::scale(_modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
    
    _mvpMatrix = viewProjectionMatrix * _modelMatrix;
}

void Ball::Draw(Shader* shaderProgram, float numberOfVertices)
{
    shaderProgram->Bind();
    
    shaderProgram->SetUniformMatrix4fv("_mvpMatrix", glm::value_ptr(_mvpMatrix));
    shaderProgram->SetUniform4f("_color", 1.0f, 1.0f, 1.0f, 1.0);
    
    GL_CALL(glBindVertexArray(_sprite->VAO));
    GL_CALL(glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices));
    GL_CALL(glBindVertexArray(0));
}
