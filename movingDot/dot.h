//
//  dot.h
//  movingDot
//
//  Created by Tyler Wendlandt on 12/26/2013.
//  Copyright (c) 2013 Tyler. All rights reserved.
//

#ifndef __movingDot__dot__
#define __movingDot__dot__

#include <iostream>
#include "main.h"
#include "LTexture.h"

class Dot
{
public:
    
    
    // The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    
    // Maximum axis velocity of the dot
    static const int DOT_VEL = 5;
    
    // Dots initial jump speed
    static const int DOT_JUMP_VEL = -10;
    static const int DOT_GRAVITY = 5;
    
    // Initialize the variables
    Dot();
    
    // Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event e );
    
    // Moves the dot
    void move(SDL_Rect walls[]);
    
    bool loadMedia();
    
    // Shows the dot on the screen
    void render();
    
    void close();
    
private:
    
    // The X and Y offsets of the dot
    float mPosX, mPosY;
    
    //The velocity of the dot
    float mVelx, mVely;
    
    // Calculate the vertical velocity
    float calcVelY();
    
    // Timer used for vertical velocity
    float startTime;
    
    bool isGrounded;
    
    //Dot's collision box
    SDL_Rect mCollider;
};


#endif /* defined(__movingDot__dot__) */
