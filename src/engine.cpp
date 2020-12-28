#include "engine.hpp"
#include "error.hpp"
#include "main.hpp"
#include "platform.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <cstdlib>
#include <fmt/format.h>

Engine::Engine(const std::string_view title, const int width, const int height)
    : m_active(true), m_level({std::make_shared<Platform>(-1, 2, 1, 1), std::make_shared<Platform>(0, 2, 1, 1),
                               std::make_shared<Platform>(1, 2, 1, 1)}),
      m_player(0, 0), m_windowWidth(width), m_windowHeight(height)
{
    SDLERR(SDL_Init(SDL_INIT_VIDEO));
    SDLERR(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG);
    SDLERR(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE);
    m_window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    SDLNULL(m_window);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDLNULL(m_renderer);

    LoadImage("assets/Grass_top.png", "grassTop");
    LoadImage("assets/character.png", "character");
}
void Engine::LoadImage(const std::string_view path, const std::string_view key)
{
    auto *character_surface = IMG_Load(path.data());
    SDLNULL(character_surface);
    auto *character = SDL_CreateTextureFromSurface(m_renderer, character_surface);
    SDLNULL(character);
    m_textureRegistry.Insert(key, character);
}

Engine::~Engine()
{
    if (m_active)
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        IMG_Quit();
    }
}
Engine::Engine(Engine &&other) noexcept
    : m_active(other.m_active), m_window(other.m_window), m_renderer(other.m_renderer),
      m_level(std::move(other.m_level)), m_player(other.m_player), m_windowWidth(other.m_windowWidth),
      m_windowHeight(other.m_windowHeight)
{
    other.m_active = false;
}
Engine &Engine::operator=(Engine &&other) noexcept
{
    if (&other != this)
    {
        if (m_active)
        {
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            IMG_Quit();
        }
        m_window = other.m_window;
        m_renderer = other.m_renderer;
        m_active = other.m_active;
        m_windowWidth = other.m_windowWidth;
        m_windowHeight = other.m_windowHeight;
        m_level = std::move(other.m_level);
        m_player = other.m_player;
        other.m_active = false;
    }

    return *this;
}

int Engine::WindowWidth() const
{
    return m_windowWidth;
}
int Engine::WindowHeight() const
{
    return m_windowHeight;
}
TextureRegistry &Engine::TextureRegistry()
{
    return m_textureRegistry;
}
KeyboardState &Engine::KeyState()
{
    return m_keyState;
}
void Engine::HandleEvent(const SDL_Event &e)
{
    if (e.type == SDL_WINDOWEVENT)
    {
        if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            m_windowWidth = e.window.data1;
            m_windowHeight = e.window.data2;
        }
    }
    if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
    {
        m_keyState.Set(static_cast<SDL_KeyCode>(e.key.keysym.sym), e.type == SDL_KEYDOWN);
    }
}
void Engine::Update()
{
    m_player.Update(1.0 / 60, this);
    m_level.Update(this);
}
void Engine::Draw()
{
    m_level.Show(m_renderer, this);
    m_player.Show(m_renderer, this);
    SDL_RenderPresent(m_renderer);
}