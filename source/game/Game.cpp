#include "game/Game.h" // IWYU pragma: keep
#include "core/Constants.h"
#include "core/Convertions.h"

#include "game/DrawChunkGrid.h"

inline void DrawMetrics() { DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 32, WHITE); }

Game::Game()
    : m_sprite_manager(std::make_unique<SpriteManager>())
{
}

void Game::Init()
{
    InitWindow(1920, 1080, "urland dev");

    // Initialize camera
    m_camera.target = {0.0f, 0.0f};
    m_camera.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    m_camera.rotation = 0.0f;
    m_camera.zoom = 1.0f;

    // Load sprites
    m_sprite_manager->AddTexture("blocks", "c:/code/urland/assets/textures/urland.png");
    m_sprite_manager->AddSprite("blocks", "air", 0, 0, BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS);
    m_sprite_manager->AddSprite("blocks", "dirt", BlocksAsPixels(1), 0, BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS);

    // Set fps to monitor refresh-rate
    // SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    SetTargetFPS(0);

    auto test = m_registry.create();
    auto& rb = m_registry.emplace<RigidBody>(test, 0.0f, 0.0f, 32.0f, 48.0f);
    m_registry.emplace<PlayerTag>(test);
    m_registry.emplace<FollowCamera>(test);

    // Set the worlds block atlas
    m_world.Init(m_sprite_manager->GetTexture("blocks"));
}

void Game::Run()
{
    while (!WindowShouldClose()) {
        m_Update();
        m_Render();
    }
}

void Game::m_Render()
{
    BeginDrawing();
    {
        ClearBackground(BLACK);

        BeginMode2D(m_camera);
        {
            m_world.Render();

            m_render_rigidbody.Render(m_registry);

            DrawChunkGrid(m_camera);
        }
        EndMode2D();
        DrawMetrics();
    }
    EndDrawing();
}

void Game::m_Update()
{
    float dt = GetFrameTime();
    m_camera.zoom = Clamp(m_camera.zoom + (GetMouseWheelMove() * 0.1f), 0.01f, 5.00f);

    m_player_control.Update(m_registry, dt);
    m_physics.Update(m_registry, dt);

    m_world.Update(m_registry, m_camera);
    m_camera_follow.Update(m_registry, m_camera);
}