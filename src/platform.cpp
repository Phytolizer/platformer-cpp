#include "platform.hpp"
#include "engine.hpp"
#include "error.hpp"
#include "main.hpp"
#include "player.hpp"
#include <fmt/format.h>

Platform::Platform(double x, double y, double w, double h) : LevelObject(x, y, w, h)
{
}
void Platform::Update(Engine *engine)
{
}
void Platform::Show(SDL_Renderer *renderer, Engine *engine)
{
    // Pixel Sizes for art
    // left endcap, center, right endcap
    // Collider: 32x32 (1x1)
    // Visual: 40x40 (4 pixels each side for detail stuff)

    SDL_Rect drawRect{static_cast<int>(engine->WindowWidth() / 2.0 + (X() - 0.1) * PIXEL_SCALE),
                      static_cast<int>(engine->WindowHeight() / 2.0 + (Y() - 0.1) * PIXEL_SCALE),
                      static_cast<int>((W() + 0.2) * PIXEL_SCALE), static_cast<int>((H() + 0.2) * PIXEL_SCALE + 8)};
    auto *characterTexture = engine->TextureRegistry().Get("grassTop");
    SDLERR(SDL_RenderCopy(renderer, characterTexture, nullptr, &drawRect));
}
bool Platform::CollideTop(Player *player)
{
    // if player above and moving downward
    return player->X() + Player::Width() > X() && player->X() < X() + W() && player->Y() + Player::Height() < Y() &&
           player->YSpeed() > 0 && player->Y() + Player::Height() + player->YSpeed() > Y();
}
bool Platform::CollideLeft(Player * /*player*/)
{
    return false;
}
bool Platform::CollideRight(Player * /*player*/)
{
    return false;
}
bool Platform::CollideBottom(Player * /*player*/)
{
    return false;
}
