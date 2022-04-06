//
//  Scoreboard.cpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-05.
//


#include "Scoreboard.hpp"
#include "Assert.hpp"

#include "Obj-C-Utils-Interface.h"

Scoreboard::Scoreboard()
{ }

Scoreboard::Scoreboard(SpriteRenderer* sprite, glm::vec3 pos)
    : _sprite(sprite), _pos(pos), _scorePair(std::pair<int, int>(-1, -1))
{
    _ftText = new FTText;
    _fontPositions = glm::vec2(0.1f, 0.2f);
    _fontSize = 16;
    _fontDpi = 100;
}

void Scoreboard::Update(glm::mat4 viewProjectionMatrix)
{
    // Set matrices
    _modelMatrix = glm::translate(glm::mat4(1.0f), _pos);
    _modelMatrix = glm::scale(_modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
    
    _mvpMatrix = viewProjectionMatrix * _modelMatrix;
}

void Scoreboard::Draw(Shader *shaderProgram, int playerScore, int enemyScore)
{
    shaderProgram->Bind();
    
    shaderProgram->SetUniform1i("useTexture", 1);
    shaderProgram->SetUniformMatrix4fv("_mvpMatrix", glm::value_ptr(_mvpMatrix));
    shaderProgram->SetUniform4f("_color", 0.5f, 0.5f, 0.5f, 1.0f);
    
    // Update scores only if it changes
    if (_scorePair.first != playerScore || _scorePair.second != enemyScore) {
        // Clear stream
        _stream.clear();
        _stream.str("");
        _stream << playerScore << " : " << enemyScore;
        
        // Draw text to internal bitmap
        _ftText->DrawText(RetrieveObjectiveCPath("pong.ttf"), _stream.str().c_str(), _fontSize, _fontDpi, _fontPositions.x, _fontPositions.y);

        GL_CALL(glGenTextures(1, &_textureId));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, _textureId));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        
        // Create texture for text using internal bitmap
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *) _ftText->texture));
        
        if (_scorePair.first != playerScore)
            _scorePair.first = playerScore;
        
        if (_scorePair.second != enemyScore)
            _scorePair.second = enemyScore;
    }
    
    GL_CALL(glActiveTexture(GL_TEXTURE0));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, _textureId));
    
    GL_CALL(glBindVertexArray(_sprite->VAO));
    GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
    
    GL_CALL(glBindVertexArray(0));
}
