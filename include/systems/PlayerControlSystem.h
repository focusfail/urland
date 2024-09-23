#pragma once

#include "components/RigidBody.h"
#include "components/FollowCamera.h"
#include "components/tags/PlayerTag.h"

#include <raylib.h>
#include <raymath.h>
#include <entt/entt.hpp>

struct PlayerControlSystem
{
    void Update(entt::registry& registry, float dt)
    {
        auto view = registry.view<PlayerTag, FollowCamera, RigidBody>();

        Vector2 direction(0.0f, 0.0f);
        float speed = 200.0f;

        if (IsKeyDown(KEY_W)) direction.y -= 1;
        if (IsKeyDown(KEY_S)) direction.y += 1;
        if (IsKeyDown(KEY_A)) direction.x -= 1;
        if (IsKeyDown(KEY_D)) direction.x += 1;
        if (IsKeyDown(KEY_SPACE)) direction.y -= 2;
        if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 1000.0f;

        direction = Vector2Normalize(direction);
        if (Vector2Equals(direction, Vector2Zero())) return;

        view.each([&](RigidBody& rb) { rb.ApplyForce(direction.x * speed * dt, direction.y * speed * dt); });
    }
};