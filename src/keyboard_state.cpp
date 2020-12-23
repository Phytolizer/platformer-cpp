//
// Created by kyle on 12/23/20.
//

#include "keyboard_state.hpp"

void KeyboardState::Set(SDL_KeyCode code, bool down)
{
    m_state[code] = down;
}
bool KeyboardState::Pressed(SDL_KeyCode code)
{
    if (m_state.find(code) != m_state.end())
    {
        bool pressed = m_state[code];
        m_state[code] = false;
        return pressed;
    }

    return false;
}
bool KeyboardState::Held(SDL_KeyCode code) const
{
    return m_state.find(code) != m_state.end() && m_state.at(code);
}
