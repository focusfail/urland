#ifndef FOLLOW_CAMERA_SYS_H
#define FOLLOW_CAMERA_SYS_H

#include <iostream>
#include "raylib.h"
#include "entt/entt.hpp"

#include "components/FollowCamera.h"
#include "components/PlayerTag.h"
#include "components/RigidBody.h"

struct FollowCameraSystem
{
    /// @brief Updates the camera position to an entity with the FollowCamera component
    /// @param reg
    /// @param camera the target camera
    /// @param dt delta time
    void Update(entt::registry& reg, Camera2D& camera, float dt)
    {
        reg.view<FollowCamera, PlayerTag, RigidBody>().each([&](FollowCamera& fc, RigidBody& rb) {
            Vector2 targetPosition = rb.GetCenter();

            camera.target.x += (targetPosition.x - camera.target.x) * fc.retardation * dt;
            camera.target.y += (targetPosition.y - camera.target.y) * fc.retardation * dt;
        });
    };
};

#endif // FOLLOW_CAMERA_SYS_H
