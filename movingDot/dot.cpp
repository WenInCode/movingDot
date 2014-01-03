//
//  dot.cpp
//  movingDot
//
//  Created by Tyler Wendlandt on 12/26/2013.
//  Copyright (c) 2013 Tyler. All rights reserved.
//

#include "dot.h"
#include "LTexture.h"
#include "CollisionDetection.h"
#include "math.h"

static LTexture gDotTexture;

Dot::Dot()
{
    // Initializes the offsets
    mPosX = 0;
    mPosY = 0;
    
    // Set collosion box dimension
    mCollider.w = DOT_WIDTH;
    mCollider.h = DOT_HEIGHT;
    
    //Initializes the velocity
    mVelx = 0;
    mVely = 0;
    
    //Initialize start time and whether the dot is grounded
    startTime = 0.0f;
    isGrounded = false;
}

void Dot::handleEvent(SDL_Event e)
{
    // If a key was pressed
    // If the key.repeat == 0 it means that this key press is not a repeat
    // Therefore DOT_VEL is only added once limiting the velocity to 10 pixels/frame
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mVely -= DOT_VEL;
                break;
            case SDLK_DOWN:
                mVely += DOT_VEL;
                break;
            case SDLK_LEFT:
                mVelx -= DOT_VEL;
                break;
            case SDLK_RIGHT:
                mVelx += DOT_VEL;
                break;
            case SDLK_SPACE:
                
                break;
                
        }
    }
    
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch ( e.key.keysym.sym )
        {
            case SDLK_UP:
                mVely += DOT_VEL;
                break;
            case SDLK_DOWN:
                mVely -= DOT_VEL;
                break;
            case SDLK_LEFT:
                mVelx += DOT_VEL;
                break;
            case SDLK_RIGHT:
                mVelx -= DOT_VEL;
                break;
            // if the user presses space, get the start time and
            // set the vertical velocity to the initial jump velocity
            case SDLK_SPACE:
                if (isGrounded)
                {
                    isGrounded = false;
                    startTime = SDL_GetTicks();
                    mVely += DOT_JUMP_VEL;
                }
                break;
        }
    }
}

void Dot::move(SDL_Rect& wall)
{
    CollisionDetection detector;
    // Move the dot left or right
    mPosX += mVelx;
    mCollider.x = mPosX;
    
    // keep the dot within the screen
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH) ||
        detector.checkCollision(mCollider, wall))
    {
        // Move back
        mPosX -= mVelx;
        mCollider.x = mPosX;
    }
    
    //Move the dot up or down
    mVely = calcVelY();
    mPosY += mVely;
    mCollider.y = mPosY;
    
    
    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) ||
       detector.checkCollision(mCollider, wall))
    {
        //Move back
        float distCorrect = ((mCollider.y + mCollider.h) - wall.y);
        mPosY -= distCorrect;
        mCollider.y = mPosY;
        isGrounded = true;
    }
}

int Dot::calcVelY()
{
    if (isGrounded)
    {
        mVely = 0;
    }
    else
    {
        float currentTime = ((SDL_GetTicks() - startTime)/1000);
        printf("%f", currentTime);
        mVely = ((DOT_GRAVITY * currentTime) + mVely);
    }
    return mVely;
}

bool Dot::loadMedia()
{
    // loading success flag
    bool success = true;
    
    //Load dot texture
    if( !gDotTexture.loadFromFile("/Users/tylerwendlandt/Development/Cpp/SDLTutorial/movingDot/dot.bmp"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    
    return success;
}


void Dot::render()
{
    // show the dot
    gDotTexture.render(mPosX, mPosY);
}

void Dot::close()
{
    gDotTexture.free();
}



