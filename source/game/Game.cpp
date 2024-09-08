#include "game/Game.h"
#include "core/Constants.h"
#include "core/Convertions.h"
#include "scenes/GameScene.h"

Game::Game()
    : m_sprite_manager(std::make_unique<SpriteManager>())
{ }

void Game::Init()
{
    InitWindow(1920, 1080, "urland dev");

    // Load sprites
    m_sprite_manager->AddTexture("blocks", "c:/code/urland/assets/textures/urland.png");
    m_sprite_manager->AddSprite("blocks", "air", 0, 0, BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS);
    m_sprite_manager->AddSprite("blocks", "dirt", BlocksAsPixels(1), 0, BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS);

    // Set fps to monitor refresh-rate
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    // Add scenes
    auto [scene, index] = m_game_state.AddScene(std::make_unique<GameScene>(&m_game_state, m_sprite_manager.get()));
    m_game_state.SetScene(index);
    scene->Init();
}

void Game::Run()
{
    while (!WindowShouldClose()) {
        Scene* scene = m_game_state.GetCurrentScene();
        m_Update(scene);
        m_Render(scene);
    }
}

void Game::m_Render(Scene* scene)
{
    BeginDrawing();
    {
        ClearBackground(BLANK);
        if (scene) scene->Render();
    }
    EndDrawing();
}

void Game::m_Update(Scene* scene)
{
    if (scene) scene->Update();
}