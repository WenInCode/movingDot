//
//  main.h
//  movingDot
//
//  Created by Tyler Wendlandt on 12/26/2013.
//  Copyright (c) 2013 Tyler. All rights reserved.
//

#ifndef movingDot_main_h
#define movingDot_main_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "dot.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

#endif
