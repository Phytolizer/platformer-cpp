//
// Created by kyle on 12/23/20.
//

#pragma once

#include "keyboard_state.hpp"
#include <SDL2/SDL.h>
#include <map>

extern KeyboardState KEY_STATE;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

#define SDLERR(call)                                                                                                   \
    if ((call) != 0)                                                                                                   \
    {                                                                                                                  \
        throw Error(fmt::format("{} failed: {}", #call, SDL_GetError()));                                              \
    }                                                                                                                  \
    0

#define SDLNULL(ptr)                                                                                                   \
    if ((ptr) == nullptr)                                                                                              \
    {                                                                                                                  \
        throw Error(fmt::format("SDL call failed: {} was nullptr: {}", #ptr, SDL_GetError()));                         \
    }                                                                                                                  \
    0
