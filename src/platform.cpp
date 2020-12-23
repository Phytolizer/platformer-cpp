#include "platform.hpp"
#include "error.hpp"
#include "main.hpp"
#include "player.hpp"
#include <fmt/format.h>

Platform::Platform(double x, double y, double w, double h) : LevelObject(x, y, w, h)
{
}
void Platform::Update()
{
}
void Platform::Show(SDL_Renderer *renderer) const
{
    // Pixel Sizes for art
    // left endcap, center, right endcap
    // Collider: 32x32 (1x1)
    // Visual: 40x40 (4 pixels each side for detail stuff)

    SDL_Rect drawRect{static_cast<int>(WINDOW_WIDTH / 2 + (m_x - 0.1) * PIXEL_SCALE),
                      static_cast<int>(WINDOW_HEIGHT / 2 + (m_y - 0.1) * PIXEL_SCALE),
                      static_cast<int>((m_w + 0.2) * PIXEL_SCALE), static_cast<int>((m_h + 0.2) * PIXEL_SCALE + 8)};
    auto *characterTexture = TEXTURE_REGISTRY.Get("grassTop");
    SDLERR(SDL_RenderCopy(renderer, characterTexture, nullptr, &drawRect));
}
bool Platform::CollideTop(Player *player) const
{
    // if player above and moving downward
    return player->X() + player->Width() > m_x && player->X() < m_x + m_w && player->Y() + player->Height() < m_y &&
           player->YSpeed() > 0 && player->Y() + player->Height() + player->YSpeed() > m_y;
}
bool Platform::CollideLeft(Player * /*player*/) const
{
    return false;
}
bool Platform::CollideRight(Player * /*player*/) const
{
    return false;
}
bool Platform::CollideBottom(Player * /*player*/) const
{
    return false;
}
