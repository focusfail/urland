#ifndef GAME_H
#define GAME_H

#include "game/world/world.h"
#include "core/sprite_manager.h"

class Game
{
public:
    Game();
    ~Game() = default;

    void Run();

private:
    void mRender(float dt) const;
    void mUpdate(float dt);

    World mWorld;
    Camera2D mCamera = {0};
    SpriteManager mSpriteManager;
};

#endif // GAME_H