#ifndef GAME_H
#define GAME_H

#include "game/world/world.h"

class Game
{
public:
    Game();
    ~Game() = default;

    void Run();

private:
    void mRender() const;
    void mUpdate();

    World mWorld;
    Camera2D mCamera;
};

#endif // GAME_H