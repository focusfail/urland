#include "systems/PlayerSys.h"

void PlayerSystem::Update(entt::registry& reg, float dt)
{
    float speed = 1000.0f;

    if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 4000.0f;

    Vector2 direction(0.0f, 0.0f);

    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;
    if (IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_S)) direction.y += 1;

    if (direction.x == 0 && direction.y == 0) return;

    direction = Vector2Normalize(direction);

    RigidBody& rb = reg.get<RigidBody>(player);

    rb.velX = direction.x * speed * dt;
    rb.velY = direction.y * speed * dt;
}