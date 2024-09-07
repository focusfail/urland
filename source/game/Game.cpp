#include "game/Game.h"

void Game::Init()
{
    InitWindow(1920, 1080, "urland dev");

    // Set fps to monitor refresh-rate
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
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
        ClearBackground(BLANK);
    }
    EndDrawing();
}

void Game::m_Update() { }