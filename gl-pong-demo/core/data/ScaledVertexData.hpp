//
//  ScaledVertexData.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-04.
//

#ifndef ScaledVertexData_hpp
#define ScaledVertexData_hpp

#include "Paddle.hpp"
#include "Scoreboard.hpp"

/// Offset vertex positions based on paddle scaling to match box2d
float ScaledVertices[12] =
{
    - PADDLE_WIDTH/2,   PADDLE_HEIGHT/2,
      PADDLE_WIDTH/2,   PADDLE_HEIGHT/2,
      PADDLE_WIDTH/2, - PADDLE_HEIGHT/2,
    
    - PADDLE_WIDTH/2,   PADDLE_HEIGHT/2,
      PADDLE_WIDTH/2, - PADDLE_HEIGHT/2,
    - PADDLE_WIDTH/2, - PADDLE_HEIGHT/2
};

/// Used to modify the ball in 'Circle.fsh'
float ScaledTextureCoords[12] =
{
    - PADDLE_WIDTH/2,   PADDLE_HEIGHT/2,
      PADDLE_WIDTH/2,   PADDLE_HEIGHT/2,
      PADDLE_WIDTH/2, - PADDLE_HEIGHT/2,
    
    - PADDLE_WIDTH/2,   PADDLE_HEIGHT/2,
      PADDLE_WIDTH/2, - PADDLE_HEIGHT/2,
    - PADDLE_WIDTH/2, - PADDLE_HEIGHT/2
};

/// Square sprite used to setup the scoreboard with rendered text
float BasicVertices[12] =
{
    - SCOREBOARD_DIMENSIONS/2,   SCOREBOARD_DIMENSIONS/2,
      SCOREBOARD_DIMENSIONS/2,   SCOREBOARD_DIMENSIONS/2,
      SCOREBOARD_DIMENSIONS/2, - SCOREBOARD_DIMENSIONS/2,
    
    - SCOREBOARD_DIMENSIONS/2,   SCOREBOARD_DIMENSIONS/2,
      SCOREBOARD_DIMENSIONS/2, - SCOREBOARD_DIMENSIONS/2,
    - SCOREBOARD_DIMENSIONS/2, - SCOREBOARD_DIMENSIONS/2
};

float BasicTextureCoords[12] =
{
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

#endif /* ScaledVertexData_hpp */
