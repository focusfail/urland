#include "game/Game.h"
#include "scenes/GameScene.h"

void Game::Init()
{
    InitWindow(1920, 1080, "urland dev");

    // Set fps to monitor refresh-rate
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    _game_state.AddScene(std::make_unique<GameScene>(&_game_state));
}

void Game::Run()
{
    while (!WindowShouldClose()) {
        Scene* scene = _game_state.GetCurrentScene();
        _Update(scene);
        _Render(scene);
    }
}

void Game::_Render(Scene* scene)
{
    BeginDrawing();
    {
        ClearBackground(BLANK);
        if (scene) scene->Render();
    }
    EndDrawing();
}

void Game::_Update(Scene* scene)
{
    if (scene) scene->Update();
}