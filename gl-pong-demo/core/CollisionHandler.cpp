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
        
        PhysicsSolver* physicsSolver = (PhysicsSolver*) bodyA->GetUserData();
        
        // Checks for type of body it collided with
        if (bodyA->GetType() == b2_dynamicBody) {
            // Collision with Enemy Paddle
            if (bodyA->GetPosition().y > 568) {
                physicsSolver->OnCollision(1);
            }
            // Collision with Player Paddle
            if (bodyA->GetPosition().y < 568) {
                physicsSolver->OnCollision(2);
            }
        }
        // Collision with Wall
        if (bodyA->GetType() == b2_staticBody) {
            physicsSolver->OnCollision(3);
        }
        
        
    }
}
