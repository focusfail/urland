#ifndef URLAND_COLLISION_LISTENER_H
#define URLAND_COLLISION_LISTENER_H

#include "core/BlockRegistry.h"
#include "world/World.h"

#include "components/RigidBody.h"

#include <entt/entt.hpp>
#include <memory>

class CollisionListener
{
public:
    CollisionListener() = default;
    CollisionListener(World* world)
        : m_world(world)
        , m_block_register(&BlockRegistry::GetInstance())
    { }
    void HandleCollision(entt::registry& reg, entt::entity);
    bool CheckCollision(const RigidBody& entity_rb, RigidBody& out_collision_rb);

private:
    World* m_world;
    BlockRegistry* m_block_register;
};

#endif // URLAND_COLLISION_LISTENER_H