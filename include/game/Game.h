#pragma once

#include "core/SpriteManager.h"
#include "game/GameState.h"

#include <raylib.h>

class Game
{
public:
    Game();

    void Init();
    void Run();

private:
    void m_Update(Scene* scene);
    void m_Render(Scene* scene);

    GameState m_game_state;
    unique_ptr<SpriteManager> m_sprite_manager;
};