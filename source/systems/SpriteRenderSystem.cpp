#include "systems/SpriteRenderSystem.h"

#include "components/RigidBody.h"
#include "components/SpriteComponent.h"

void SpriteRenderSystem::Render(entt::registry& reg, const Texture2DAtlas& atlas) const
{
    auto view = reg.view<Sprite, RigidBody>();
    int tilesize = atlas.GetTileSize();

    for (auto entity : view) {
        const auto& rb = view.get<RigidBody>(entity);
        const auto& s = view.get<Sprite>(entity);

        for (int x = 0; x < s.width; x++) { atlas.DrawSprite(s.index + x, rb.x + tilesize * x, rb.y); }

        for (int y = 0; y < s.height; y++) { atlas.DrawSprite(s.index + s.width - 1 + y, rb.x, rb.y + tilesize * y); }
    }
}