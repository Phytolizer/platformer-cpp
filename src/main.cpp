//
// Created by kyle on 12/23/20.
//

#include "main.hpp"
#include "engine.hpp"
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

int main(int argc, char* argv[])
{
    Engine engine("Platformer", 800, 600);

    auto timer = Timer(1.0 / 60);

    LevelReader testReader("levels/first.lvl");
    auto tokens = testReader.LexFile();
    testReader.ParseFile(tokens);

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
            engine.HandleEvent(e);
        }

        if (timer.Tick())
        {
            engine.Update();
        }

        engine.Draw();
    }
    return 0;
}
