//
//  CollisionHandler.cpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-04.
//

#include "CollisionHandler.hpp"
#include "Assert.hpp"

void CollisionHandler::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    
    b2PointState state1[1], state2[2];
    b2GetPointStates(state1, state2, oldManifold, contact->GetManifold());
    
    if (state2[0] == b2_addState)
    {
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        LOG("bodyA.position.y " << bodyA->GetPosition().y);
        PhysicsSolver* physicsSolver = (PhysicsSolver*) bodyA->GetUserData();
        physicsSolver->OnCollision();
    }
}
