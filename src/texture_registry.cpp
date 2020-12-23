#include "texture_registry.hpp"

void TextureRegistry::Insert(std::string_view name, SDL_Texture *texture)
{
    m_textures[name.data()] = texture;
}
SDL_Texture *TextureRegistry::Get(std::string_view name)
{
    std::string nameStr = name.data();
    if (m_textures.contains(nameStr))
    {
        return m_textures[nameStr];
    }
    return nullptr;
}
