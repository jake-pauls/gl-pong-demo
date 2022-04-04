//
//  PhysicsSolver.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-03-23.
//

#ifndef PhysicsSolver_hpp
#define PhysicsSolver_hpp

#include <string>
#include <unordered_map>

#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2Body.h"

#include "CollisionHandler.hpp"

#define MAX_TIMESTEP                    1.0f / 60.0f
#define NUMBER_OF_VELOCITY_ITERATIONS          10.0f
#define NUMBER_OF_POSITION_ITERATIONS           3.0f

typedef std::unordered_map<std::string, b2Body*> PhysicsObjectSet;

class PhysicsSolver {
public:
    PhysicsSolver();
    
    void Update(float dt);
    void OnCollision();
    
    PhysicsObjectSet g_PhysicsObjects;
    
    bool IsBallLaunched = true;
    
private:
    float _accumulator;
    
    // World
    b2Vec2* _gravity;
    b2World* _world;
    
    // Paddle
    b2Body* _playerPaddleBody;
    b2Body* _enemyPaddleBody;
    b2Body* _ballBody;
    
    // Kinematics
    b2Vec2 _ballVelocity;
};

#endif /* PhysicsSolver_hpp */
