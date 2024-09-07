#pragma once

#include <raylib.h>

class Game
{
public:
    Game() = default;

    void Init();
    void Run();

private:
    void m_Update();
    void m_Render();
};