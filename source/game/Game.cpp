#include "game/Game.h"

#include "components/Camera.h"
#include "components/CharacterController.h"
#include "components/RigidBody.h"
#include "components/SpriteComponent.h"

#include "core/BlockRegistry.h"
#include "world/DrawChunkGrid.h"

using std::format;

Game::Game()
// : m_atlas(Texture2DAtlas(ASSETS_PATH "/textures/urland.png", 16.0f))
{
    m_col_listener = CollisionListener(&m_world);
}

void Game::Init()
{
    const int win_w = 1920;
    const int win_h = 1080;

    InitWindow(win_w, win_h, "urland");
    TraceLog(LOG_INFO, "URLAND: Initializing urland ...");

    // Init the BlockRegister
    BlockRegistry& br = BlockRegistry::GetInstance();
    br.LoadFromJson("C:/code/urland/assets/blocks.jsonc");
    TraceLog(LOG_INFO, format("URLAND: Registered {} blocks", br.GetNumBlocks()).c_str());

    // Set fps to monitor refresh-rate (vsync)
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    m_atlas = Texture2DAtlas(ASSETS_PATH "/textures/urland.png", 16.0f);

    // Config camera2d
    m_camera = Camera2D {Vector2(win_w / 2.0f, win_h / 2.0f), Vector2(0, 0), 0.0f, 3.0f};

    // Connect ecs listeners
    m_registry.on_update<RigidBody>().connect<&CollisionListener::HandleCollision>(m_col_listener);

    // Create plater
    auto player = m_registry.create();
    m_registry.emplace<Sprite>(player, 80, 1, 2);
    m_registry.emplace<CharacterController>(player);
    m_registry.emplace<RigidBody>(player, 0.0f, 0.0f, 8.0f, 32.0f);
    m_registry.emplace<CameraComponent>(player, true);
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
    OnClose();
}

void Game::Update(float dt)
{
    m_char_sys.Update(m_registry, dt);
    m_cam_sys.Update(m_registry, m_camera);
    m_world.Update(m_registry, dt);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 click_pos = GetMousePosition();
        Vector2 world_pos = GetScreenToWorld2D(click_pos, m_camera);
        Block dirt = Block {1, 1, 15};
        m_world.PlaceBlock(world_pos.x, world_pos.y, dirt);
    }
}

void Game::Render()
{
    const BlockRegistry& br = BlockRegistry::GetInstance();
    BeginDrawing();
    {
        ClearBackground(Color {20, 20, 30, 255});

        BeginMode2D(m_camera);
        {
            m_world.Render(m_atlas, br);
            m_sprite_sys.Render(m_registry, m_atlas);
            DrawChunkGrid(m_camera);
        }
        EndMode2D();

        // Draw game version in the bottom left
        DrawText("urland " GAME_VERSION, 10, GetScreenHeight() - 25, 20, Color {100, 100, 100, 100});
    }
    EndDrawing();
}

void Game::OnClose() { }