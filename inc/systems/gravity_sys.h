#ifndef GRAVITY_SYS_H
#define GRAVITY_SYS_H

#include "entt/entt.hpp"
#include "components/rigid_body.h"

struct GravitySystem
{
    void Update(entt::registry& reg, float dt)
    {
        reg.view<RigidBody>().each([&](RigidBody& rb) { rb.velY += 1000.0f * dt; });
    }
};

#endif // GRAVITY_SYS_H