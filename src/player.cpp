//
// Created by kyle on 12/23/20.
//

#include "player.hpp"
#include "main.hpp"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>

double Player::ComputeXAcceleration(int sign)
{
    return sign * (abs(sign * MAX_SPEED - m_xSpeed));
}
void Player::Update(double deltaTime)
{
    if (KEY_STATE.Held(SDLK_a))
    {
        // move left
        m_xAcceleration = ComputeXAcceleration(-1);
    }
    if (KEY_STATE.Held(SDLK_d))
    {
        // move right
        m_xAcceleration = ComputeXAcceleration(1);
    }
    if (KEY_STATE.Held(SDLK_SPACE) && m_grounded)
    {
        m_ySpeed = sqrt(2 * GRAVITY * JUMP_HEIGHT);
    }
    if (!m_grounded)
    {
        m_ySpeed -= GRAVITY * deltaTime;
    }

    m_x += m_xSpeed * deltaTime;
    m_y += m_ySpeed * deltaTime;
}

void Player::Show(SDL_Renderer *renderer)
{
    SDL_Rect drawRect{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 10, 20};
    SDL_RenderFillRect(renderer, &drawRect);
}
