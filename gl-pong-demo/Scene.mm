//
//  Scene.mm
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-03-23.
//

#import "Scene.h"

#include "CubeData.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PhysicsSolver.hpp"
#include "Assert.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

#include "Paddle.hpp"

@interface Scene () {
    GLKView* _viewport;
    Shader* _shaderProgram;
    
    // "Camera" Matrices
    glm::mat4 _projectionMatrix;
    glm::mat4 _modelViewMatrix;
    glm::mat4 _modelViewProjectionMatrix;
    
    // Objects
    Paddle* _paddle;
    
    // Meshes
    Mesh* _cubeMesh;
    
    // Physics
    PhysicsSolver* _physics;
}

@end

@implementation Scene

/// Sets up GL context, loads shaders, and defines GL viewport
- (void)setup:(GLKView *)view
{
    view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    ASSERT(view.context);
    
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    _viewport = view;
    [EAGLContext setCurrentContext:view.context];
    
    ASSERT([self setupShaders]);
    
    // Initialize box2d
    _physics = new PhysicsSolver();
    
    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glEnable(GL_CULL_FACE));
    
    // Physics Solver
    _physics = new PhysicsSolver();
    
    // Meshes
    _cubeMesh = new Mesh();
}

- (void)loadModels
{
    ASSERT([self loadMeshes]);
    
    // Testing box2d
    _physics->Test();
    
    // Creating paddle
    _paddle = new Paddle(_cubeMesh, glm::vec3(0.0f, 1.0f, 0.0f));
}

- (void)update
{
    _projectionMatrix = glm::ortho(0, 800, 0, 600, -10, 100);
    
    _paddle->Update(_projectionMatrix);
}

- (void)draw
{
    // Clear GL viewport before drawing
    GL_CALL(glViewport(0, 0, (int) _viewport.drawableWidth, (int) _viewport.drawableHeight));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    _paddle->Draw(_shaderProgram);
}

/// Loads meshes with relevant render data
- (bool)loadMeshes
{
    _cubeMesh->SetupMesh(Mesh::MeshData{
        CubeVertices,
        sizeof(CubeVertices),
        CubeNormals,
        sizeof(CubeNormals),
        CubeTextureCoords,
        sizeof(CubeTextureCoords),
        CubeIndices,
        sizeof(CubeIndices),
        NumberOfCubeIndices
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
