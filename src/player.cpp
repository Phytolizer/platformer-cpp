//
// Created by kyle on 12/23/20.
//

#include "player.hpp"
#include "engine.hpp"
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
    return sign * (abs(sign * MAX_SPEED - m_xSpeed));
}
void Player::Update(double deltaTime, Engine *engine)
{
    if (engine->KeyState().Held(SDLK_a))
    {
        // move left
        m_xAcceleration = ComputeXAcceleration(-1);
    }
    else if (engine->KeyState().Held(SDLK_d))
    {
        // move right
        m_xAcceleration = ComputeXAcceleration(1);
    }
    else
    {
        m_xAcceleration = 0;
    }
    if (engine->KeyState().Held(SDLK_SPACE) && m_grounded)
    {
        m_ySpeed = -sqrt(2 * GRAVITY * JUMP_HEIGHT);
        m_grounded = false;
    }
    if (!m_grounded)
    {
        m_ySpeed += GRAVITY * deltaTime;
    }

    m_xSpeed += m_xAcceleration * deltaTime;
    m_x += m_xSpeed * deltaTime;
    m_y += m_ySpeed * deltaTime;

    m_facingRight = m_xSpeed > 0;
}

void Player::Show(SDL_Renderer *renderer, Engine *engine) const
{
    SDL_Rect drawRect{static_cast<int>(engine->WindowWidth() / 2.0 + m_x * PIXEL_SCALE),
                      static_cast<int>(engine->WindowHeight() / 2.0 + m_y * PIXEL_SCALE),
                      static_cast<int>(WIDTH * PIXEL_SCALE), static_cast<int>(HEIGHT * PIXEL_SCALE)};
    auto *characterTexture = engine->TextureRegistry().Get("character");
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
double Player::Width()
{
    return WIDTH;
}
double Player::Height()
{
    return HEIGHT;
}
