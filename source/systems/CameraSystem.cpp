#include "systems/CameraSystem.h"

#include "components/Camera.h"
#include "components/CharacterController.h"
#include "components/RigidBody.h"

void CameraSystem::Update(entt::registry& reg, Camera2D& cam)
{
    auto view = reg.view<CameraComponent, CharacterController, RigidBody>();

    cam.zoom = std::clamp(cam.zoom + (GetMouseWheelMove() * 0.1f), 0.01f, 5.00f);

    for (auto entity : view) {
        const auto& cam_c = reg.get<CameraComponent>(entity);
        const auto& body = reg.get<RigidBody>(entity);

        if (!cam_c.active) continue;

        cam.target.x = body.x;
        cam.target.y = body.y;
    }
}