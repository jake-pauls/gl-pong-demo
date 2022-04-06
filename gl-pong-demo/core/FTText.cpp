//
//  FTText.cpp
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-04-05.
//

#include "FTText.hpp"
#include "Assert.hpp"

FTText::FTText()
{
    texture = (unsigned char *) calloc(IMAGE_WIDTH * IMAGE_HEIGHT * 4, sizeof(unsigned char));
}

FTText::~FTText()
{
    free(texture);
    texture = NULL;
}

void FTText::DrawText(const char* fontName, const char* text, int fontPtSize, int dpi, float x, float y)
{
    FT_Library library;
    FT_Error error = FT_Init_FreeType(&library);
    FT_Face face;
    error = FT_New_Face(library, fontName, 0, &face);
    error = FT_Set_Char_Size(face, fontPtSize * 64, 0, dpi, 0);
    FT_GlyphSlot slot = face->glyph;
    
    FT_Vector pen;
    pen.x = (int)(x * 256) * 64;
    pen.y = (IMAGE_HEIGHT - (int)(y * 256)) * 64;
    
    // Reset texture to RGB * Width * Height
    memset(texture, 0, 4 * IMAGE_WIDTH * IMAGE_HEIGHT);
    
    size_t numChars = strlen(text);
    int n;
    for (n = 0; n < numChars; n++)
    {
        FT_Set_Transform(face, NULL, &pen);
        
        error = FT_Load_Char(face, text[n], FT_LOAD_RENDER);
        
        if (error)
            continue;
        
        DrawBitmap(&slot->bitmap, slot->bitmap_left, IMAGE_HEIGHT-slot->bitmap_top);
        
        pen.x += slot->advance.x;
        pen.y += slot->advance.y;
    }
    
    FT_Done_Face(face);
    FT_Done_FreeType(library);
}

void FTText::DrawBitmap(FT_Bitmap *bitmap, FT_Int x, FT_Int y)
{
    FT_Int i, j, p, q;
    FT_Int x_max = x + bitmap->width;
    FT_Int y_max = y + bitmap->rows;
    
    for (i = x, p = 0; i < x_max; i++, p++)
    {
        for (j = y, q = 0; j < y_max; j++, q++)
        {
            if (i < 0 || j < 0 || i >= IMAGE_WIDTH || j >= IMAGE_HEIGHT)
                continue;
            
            texture[(IMAGE_HEIGHT-j+1)*IMAGE_WIDTH*4+i*4] = bitmap->buffer[q * bitmap->width + p];
            texture[(IMAGE_HEIGHT-j+1)*IMAGE_WIDTH*4+i*4+1] = bitmap->buffer[q * bitmap->width + p];
            texture[(IMAGE_HEIGHT-j+1)*IMAGE_WIDTH*4+i*4+2] = bitmap->buffer[q * bitmap->width + p];
            texture[(IMAGE_HEIGHT-j+1)*IMAGE_WIDTH*4+i*4+3] = 255;
        }
    }
}
