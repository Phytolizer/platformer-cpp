//
// Created by kyle on 12/23/20.
//

#include "main.hpp"
#include "error.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_video.h>
#include <fmt/format.h>

KeyboardState KEY_STATE;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

int main()
{
    SDLERR(SDL_Init(SDL_INIT_VIDEO));
    SDLERR(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG);

    auto *win = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                 WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    SDLNULL(win);

    bool run = true;
    while (run)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
                break;
            }
            if (e.type == SDL_WINDOWEVENT)
            {
                switch (e.window.event)
                {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    WINDOW_WIDTH = e.window.data1;
                    WINDOW_HEIGHT = e.window.data2;
                    break;
                }
            }
            if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
                KEY_STATE.Set(static_cast<SDL_KeyCode>(e.key.keysym.sym), e.type == SDL_KEYDOWN);
            }
        }

        // Draw, Update
    }

    SDL_Quit();
    IMG_Quit();
    return 0;
}
