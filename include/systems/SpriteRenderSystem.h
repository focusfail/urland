#ifndef URLAND_SPRITE_RENDER_SYSTEM_H
#define URLAND_SPRITE_RENDER_SYSTEM_H

#include <raylib.h>
#include <entt/entt.hpp>

#include "core/Texture2DAtlas.h"

struct SpriteRenderSystem {
    void Render(entt::registry& reg, const Texture2DAtlas& atlas) const;
};

#endif // URLAND_SPRITE_RENDER_SYSTEM_H