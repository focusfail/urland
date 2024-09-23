#pragma once

#include "components/RigidBody.h"

#include <entt/entt.hpp>

struct PhysicsSystem
{
    /// @brief Always update last
    /// @param registry
    /// @param dt
    void Update(entt::registry& registry, float dt)
    {
        auto view = registry.view<RigidBody>();

        view.each([&](RigidBody& rb) {
            rb.x += rb.velocity_x;
            rb.y += rb.velocity_y;

            rb.velocity_x *= rb.friction;
            rb.velocity_y *= rb.friction;
        });
    }
};