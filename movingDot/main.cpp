//  main.cpp
//  movingDot
//
//  Created by Tyler Wendlandt on 12/25/2013.
//  Copyright (c) 2013 Tyler. All rights reserved.


#include "main.h"

SDL_Window* gWindow;
SDL_Renderer* gRenderer;


bool init ()
{
    // Initialization flag
    bool success = true;
    
    // INITIALIZE SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Enable VSync
        if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
        {
            printf("Vsync not enabled");
        }
        // Enable linear texture filtering
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Linear texture filtering not enabled");
        }
        
        // Create the window
        gWindow = SDL_CreateWindow("movingDot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created: SDL Error %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create the renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize the renderer
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (! (IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n",
                           IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}


void close()
{
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    
    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, const char * argv[])
{
    // The dot that will be moving around on the screen
    Dot dot;

    
    // Start SDL and create window
    if (!init())
    {
        printf("failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!dot.loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Main loop flag
            bool quit = false;
            
            // Event handler
            SDL_Event e;
            
            SDL_Rect wall;
            wall.x = 0;
            wall.y = 400;
            wall.w = 640;
            wall.h = 50;
            
            SDL_Rect wall1;
            wall1.x = 0;
            wall1.y = 350;
            wall1.w = 100;
            wall1.h = 20;
            
            // Game loop
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    
                    //Handle input for the dot
                    dot.handleEvent(e);
                }
                
                // Move the dot
                dot.move(wall);
                
                //Clear the screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                
                // Redner the wall
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderDrawRect(gRenderer, &wall);
                
                // Redner the wall
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderDrawRect(gRenderer, &wall1);
                
                //Render objects
                dot.render();
                
                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    dot.close();
    close();
    
    return 0;
}

