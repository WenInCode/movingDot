//
//  LTexture.cpp
//  movingDot
//
//  Created by Tyler Wendlandt on 12/26/2013.
//  Copyright (c) 2013 Tyler. All rights reserved.
//

#include "main.h"
#include "LTexture.h"

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    // Get rid of previous processes
    free();
    
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Color key the image
        //What does SDL_mapRBg really do?? ****
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 0, 0xFF, 0xFF));
        
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
                //get the image dimensions
            mHeight = loadSurface->w;
            mWidth = loadSurface->h;
        }
        // Get rid of the temporary surface
        SDL_FreeSurface(loadSurface);
    }
    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    // Free texture if it exists
    if (mTexture != NULL )
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle,
                           SDL_Point* center, SDL_RendererFlip flip)
{
    // Set rendering space and render screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
    //Set clip Rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    // Render the clip to the screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

// a few accessor methods
int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}
