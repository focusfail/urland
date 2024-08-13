#ifndef URLAND_GAME_H
#define URLAND_GAME_H

#include "core/Texture2DAtlas.h"
#include "listeners/CollisionListener.h"
#include "systems/CameraSystem.h"
#include "systems/CharacterControlSystem.h"
#include "systems/SpriteRenderSystem.h"

#include "world/World.h"

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
    void OnClose();

    entt::registry m_registry;
    Camera2D m_camera;
    Texture2DAtlas m_atlas;
    World m_world;

    SpriteRenderSystem m_sprite_sys;
    CameraSystem m_cam_sys;
    CharacterControlSystem m_char_sys;

    CollisionListener m_col_listener;
};

#endif // URLAND_GAME_H