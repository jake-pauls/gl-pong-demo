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

Paddle::Paddle(Mesh* mesh, glm::vec3 pos)
    : _mesh(mesh), _pos(pos)
{

}

void Paddle::Update(glm::mat4 projectionMatrix)
{
    _modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 0.5f));
    _modelMatrix = glm::translate(_modelMatrix, _pos);
    
    _mvpMatrix = projectionMatrix * _modelMatrix;
}

void Paddle::Draw(Shader* shaderProgram)
{
    shaderProgram->Bind();
    
    shaderProgram->SetUniformMatrix4fv("_mvpMatrix", glm::value_ptr(_mvpMatrix));
    shaderProgram->SetUniform4f("_color", 0.85f, 0.1f, 0.0f, 1.0);
    
    GL_CALL(glBindVertexArray(_mesh->VAO));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->IBO));
    GL_CALL(glDrawElements(GL_TRIANGLES, _mesh->NumberOfMeshIndices, GL_UNSIGNED_INT, 0));
    GL_CALL(glBindVertexArray(0));
}
