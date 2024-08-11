#ifndef URLAND_CHARACTER_CONTROL_SYSTEM_H
#define URLAND_CHARACTER_CONTROL_SYSTEM_H

#include <entt/entt.hpp>

struct CharacterControlSystem {
    void Update(entt::registry& reg, float dt);
};

#endif // URLAND_CHARACTER_CONTROL_SYSTEM_H