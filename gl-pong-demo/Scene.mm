//
//  Scene.mm
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-03-23.
//

#include <vector>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#import "Scene.h"

#include "ScaledVertexData.hpp"

#include "PhysicsSolver.hpp"
#include "Assert.hpp"
#include "Shader.hpp"
#include "SpriteRenderer.hpp"

#include "Paddle.hpp"
#include "Ball.hpp"
#include "Scoreboard.hpp"

@interface Scene () {
    GLKView* _viewport;
    std::chrono::time_point<std::chrono::steady_clock> _lastTime;
    
    // Shaders
    Shader* _defaultShaderProgram;
    Shader* _circleShaderProgram;
    
    // "Camera" Matrices
    glm::mat4 _projectionMatrix;
    glm::mat4 _viewProjectionMatrix;
    glm::mat4 _modelViewProjectionMatrix;
    
    // Objects
    Paddle* _playerPaddle;
    Paddle* _enemyPaddle;
    Ball* _ball;
    Scoreboard* _scoreboard;
    
    // Sprites
    SpriteRenderer* _scaledSprite;
    SpriteRenderer* _scoreboardSprite;
    
    // Physics
    PhysicsSolver* _physics;
}

@end

@implementation Scene

@synthesize playerPaddleXInput;
@synthesize playerScore;
@synthesize enemyScore;

- (void)dealloc
{
    // Shaders
    delete _defaultShaderProgram;
    delete _circleShaderProgram;
    
    // Physics
    delete _physics;
    
    // Sprites
    delete _scaledSprite;
    delete _scoreboardSprite;
   
    // Objects
    delete _playerPaddle;
    delete _enemyPaddle;
    delete _ball;
}

/// Sets up GL context, loads shaders, and defines GL viewport
- (void)setup:(GLKView *)view
{
    view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    ASSERT(view.context);
    
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    _viewport = view;
    [EAGLContext setCurrentContext:view.context];
    
    ASSERT([self setupShaders]);
    
    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CALL(glEnable(GL_DEPTH_TEST));
    
    // Disable backface culling for sprite quads
//    GL_CALL(glDisable(GL_CULL_FACE));
    
    // Initialize time
    _lastTime = std::chrono::steady_clock::now();

    // Initialize box2d
    _physics = new PhysicsSolver();
    
    // Sprites
    _scaledSprite = new SpriteRenderer();
    _scoreboardSprite = new SpriteRenderer();
}

- (void)loadModels
{
    ASSERT([self loadSprites]);
    
    _playerPaddle = new Paddle(_scaledSprite);
    
    _enemyPaddle = new Paddle(_scaledSprite);
    
    _ball = new Ball(_scaledSprite);
    
    _scoreboard = new Scoreboard(_scoreboardSprite, glm::vec3(320.0f, 568.0f, 0.5f));
}

- (void)update
{
     _projectionMatrix = glm::ortho(0.0f, (float) _viewport.drawableWidth, 0.0f, (float) _viewport.drawableHeight,  -1.0f, 1.0f);
    
    // In orthographic view, the view matrix remains the identity
    _viewProjectionMatrix = _projectionMatrix * glm::mat4(1.0);
    
    // Calculate elapsed time and update PhysicsSolver
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastTime).count();
    _lastTime = currentTime;

    _physics->Update(elapsedTime / 1000.0f);
    
    // Update score UI
    playerScore = _physics->playerScore;
    enemyScore = _physics->enemyScore;
    
    // Update player paddle transforms
    _physics->SetPaddleTransformData(playerPaddleXInput);
    
    // Check if each GameObject has a corresponding physics object
    if (_physics->g_PhysicsObjects.find("PLAYER_PADDLE") != _physics->g_PhysicsObjects.end())
        _playerPaddle->Update(_viewProjectionMatrix, _physics->g_PhysicsObjects["PLAYER_PADDLE"]);
    
    if (_physics->g_PhysicsObjects.find("ENEMY_PADDLE") != _physics->g_PhysicsObjects.end())
        _enemyPaddle->Update(_viewProjectionMatrix, _physics->g_PhysicsObjects["ENEMY_PADDLE"]);
    
    if (_physics->g_PhysicsObjects.find("BALL") != _physics->g_PhysicsObjects.end())
        _ball->Update(_viewProjectionMatrix, _physics->g_PhysicsObjects["BALL"]);
    
    // Scoreboard updates in isolation of physics
    _scoreboard->Update(_viewProjectionMatrix);
}

- (void)draw
{
    // Clear GL viewport before drawing
    GL_CALL(glViewport(0, 0, (int) _viewport.drawableWidth, (int) _viewport.drawableHeight));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    _playerPaddle->Draw(_defaultShaderProgram);
    
    _enemyPaddle->Draw(_defaultShaderProgram);
    
    _ball->Draw(_circleShaderProgram);
    
    _scoreboard->Draw(_defaultShaderProgram, playerScore, enemyScore);
}

/// Loads sprites with relevant render data
- (bool)loadSprites
{
    _scaledSprite->SetupSprite(SpriteRenderer::SpriteData{
        ScaledVertices,
        sizeof(ScaledVertices),
        ScaledTextureCoords,
        sizeof(ScaledTextureCoords)
    });
    
    _scoreboardSprite->SetupSprite(SpriteRenderer::SpriteData{
        BasicVertices,
        sizeof(BasicVertices),
        BasicTextureCoords,
        sizeof(BasicTextureCoords)
    });
    
    return true;
}

/// Sets up basic shaders
- (bool)setupShaders
{
    _defaultShaderProgram = new Shader([Scene RetrieveFilePathByName:"Shader.vsh"], [Scene RetrieveFilePathByName:"Shader.fsh"]);
    _circleShaderProgram = new Shader([Scene RetrieveFilePathByName:"Circle.vsh"], [Scene RetrieveFilePathByName:"Circle.fsh"]);
    
    return true;
}

/// Retrieves resources within the Xcode project
+ (const char*)RetrieveFilePathByName:(const char*)fileName
{
    return [[[NSBundle mainBundle] pathForResource:[[NSString stringWithUTF8String:fileName] stringByDeletingPathExtension] ofType:[[NSString stringWithUTF8String:fileName] pathExtension]] cStringUsingEncoding:1];
}

const char* RetrieveObjectiveCPath(const char* fileName)
{
    return [Scene RetrieveFilePathByName:fileName];
}

@end
