#pragma once

#include "level_object.hpp"
#include <SDL_render.h>
#include <memory>
#include <vector>

class Engine;

/**
 * A level. Contains many owned LevelObject instances.
 */
class Level
{
    std::vector<std::shared_ptr<LevelObject>> m_objects;

  public:
    explicit Level(std::vector<std::shared_ptr<LevelObject>> &&objects);

    void Update(Engine *engine);
    void Show(SDL_Renderer *renderer, Engine *engine);
};