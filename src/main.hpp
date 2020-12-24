//
// Created by kyle on 12/23/20.
//

#pragma once

#include "keyboard_state.hpp"
#include "texture_registry.hpp"
#include <SDL2/SDL.h>

constexpr double PIXEL_SCALE = 50;

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
