//
//  ScaledVertexData.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-04.
//

#ifndef ScaledVertexData_hpp
#define ScaledVertexData_hpp

#include "Paddle.hpp"

/// Offset vertex positions based on paddle scaling to match box2d
float ScaledVerticies[12] =
{
    - PADDLE_WIDTH/2,   PADDLE_HEIGHT/2,
      PADDLE_WIDTH/2,   PADDLE_HEIGHT/2,
      PADDLE_WIDTH/2, - PADDLE_HEIGHT/2,
    
    - PADDLE_WIDTH/2,   PADDLE_HEIGHT/2,
      PADDLE_WIDTH/2, - PADDLE_HEIGHT/2,
    - PADDLE_WIDTH/2, - PADDLE_HEIGHT/2
};

#endif /* ScaledVertexData_hpp */
