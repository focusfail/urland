#include "systems/SpriteRenderSystem.h"

#include "components/RigidBody.h"
#include "components/SpriteComponent.h"

void SpriteRenderSystem::Render(entt::registry& reg, const Texture2DAtlas& atlas) const
{
    auto view = reg.view<Sprite, RigidBody>();

    for (auto entity : view) {
        const auto& rb = view.get<RigidBody>(entity);
        const auto& s = view.get<Sprite>(entity);

        atlas.DrawSprite(s.index, rb.x, rb.y);
    }
}