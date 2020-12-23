#pragma once

#include <SDL_render.h>

class Player;

class LevelObject
{
  protected:
    double m_x;
    double m_y;
    double m_w;
    double m_h;

    LevelObject(double x, double y, double w, double h);

  public:
    virtual void Update() = 0;
    virtual void Show(SDL_Renderer *renderer) const = 0;
    virtual bool CollideTop(Player *player) const = 0;
    virtual bool CollideLeft(Player *player) const = 0;
    virtual bool CollideRight(Player *player) const = 0;
    virtual bool CollideBottom(Player *player) const = 0;
};