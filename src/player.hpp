//
// Created by kyle on 12/23/20.
//

#pragma once

#include <SDL2/SDL.h>

class Engine;
class Player
{
    double m_x;
    double m_y;
    double m_xSpeed;
    double m_ySpeed;
    double m_xAcceleration;
    bool m_grounded;
    bool m_facingRight;
    constexpr static double MAX_SPEED = 10;
    constexpr static double JUMP_HEIGHT = 2;
    constexpr static double GRAVITY = 8;
    constexpr static double WIDTH = 1;
    constexpr static double HEIGHT = 2;

    [[nodiscard]] double ComputeXAcceleration(int sign) const;

  public:
    Player(double spawnX, double spawnY);

    void Update(double deltaTime, Engine *engine);
    void Show(SDL_Renderer *renderer, Engine *engine) const;

    [[nodiscard]] double X() const;
    [[nodiscard]] double Y() const;
    [[nodiscard]] double XSpeed() const;
    [[nodiscard]] double YSpeed() const;
    [[nodiscard]] static double Width();
    [[nodiscard]] static double Height();
};
