#pragma once

#include "level_object.hpp"

class Platform : public LevelObject
{
  public:
    Platform(double x, double y, double w, double h);
    void Update() override;
    void Show(SDL_Renderer *renderer) const override;
    bool CollideTop(Player *player) const override;
    bool CollideLeft(Player *player) const override;
    bool CollideRight(Player *player) const override;
    bool CollideBottom(Player *player) const override;
};