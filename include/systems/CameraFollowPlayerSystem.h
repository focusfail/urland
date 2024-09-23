#pragma once

#include "components/RigidBody.h"
#include "components/FollowCamera.h"
#include "components/tags/PlayerTag.h"

#include <entt/entt.hpp>
#include <raylib.h>

struct CameraFollowPlayerSystem
{
    void Update(entt::registry& registry, Camera2D& camera)
    {
        auto view = registry.view<FollowCamera, PlayerTag, RigidBody>();

        view.each([&](RigidBody& rb) { camera.target = rb.Center(); });
    }
};