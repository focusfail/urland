#ifndef GRAVITY_SYS_H
#define GRAVITY_SYS_H

#include "entt/entt.hpp"
#include "components/RigidBody.h"
#include "core/Globals.h"

struct GravitySystem
{
    void Update(entt::registry& reg, float dt)
    {
        reg.view<RigidBody>().each([&](RigidBody& rb) {
            if (rb.hasGravity) rb.velY += RB_GRAVITY * dt;
        });
    }
};

#endif // GRAVITY_SYS_H