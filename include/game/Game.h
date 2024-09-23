#pragma once

#include "core/SpriteManager.h"
#include "core/World.h"

#include "systems/PlayerControlSystem.h"
#include "systems/RenderRigidBody.h"
#include "systems/PhysicsSystem.h"
#include "systems/CameraFollowPlayerSystem.h"

#include <raylib.h>
#include <memory>

class Game
{
public:
    Game();

    void Init();
    void Run();

private:
    void m_Update();
    void m_Render();

    std::unique_ptr<SpriteManager> m_sprite_manager;
    World m_world;
    Camera2D m_camera;
    entt::registry m_registry;
    RenderRigidBodiesSystem m_render_rigidbody;
    PlayerControlSystem m_player_control;
    PhysicsSystem m_physics;
    CameraFollowPlayerSystem m_camera_follow;
};