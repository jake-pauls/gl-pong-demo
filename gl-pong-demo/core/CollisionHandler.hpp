//
//  CollisionHandler.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-04.
//

#ifndef CollisionHandler_hpp
#define CollisionHandler_hpp

#include "Box2D.h"
#include "PhysicsSolver.hpp"

class CollisionHandler : public b2ContactListener
{
public:
    void PreSolve(b2Contact* contact, const b2Manifold* manifold);
};

#endif /* CollisionHandler_hpp */
