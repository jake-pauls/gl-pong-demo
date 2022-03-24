//
//  Assert.cpp
//  gl-maze-demo
//
//  Created by Jake Pauls on 2022-03-08.
//

#include <iostream>

#include "Assert.hpp"

void GLClearErrors()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int lineNumber)
{
    GLenum error;
    
    while((error = glGetError()))
    {
        std::cout << "[OpenGLES Error] #" << error << " - " << function << "::" << file << "::" << lineNumber << std::endl;
        return false;
    }
    
    return true;
}
