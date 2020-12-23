//
// Created by kyle on 12/23/20.
//

#pragma once

#include <SDL2/SDL_keycode.h>
#include <unordered_map>

class KeyboardState
{
    std::unordered_map<SDL_KeyCode, bool> m_state;

  public:
    KeyboardState() = default;
    void Set(SDL_KeyCode code, bool down);
    bool Pressed(SDL_KeyCode code);
    bool Held(SDL_KeyCode code) const;
};
