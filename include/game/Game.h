#pragma once

#include "game/GameState.h"

#include <raylib.h>

class Game
{
public:
    Game() = default;

    void Init();
    void Run();

private:
    void _Update(Scene* scene);
    void _Render(Scene* scene);

    GameState _game_state;
};