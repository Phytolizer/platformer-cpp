#pragma once

#include "keyboard_state.hpp"
#include "level.hpp"
#include "player.hpp"
#include "texture_registry.hpp"
#include <SDL_events.h>
#include <SDL_video.h>
#include <string_view>

class Engine
{
    bool m_active;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    Level m_level;
    Player m_player;
    KeyboardState m_keyState;
    int m_windowWidth;
    int m_windowHeight;
    TextureRegistry m_textureRegistry;

    void LoadImage(std::string_view path, std::string_view key);

  public:
    Engine(std::string_view title, int width, int height);

    ~Engine();
    Engine(const Engine &) = delete;
    Engine(Engine &&) noexcept;
    Engine &operator=(const Engine &) = delete;
    Engine &operator=(Engine &&) noexcept;

    int WindowWidth() const;
    int WindowHeight() const;

    void HandleEvent(const SDL_Event &e);
    void Update();
    void Draw();

    TextureRegistry &TextureRegistry();
    KeyboardState &KeyState();
};