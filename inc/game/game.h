#ifndef GAME_H
#define GAME_H

#include "game/world/World.h"
#include "core/SpriteManager.h"
#include "systems/PlayerMoveSys.h"
#include "systems/RigidBodyCollisionSys.h"
#include "systems/GravitySys.h"
#include "systems/FollowCameraSys.h"

#include "entt/entt.hpp"

class Game
{
public:
    Game();
    ~Game() = default;

    /// @brief Start the game-loop
    void Run();

private:
    void mRender(float dt) /*const*/;
    void mUpdate(float dt);

    entt::registry mRegistry;
    World mWorld;
    Camera2D mCamera = {0};
    SpriteManager mSpriteManager;

    // systems
    GravitySystem mGravitySystem;
    PlayerMovementSystem mPlayerMovementSystem;
    RigidBodyCollisionSystem mRigidBodyCollisionSystem;
    FollowCameraSystem mFollowCameraSystem;
};

#endif // GAME_H