//
// Created by kyle on 12/23/20.
//

#pragma once

#include <SDL2/SDL.h>
class Player
{
    double m_x;
    double m_y;
    double m_xSpeed;
    double m_ySpeed;
    double m_xAcceleration;
    double m_jumpHeight;
    bool m_grounded;
    bool m_facingRight;
    constexpr static double JUMP_HEIGHT = 2;
    constexpr static double GRAVITY = 3;

    double ComputeXAcceleration(int sign);

  public:
    Player();

    void Update(double deltaTime);
    void Show(SDL_Renderer *renderer);
};
