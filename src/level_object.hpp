#pragma once

#include <SDL_render.h>

class Player;
class Engine;

class LevelObject
{
  private:
    double m_x;
    double m_y;
    double m_w;
    double m_h;

  protected:
    double &X();
    double &Y();
    double &W();
    double &H();

    LevelObject(double x, double y, double w, double h);

  public:
    virtual void Update(Engine *engine) = 0;
    virtual void Show(SDL_Renderer *renderer, Engine *engine) = 0;
    virtual bool CollideTop(Player *player) = 0;
    virtual bool CollideLeft(Player *player) = 0;
    virtual bool CollideRight(Player *player) = 0;
    virtual bool CollideBottom(Player *player) = 0;
};