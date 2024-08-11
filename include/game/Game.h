#ifndef URLAND_GAME_H
#define URLAND_GAME_H

#include "core/Texture2DAtlas.h"
#include "systems/CharacterControlSystem.h"
#include "systems/SpriteRenderSystem.h"

#include <raylib.h>
#include <entt/entt.hpp>

class Game
{
public:
    Game();
    ~Game() = default;
    void Init();
    void Run();

private:
    void Update(float dt);
    void Render();

    entt::registry m_registry;
    Camera2D m_camera;
    Texture2DAtlas m_atlas;

    SpriteRenderSystem m_sprite_sys;
    CharacterControlSystem m_char_sys;
};

#endif // URLAND_GAME_H