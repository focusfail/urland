#ifndef PLAYER_SYS
#define PLAYER_SYS
#include "entt/entt.hpp"

struct PlayerSystem
{
    entt::entity player;
    void Update(entt::registry& reg, float dt);
};

#endif // PLAYER_SYS