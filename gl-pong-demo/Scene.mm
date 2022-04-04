//
//  Scene.mm
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-03-23.
//

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#import "Scene.h"

#include "QuadData.h"

#include "PhysicsSolver.hpp"
#include "Assert.hpp"
#include "Shader.hpp"
#include "SpriteRenderer.hpp"

#include "Paddle.hpp"
#include "Ball.hpp"

@interface Scene () {
    GLKView* _viewport;
    Shader* _shaderProgram;
    
    // "Camera" Matrices
    glm::mat4 _projectionMatrix;
    glm::mat4 _viewProjectionMatrix;
    glm::mat4 _modelViewProjectionMatrix;
    
    // Objects
    Paddle* _paddle;
    Paddle* _enemyPaddle;
    Ball* _ball;
    
    // Sprites
    SpriteRenderer* _basicSprite;
    SpriteRenderer* _circleSprite;
    std::vector<float> _circleVertices;
    
    // Physics
    PhysicsSolver* _physics;
}

@end

@implementation Scene

- (void)dealloc
{
    // Physics
    delete _physics;
    
    // Sprites
    delete _basicSprite;
    delete _circleSprite;
    
    // Objects
    delete _paddle;
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
    GL_CALL(glDisable(GL_CULL_FACE));
    
    // Initialize box2d
    _physics = new PhysicsSolver();
    
    // Sprites
    _basicSprite = new SpriteRenderer();
    _circleSprite = new SpriteRenderer();
    
    _circleVertices = std::vector<float>(60);
    _circleSprite->CreateCircleSprite2(_circleVertices, 30.0f, 1.0f);
    
    for (unsigned int i = 0; i < _circleVertices.size(); i++)
    {
        LOG("[i:" << i << "] " << _circleVertices[i]);
    }
}

- (void)loadModels
{
    ASSERT([self loadSprites]);
    
    // Testing box2d
    _physics->Test();
    
    // Creating paddle
    _paddle = new Paddle(_basicSprite, glm::vec3(PADDLE_STARTING_X, PADDLE_PLAYER_STARTING_Y, 0.0f));
    _enemyPaddle = new Paddle(_basicSprite, glm::vec3(PADDLE_STARTING_X, -PADDLE_PLAYER_STARTING_Y, 0.0f));
    _ball = new Ball(_circleSprite, glm::vec3(0.0f, 0.0f, 0.0f));
}

- (void)update
{
     float aspectRatio = (float) _viewport.drawableWidth / (float) _viewport.drawableHeight;
    
     float halfHeight = _viewport.drawableHeight / 2.0f;
     float halfWidth = halfHeight * aspectRatio;
    
    // Draw orthographic with (0,0) at the center of the screen
    // ie: If viewport resolution is 1000x500, this is ortho setup with: x = [-1000, 1000] andy = [-500, 500]
     _projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight,  -1.0f, 1.0f);
    
    // In orthographic view, the view matrix remains the identity
    _viewProjectionMatrix = _projectionMatrix * glm::mat4(1.0);
    
    _paddle->Update(_viewProjectionMatrix);
    
    _enemyPaddle->Update(_viewProjectionMatrix);
    
    _ball->Update(_viewProjectionMatrix);
}

- (void)draw
{
    // Clear GL viewport before drawing
    GL_CALL(glViewport(0, 0, (int) _viewport.drawableWidth, (int) _viewport.drawableHeight));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    _paddle->Draw(_shaderProgram);
    
    _enemyPaddle->Draw(_shaderProgram);
    
    _ball->Draw(_shaderProgram, (float) _circleVertices.size());
}

/// Loads sprites with relevant render data
- (bool)loadSprites
{
    _basicSprite->SetupSprite(SpriteRenderer::SpriteData{
        QuadVertices,
        sizeof(QuadVertices),
        QuadTexCoords,
        sizeof(QuadTexCoords)
    });
    
    float* circleVertices = &_circleVertices[0];
    _circleSprite->SetupSprite(SpriteRenderer::SpriteData{
        circleVertices,
        sizeof(circleVertices),
    });
    
    return true;
}

/// Sets up basic shaders
- (bool)setupShaders
{
    _shaderProgram = new Shader([self retrieveFilePathByName:"Shader.vsh"], [self retrieveFilePathByName:"Shader.fsh"]);
    
    return true;
}

/// Retrieves resources within the Xcode project
- (const char*)retrieveFilePathByName:(const char*)fileName
{
    return [[[NSBundle mainBundle] pathForResource:[[NSString stringWithUTF8String:fileName] stringByDeletingPathExtension] ofType:[[NSString stringWithUTF8String:fileName] pathExtension]] cStringUsingEncoding:1];
}

@end
