//
// Created by kyle on 12/23/20.
//

#include "main.hpp"
#include "error.hpp"
#include "level.hpp"
#include "platform.hpp"
#include "player.hpp"
#include "timer.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL_events.h>
#include <SDL_hints.h>
#include <SDL_keyboard.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <fmt/format.h>

KeyboardState KEY_STATE;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
TextureRegistry TEXTURE_REGISTRY;

int main(int argc, char *argv[])
{
    SDLERR(SDL_Init(SDL_INIT_VIDEO));
    SDLERR(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG);
    SDLERR(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE);

    auto *win = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                 WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    SDLNULL(win);
    auto *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDLNULL(renderer);

    auto timer = Timer(1.0 / 60);

    auto level = Level({std::make_shared<Platform>(-1, 2, 1, 1), std::make_shared<Platform>(0, 2, 1, 1),
                        std::make_shared<Platform>(1, 2, 1, 1)});
    auto player = Player(0, 0);

    auto *grassTopSurface = IMG_Load("assets/Grass_top.png");
    SDLNULL(grassTopSurface);
    auto *grassTop = SDL_CreateTextureFromSurface(renderer, grassTopSurface);
    SDLNULL(grassTop);
    TEXTURE_REGISTRY.Insert("grassTop", grassTop);

    auto *characterSurface = IMG_Load("assets/character.png");
    SDLNULL(characterSurface);
    auto *character = SDL_CreateTextureFromSurface(renderer, characterSurface);
    SDLNULL(character);
    TEXTURE_REGISTRY.Insert("character", character);

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

        if (timer.Tick())
        {
            // Update
            level.Update();
            player.Update(1.0 / 60);
        }

        SDLERR(SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255));
        SDLERR(SDL_RenderClear(renderer));
        // Draw
        level.Show(renderer);
        player.Show(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    IMG_Quit();
    return 0;
}
