#pragma once

#include <SDL_render.h>
#include <string>
#include <string_view>
#include <unordered_map>

class TextureRegistry
{
    std::unordered_map<std::string, SDL_Texture *> m_textures;

  public:
    TextureRegistry() = default;

    void Insert(std::string_view name, SDL_Texture *texture);
    SDL_Texture *Get(std::string_view name);
};