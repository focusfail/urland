#ifndef PLAYER_SYS
#define PLAYER_SYS
#include "entt/entt.hpp"
#include "raylib.h"
#include "raymath.h"

#include "components/PlayerTag.h"
#include "components/RigidBody.h"

struct PlayerSystem
{
    entt::entity player;
    void Update(entt::registry& reg, float dt);
};

#endif // PLAYER_SYS