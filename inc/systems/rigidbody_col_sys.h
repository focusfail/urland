#ifndef RIGID_BODY_COL_SYS_H
#define RIGID_BODY_COL_SYS_H

#include "entt/entt.hpp"
#include "raylib.h"
#include "raymath.h"

#include "components/player_tag.h"
#include "components/rigid_body.h"
#include "game/world/world.h"

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