//
//  Scoreboard.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-05.
//

#ifndef Scoreboard_hpp
#define Scoreboard_hpp

#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2Body.h"

#include "SpriteRenderer.hpp"
#include "Shader.hpp"
#include "FTText.hpp"

#define SCOREBOARD_DIMENSIONS  100.0f

class Scoreboard
{
public:
    Scoreboard();
    Scoreboard(SpriteRenderer* sprite, glm::vec3 pos);
    
    void Update(glm::mat4 viewProjectionMatrix);
    void Draw(Shader* shaderProgram, int playerScore, int enemyScore);
    
private:
    SpriteRenderer* _sprite;
    
    glm::vec3 _pos;
    
    glm::mat4 _mvpMatrix, _modelMatrix;
    
    std::stringstream _stream;
    std::pair<int, int> _scorePair;
    
    // Text rendering
    GLuint _textureId;
    FTText* _ftText;
    glm::vec2 _fontPositions;
    int _fontSize;
    int _fontDpi;
};

#endif /* Scoreboard_hpp */
