#ifndef FOLLOW_CAMERA_SYS_H
#define FOLLOW_CAMERA_SYS_H

#include "raylib.h"
#include "entt/entt.hpp"

#include "components/follow_camera.h"
#include "components/player_tag.h"
#include "components/rigid_body.h"

struct FollowCameraSystem
{
    void Update(entt::registry& reg, Camera2D& camera, float dt)
    {
        reg.view<FollowCamera, PlayerTag, RigidBody>().each([&](FollowCamera& fc, RigidBody& rb) {
            Vector2 targetPosition = {rb.x, rb.y};

            camera.target.x += (targetPosition.x - camera.target.x) * fc.retardation * dt;
            camera.target.y += (targetPosition.y - camera.target.y) * fc.retardation * dt;
        });
    };
};

#endif // FOLLOW_CAMERA_SYS_H
