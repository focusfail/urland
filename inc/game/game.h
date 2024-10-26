#ifndef GAME_H
#define GAME_H

#include "game/world/world.h"
#include "core/sprite_manager.h"
#include "systems/player_move_sys.h"
#include "systems/rigidbody_col_sys.h"

#include "entt/entt.hpp"

class Game
{
public:
    Game();
    ~Game() = default;

    void Run();

private:
    void mRender(float dt) const;
    void mUpdate(float dt);

    entt::registry mRegistry;
    World mWorld;
    Camera2D mCamera = {0};
    SpriteManager mSpriteManager;

    // systems
    PlayerMovementSystem mPlayerMovementSystem;
    RigidBodyCollisionSystem mRigidBodyCollisionSystem;
};

#endif // GAME_H