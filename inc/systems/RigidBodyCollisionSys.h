#ifndef RIGID_BODY_COL_SYS_H
#define RIGID_BODY_COL_SYS_H

#include "entt/entt.hpp"
#include "raylib.h"
#include "raymath.h"

#include "components/PlayerTag.h"
#include "components/RigidBody.h"
#include "game/world/World.h"

class RigidBodyCollisionSystem
{
public:
    RigidBodyCollisionSystem() = default;
    ~RigidBodyCollisionSystem() = default;

    void Init(World& world);
    void Update(entt::registry& reg);

private:
    bool mCheckCollision(const RigidBody& rb, RigidBody& out_rb);

    World* mWorld;
};

#endif // RIGID_BODY_COL_SYS_H