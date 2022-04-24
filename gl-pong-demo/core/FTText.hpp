//
//  FTText.hpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-05.
//

#ifndef FTText_hpp
#define FTText_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>

#include <ft2build.h>
#include "freetype/freetype.h"

#define IMAGE_WIDTH   128
#define IMAGE_HEIGHT  128

class FTText
{
public:
    FTText();
    ~FTText();
    
    void DrawText(const char* fontName, const char* text, int fontPtSize = 24, int dpi = 100, float x = 0.2f, float y = 0.2f);
    
    unsigned char* texture;
    
private:
    void DrawBitmap(FT_Bitmap *bitmap, FT_Int x, FT_Int y);
};

#endif /* FTText_hpp */
