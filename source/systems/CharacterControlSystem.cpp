#include "systems/CharacterControlSystem.h"
#include "components/CharacterController.h"
#include "components/RigidBody.h"

#include <raylib.h>
#include <raymath.h>

void CharacterControlSystem::Update(entt::registry& reg, float dt)
{
    auto view = reg.view<RigidBody, CharacterController>();

    Vector2 direction(0.0f, 0.0f);

    if (IsKeyDown(KEY_W)) { direction.y -= 1.0f; }
    if (IsKeyDown(KEY_S)) { direction.y += 1.0f; }
    if (IsKeyDown(KEY_A)) { direction.x -= 1.0f; }
    if (IsKeyDown(KEY_D)) { direction.x += 1.0f; }

    float speed = 200.0f;
    if (IsKeyDown(KEY_LEFT_CONTROL)) speed = speed * 10.0f;

    direction = Vector2Normalize(direction);

    // Character did not more
    if (Vector2Length(direction) == 0.0f) return;

    for (auto entity : view) {
        // auto& rb = view.get<RigidBody>(entity);

        float dx = speed * direction.x * dt;
        float dy = speed * direction.y * dt;
        RigidBody::RegisterMove(reg, entity, dx, dy);
    }
}