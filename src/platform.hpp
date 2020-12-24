#pragma once

#include "level_object.hpp"

class Engine;

class Platform : public LevelObject
{
  public:
    Platform(double x, double y, double w, double h);
    void Update(Engine *engine) override;
    void Show(SDL_Renderer *renderer, Engine *engine) override;
    bool CollideTop(Player *player) override;
    bool CollideLeft(Player *player) override;
    bool CollideRight(Player *player) override;
    bool CollideBottom(Player *player) override;
};