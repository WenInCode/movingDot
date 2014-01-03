//
//  CollisionDetection.cpp
//  movingDot
//
//  Created by Tyler Wendlandt on 1/1/2014.
//  Copyright (c) 2014 Tyler. All rights reserved.
//

#include "CollisionDetection.h"

bool CollisionDetection::checkCollision(SDL_Rect a, SDL_Rect b)
{
    // The sides of the rectangles
    int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;
    
    // Calculate the sides of rectA
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    // Calculate the sides of rectB
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    // If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }
    
    else if (topA >= bottomB)
    {
        return false;
    }
    
    else if (rightA <= leftB)
    {
        return false;
    }
    
    else if (leftA >= rightB)
    {
        return false;
    }
    
    else
    {
        return true;
    }
}
