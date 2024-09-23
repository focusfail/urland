#pragma once

#include "components/RigidBody.h"

#include <raylib.h>
#include <entt/entt.hpp>

struct RenderRigidBodiesSystem {
    void Render(const entt::registry& registry) const
    {
        auto view = registry.view<RigidBody>();

        view.each([](auto& rb) { DrawRectangle(rb.x, rb.y, rb.width, rb.height, RED); });
    }
};