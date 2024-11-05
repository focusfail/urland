#include "systems/PlayerSys.h"

#include "components/PlayerTag.h"
#include "components/Stats.h"
#include "components/RigidBody.h"
#include "raylib.h"
#include "raymath.h"

void PlayerSystem::ApplyMovement(entt::registry& reg, float dt)
{
    Vector2 direction(0.0f, 0.0f);

    if (IsKeyDown(KEY_A)) direction.x -= 1; // Move left
    if (IsKeyDown(KEY_D)) direction.x += 1; // Move right
    if (IsKeyDown(KEY_W)) direction.y -= 1; // Move up
    if (IsKeyDown(KEY_S)) direction.y += 1; // Move down

    bool sprinting = false;
    if (IsKeyDown(KEY_LEFT_SHIFT)) sprinting = true;

    // Return if not moved
    if (direction.x == 0 && direction.y == 0) return;
    // Normalize direction vector
    direction = Vector2Normalize(direction);

    auto& rb = reg.get<RigidBody>(player);
    auto& stats = reg.get<Stats>(player);

    // Set the correct speed
    float speed = !sprinting ? stats.speed : stats.speed * stats.sprintMul;

    // Apply horizontal movement
    rb.velX = direction.x * speed * dt;

    // Only apply vertical movement if the player has no gravity so he can fly.
    if (!rb.hasGravity) { rb.velY = direction.y * speed * dt; }
}