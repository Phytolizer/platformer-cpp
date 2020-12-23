//
// Created by kyle on 12/23/20.
//

#include "player.hpp"
#include "error.hpp"
#include "main.hpp"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <fmt/format.h>

Player::Player(double spawnX, double spawnY)
    : m_x(spawnX), m_y(spawnY), m_facingRight(true), m_grounded(true), m_xAcceleration(0), m_xSpeed(0), m_ySpeed(0)
{
}

double Player::ComputeXAcceleration(int sign) const
{
    return sign * (abs(sign * MAX_SPEED - m_xSpeed)) / 10;
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

    m_facingRight = m_xSpeed > 0;
}

void Player::Show(SDL_Renderer *renderer)
{
    SDL_Rect drawRect{static_cast<int>(WINDOW_WIDTH / 2 + m_x * PIXEL_SCALE),
                      static_cast<int>(WINDOW_HEIGHT / 2 + m_y * PIXEL_SCALE), static_cast<int>(WIDTH * PIXEL_SCALE),
                      static_cast<int>(HEIGHT * PIXEL_SCALE)};
    auto *characterTexture = TEXTURE_REGISTRY.Get("character");
    SDLERR(SDL_RenderCopy(renderer, characterTexture, nullptr, &drawRect));
}

double Player::X() const
{
    return m_x;
}
double Player::Y() const
{
    return m_y;
}
double Player::XSpeed() const
{
    return m_xSpeed;
}
double Player::YSpeed() const
{
    return m_ySpeed;
}
double Player::Width() const
{
    return WIDTH;
}
double Player::Height() const
{
    return HEIGHT;
}
