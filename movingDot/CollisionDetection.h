//
//  CollisionDetection.h
//  movingDot
//
//  Created by Tyler Wendlandt on 1/1/2014.
//  Copyright (c) 2014 Tyler. All rights reserved.
//

#ifndef __movingDot__CollisionDetection__
#define __movingDot__CollisionDetection__

#include <iostream>
#include <SDL2/SDL.h>

class CollisionDetection {
public:
    bool checkCollision( SDL_Rect a, SDL_Rect b);
};

#endif /* defined(__movingDot__CollisionDetection__) */
