//
//  PhysicsSolver.cpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-03-23.
//

#include <stdio.h>

#include "PhysicsSolver.hpp"
#include "Assert.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

PhysicsSolver::PhysicsSolver()
{
    _gravity = new b2Vec2(0.0f, -9.81f);
    _world = new b2World(*_gravity);
    
    // Create body definition for player and enemy paddles
    b2BodyDef playerPaddleBodyDef;
    playerPaddleBodyDef.type = b2_dynamicBody;
    playerPaddleBodyDef.position.Set(PADDLE_STARTING_X, PADDLE_PLAYER_STARTING_Y);
    
    b2BodyDef enemyPaddleBodyDef;
    enemyPaddleBodyDef.type = b2_dynamicBody;
    enemyPaddleBodyDef.position.Set(PADDLE_STARTING_X, PADDLE_ENEMY_STARTING_Y);
    
    // Create and insert the player and enemy paddles
    _playerPaddleBody = _world->CreateBody(&playerPaddleBodyDef);
    g_PhysicsObjects.insert(std::pair<std::string, b2Body*>("PLAYER_PADDLE", _playerPaddleBody));
    
    _enemyPaddleBody = _world->CreateBody(&enemyPaddleBodyDef);
    g_PhysicsObjects.insert(std::pair<std::string, b2Body*>("ENEMY_PADDLE", _enemyPaddleBody));
    
    _playerPaddleBody->SetAwake(false);
    _enemyPaddleBody->SetAwake(false);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2);
        
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 1.0f;
    
    _playerPaddleBody->CreateFixture(&fixtureDef);
    _enemyPaddleBody->CreateFixture(&fixtureDef);
    
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(BALL_STARTING_X, BALL_STARTING_Y);
    
    // Create and insert the ball
    _ballBody = _world->CreateBody(&ballBodyDef);
    g_PhysicsObjects.insert(std::pair<std::string, b2Body*>("BALL", _ballBody));
    
    _ballBody->SetAwake(false);
    
    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(0, 0);
    dynamicCircle.m_radius = BALL_RADIUS;
    
    b2FixtureDef circleFixtureDef;
    circleFixtureDef.shape = &dynamicCircle;
    circleFixtureDef.density = 1.0f;
    circleFixtureDef.friction = 0.3f;
    circleFixtureDef.restitution = 1.0f;
    
    _ballBody->CreateFixture(&circleFixtureDef);
    
    _accumulator = 0.0f;
}

void PhysicsSolver::Update(float dt)
{
    _accumulator += dt;
    
    if (IsBallLaunched)
    {
        _ballBody->ApplyLinearImpulse(b2Vec2(0, 10000.0f), _ballBody->GetPosition(), true);
        _ballBody->SetAwake(true);
    }
    
    if (_world)
    {
        if (dt > 0.0f)
        {
            _world->Step(dt, NUMBER_OF_VELOCITY_ITERATIONS, NUMBER_OF_POSITION_ITERATIONS);
        }
    }
}

/// Sample test that can be run to test box2d
void PhysicsSolver::Test()
{
    LOG("[PhysicsSolver] Running initial test...");
    
    _groundBodyDef = new b2BodyDef;
    _groundBodyDef->position.Set(0.0f, -10.0f);
    _groundBody = _world->CreateBody(_groundBodyDef);
    
    _groundBox = new b2PolygonShape;
    _groundBox->SetAsBox(50.0f, 10.0f);
    
    _groundBody->CreateFixture(_groundBox, 0.0f);
    
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = _world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    
    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    
    // Override the default friction.
    fixtureDef.friction = 0.3f;
    
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
    
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    
    // This is our little game loop.
    for (int32 i = 0; i < 60; ++i)
    {
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        _world->Step(timeStep, velocityIterations, positionIterations);
        
        // Now print the position and angle of the body.
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }
}
