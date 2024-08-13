#ifndef URLAND_RIGID_BODY_H
#define URLAND_RIGID_BODY_H

#include <entt/entt.hpp>

struct RigidBody {
    float x = 0;
    float y = 0;
    float width = 10;
    float height = 10;
    float dx = 0;
    float dy = 0;

    bool Intersects(const RigidBody& other) const
    {
        return (x < other.x + other.width && x + width > other.x && y < other.y + other.height && y + height > other.y);
    }

    static void RegisterMove(entt::registry& reg, entt::entity e, float dx, float dy)
    {
        reg.patch<RigidBody>(e, [dx, dy](auto& b) {
            b.dx += dx;
            b.dy += dy;
        });
    }
};

#endif // URLAND_RIGID_BODY_H