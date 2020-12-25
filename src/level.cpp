#include "level.hpp"
#include "error.hpp"
#include "main.hpp"
#include <SDL_render.h>
#include <fmt/format.h>
#include <memory>

Level::Level(std::vector<std::shared_ptr<LevelObject>> &&objects) : m_objects(objects)
{
}
void Level::Update(Engine *engine)
{
    for (auto &object : m_objects)
    {
        object->Update(engine);
    }
}
void Level::Show(SDL_Renderer *renderer, Engine *engine)
{
    SDLERR(SDL_SetRenderDrawColor(renderer, 153, 201, 207, 255));
    SDLERR(SDL_RenderClear(renderer));
    for (const auto &object : m_objects)
    {
        object->Show(renderer, engine);
    }
}
