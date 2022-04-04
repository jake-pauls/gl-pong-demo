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
    : _accumulator(0.0f), _playerPaddleXPosition(PADDLE_STARTING_X), _lastXInput(0.0f), _ballVelocity(0.0f, 10000.0f)
{
    _gravity = new b2Vec2(0.0f, -9.81f);
    _world = new b2World(*_gravity);
    
    CollisionHandler* _collisionHandler = new CollisionHandler();
    _world->SetContactListener(_collisionHandler);
    
    // Create body definition for player and enemy paddles
    b2BodyDef playerPaddleBodyDef;
    playerPaddleBodyDef.gravityScale = 0.0f;
    playerPaddleBodyDef.type = b2_dynamicBody;
    playerPaddleBodyDef.position.Set(PADDLE_STARTING_X, PADDLE_PLAYER_STARTING_Y);
    
    b2BodyDef enemyPaddleBodyDef;
    enemyPaddleBodyDef.gravityScale = 0.0f;
    enemyPaddleBodyDef.type = b2_dynamicBody;
    enemyPaddleBodyDef.position.Set(PADDLE_STARTING_X, PADDLE_ENEMY_STARTING_Y);
    
    // Create and insert the player and enemy paddles
    _playerPaddleBody = _world->CreateBody(&playerPaddleBodyDef);
    g_PhysicsObjects.insert(std::pair<std::string, b2Body*>("PLAYER_PADDLE", _playerPaddleBody));
    
    _enemyPaddleBody = _world->CreateBody(&enemyPaddleBodyDef);
    g_PhysicsObjects.insert(std::pair<std::string, b2Body*>("ENEMY_PADDLE", _enemyPaddleBody));
    
    _playerPaddleBody->SetUserData(this);
    _playerPaddleBody->SetAwake(false);
    
    _enemyPaddleBody->SetUserData(this);
    _enemyPaddleBody->SetAwake(false);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2);
        
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;
    
    _playerPaddleBody->CreateFixture(&fixtureDef);
    _enemyPaddleBody->CreateFixture(&fixtureDef);
    
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(BALL_STARTING_X, BALL_STARTING_Y);
    
    // Create and insert the ball
    _ballBody = _world->CreateBody(&ballBodyDef);
    g_PhysicsObjects.insert(std::pair<std::string, b2Body*>("BALL", _ballBody));
    
    _ballBody->SetUserData(this);
    _ballBody->SetAwake(false);
    
    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(0, 0);
    dynamicCircle.m_radius = BALL_RADIUS;
    
    b2FixtureDef circleFixtureDef;
    circleFixtureDef.shape = &dynamicCircle;
    circleFixtureDef.friction = 0.0f;
    circleFixtureDef.restitution = 1.0f;
    
    _ballBody->CreateFixture(&circleFixtureDef);
}

void PhysicsSolver::Update(float dt)
{
    _accumulator += dt;
    
    // Check if ball has been launched and apply current velocity
    if (IsBallLaunched)
    {
        _ballBody->SetAwake(true);
        _ballBody->ApplyLinearImpulse(_ballVelocity, _ballBody->GetPosition(), true);
    }
    
    while (_accumulator >= MAX_TIMESTEP)
    {
        _accumulator -= MAX_TIMESTEP;
        _world->Step(MAX_TIMESTEP, NUMBER_OF_VELOCITY_ITERATIONS, NUMBER_OF_POSITION_ITERATIONS);
    }
    
    if (dt > 0.0f)
    {
        _world->Step(dt, NUMBER_OF_VELOCITY_ITERATIONS, NUMBER_OF_POSITION_ITERATIONS);
    }
}

/// Reverse the ball's y-component when it collides with a surface
void PhysicsSolver::OnCollision()
{
    _ballVelocity.y *= -1;
}

/// Apply input updates to physics transforms
void PhysicsSolver::SetPaddleTransformData(float xInput)
{
    float xSensitivity = 54.0f;
    
    if (_lastXInput != xInput)
    {
        if (xInput > 0.0f)
            _playerPaddleXPosition += xSensitivity;
        else if (xInput < 0.0f)
            _playerPaddleXPosition -= xSensitivity;
    }
    
    // Player/enemy y-components are constantly being set which prevents them from being manipulated by forces
    _playerPaddleBody->SetTransform(b2Vec2(_playerPaddleXPosition, PADDLE_PLAYER_STARTING_Y), 0.0f);
    _enemyPaddleBody->SetTransform(b2Vec2(PADDLE_STARTING_X, PADDLE_ENEMY_STARTING_Y), 0.0f);
    
    // Store last xComponent to prevent paddle from continuously moving when input is held
    _lastXInput = xInput;
}
