#include "game/Game.h"

#include "components/CharacterController.h"
#include "components/RigidBody.h"
#include "components/SpriteComponent.h"

Game::Game()
// : m_atlas(Texture2DAtlas(ASSETS_PATH "/textures/urland.png", 16.0f))
{ }

void Game::Init()
{
    const int win_w = 1920;
    const int win_h = 1080;

    InitWindow(win_w, win_h, "urland");
    TraceLog(LOG_INFO, "Initializing urland ...");

    // Set fps to monitor refresh-rate (vsync)
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    m_atlas = Texture2DAtlas(ASSETS_PATH "/textures/urland.png", 16.0f);

    // Create plater
    auto player = m_registry.create();
    m_registry.emplace<Sprite>(player, 80);
    m_registry.emplace<CharacterController>(player);
    m_registry.emplace<RigidBody>(player, 0.0f, 0.0f, 16.0f, 32.0f);
}

void Game::Run()
{
    // Game main-loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        Update(dt);
        Render();
    }

    CloseWindow();
}

void Game::Update(float dt) { m_char_sys.Update(m_registry, dt); }

void Game::Render()
{
    BeginDrawing();
    {
        ClearBackground(Color {20, 20, 30, 255});

        m_sprite_sys.Render(m_registry, m_atlas);

        // Draw game version in the bottom left
        DrawText("urland " GAME_VERSION, 10, GetScreenHeight() - 25, 20, Color {100, 100, 100, 100});
    }
    EndDrawing();
}