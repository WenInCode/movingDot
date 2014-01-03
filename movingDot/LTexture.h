//
//  LTexture.h
//  movingDot
//
//  Created by Tyler Wendlandt on 12/26/2013.
//  Copyright (c) 2013 Tyler. All rights reserved.
//

#ifndef __movingDot__LTexture__
#define __movingDot__LTexture__

class LTexture
{
public:
    //Initialize variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    // Loads image at specified path
    bool loadFromFile(std::string path);
    
    //Deallocates texture
    void free();
    
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Set blending
    void setBlendMode(SDL_BlendMode blending);
    
    // Set alpha modulation
    void setAlpha(Uint8 alpha);
    
    //Renders texture at given point
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    // Get the image dimensions
    int getWidth();
    int getHeight();

private:
    //hardware texture
    SDL_Texture* mTexture;
    
    // Image dimensions
    int mWidth;
    int mHeight;
};

#endif /* defined(__movingDot__LTexture__) */
